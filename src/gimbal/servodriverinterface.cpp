#include "include/gimbal/servodriverinterface.h"
#include <QModbusReply>
#include <QSerialPort>
#include <QVariant>
#include <QDebug>

ServoDriverInterface::ServoDriverInterface(const QString &identifier,
                                           const QString &device,
                                           int baudRate,
                                           int slaveId,
                                           QObject *parent)
    : QObject(parent),
    m_identifier(identifier),
    m_device(device),
    m_baudRate(baudRate),
    m_slaveId(slaveId),
    m_modbusDevice(nullptr),
    m_readTimer(new QTimer(this)),
    m_timeoutTimer(new QTimer(this))
{
    // Initialize Modbus device
    m_modbusDevice = new QModbusRtuSerialClient(this);

    // Configure connection parameters
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_device);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m_baudRate);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);

    m_modbusDevice->setTimeout(500); // 500 ms timeout
    m_modbusDevice->setNumberOfRetries(3);

    // Set up read timer
    connect(m_readTimer, &QTimer::timeout, this, &ServoDriverInterface::readData);
    m_readTimer->setInterval(50); // Adjust interval as needed

    // Set up timeout timer
    connect(m_timeoutTimer, &QTimer::timeout, this, &ServoDriverInterface::handleTimeout);
    m_timeoutTimer->setSingleShot(true);

    // Connect Modbus signals
    connect(m_modbusDevice, &QModbusClient::stateChanged, this, &ServoDriverInterface::onStateChanged);
    connect(m_modbusDevice, &QModbusClient::errorOccurred, this, &ServoDriverInterface::onErrorOccurred);
}

ServoDriverInterface::~ServoDriverInterface() {
    disconnectDevice();
}

bool ServoDriverInterface::connectDevice() {
    if (!m_modbusDevice)
        return false;

    if (m_modbusDevice->state() != QModbusDevice::UnconnectedState) {
        m_modbusDevice->disconnectDevice();
    }

    // Remove setServerAddress() call
    // m_modbusDevice->setServerAddress(m_slaveId); // Not needed

    if (!m_modbusDevice->connectDevice()) {
        logError(QString("Failed to connect to Modbus device: %1").arg(m_modbusDevice->errorString()));
        emit connectionStatusChanged(false);
        return false;
    }

    // Connection process is asynchronous; actual connection is confirmed in onStateChanged()
    return true;
}

void ServoDriverInterface::disconnectDevice() {
    if (m_modbusDevice) {
        if (m_modbusDevice->state() != QModbusDevice::UnconnectedState) {
            m_modbusDevice->disconnectDevice();
        }
        m_modbusDevice->deleteLater();
        m_modbusDevice = nullptr;
        emit logMessage(QString("[%1] Modbus connection closed.").arg(m_identifier));
        emit connectionStatusChanged(false);
    }

    if (m_readTimer->isActive())
        m_readTimer->stop();
}

void ServoDriverInterface::onStateChanged(QModbusDevice::State state) {
    if (state == QModbusDevice::ConnectedState) {
        emit logMessage(QString("[%1] Modbus connection established successfully.").arg(m_identifier));
        emit connectionStatusChanged(true);
        // Start reading data
        m_readTimer->start();
    } else if (state == QModbusDevice::UnconnectedState) {
        emit logMessage(QString("[%1] Modbus device disconnected.").arg(m_identifier));
        emit connectionStatusChanged(false);
        m_readTimer->stop();
    }
}

void ServoDriverInterface::onErrorOccurred(QModbusDevice::Error error) {
    if (error == QModbusDevice::NoError)
        return;
    logError(QString("Modbus error: %1").arg(m_modbusDevice->errorString()));
    emit errorOccurred(m_modbusDevice->errorString()); // Emit signal with QString
}

void ServoDriverInterface::readData() {
    if (!m_modbusDevice || m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return;

    QMutexLocker locker(&m_mutex);

    int startAddress = 196;
    int numberOfEntries = 50;

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, numberOfEntries);

    if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, m_slaveId)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &ServoDriverInterface::onReadReady);
            // Start timeout timer
            if (!m_timeoutTimer->isActive())
                m_timeoutTimer->start(1000); // Adjust timeout as needed
        } else {
            // Reply is finished immediately
            reply->deleteLater();
        }
    } else {
        logError(QString("Read error: %1").arg(m_modbusDevice->errorString()));
        emit errorOccurred(m_modbusDevice->errorString()); // Emit errorOccurred signal
        emit connectionStatusChanged(false);
    }
}

void ServoDriverInterface::onReadReady() {
    auto *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    // Stop timeout timer
    if (m_timeoutTimer->isActive())
        m_timeoutTimer->stop();

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        QVector<uint16_t> data;
        data.reserve(unit.valueCount());
        for (uint i = 0; i < unit.valueCount(); ++i) {
            data.append(unit.value(i));
        }

        emit dataRead(data);
        emit connectionStatusChanged(true);

    } else {
        logError(QString("Read response error: %1").arg(reply->errorString()));
        emit errorOccurred(reply->errorString()); // Emit errorOccurred signal
        emit connectionStatusChanged(false);
    }

    reply->deleteLater();
}

void ServoDriverInterface::handleTimeout() {
    logError("Timeout waiting for response from servo driver.");
    emit errorOccurred("Timeout waiting for response from servo driver."); // Emit errorOccurred signal
    // Handle timeout (e.g., attempt reconnection)
    if (m_modbusDevice) {
        m_modbusDevice->disconnectDevice();
        // Optionally, attempt reconnection after some delay
        QTimer::singleShot(1000, this, &ServoDriverInterface::connectDevice);
    }
}

void ServoDriverInterface::logError(const QString &message) {
    emit logMessage(QString("[%1] %2").arg(m_identifier, message));
    qWarning() << QString("[%1] %2").arg(m_identifier, message);
}
