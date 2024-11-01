#include "include/comm/plcmodbusworker.h"
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QSerialPort>
#include <QVariant>
#include <QDebug>

PLCModbusWorker::PLCModbusWorker(const QString &portName, int baudRate, QObject *parent)
    : QObject(parent),
    m_modbusDevice(nullptr),
    m_timer(nullptr),
    m_portName(portName),
    m_baudRate(baudRate),
    m_running(false)
{
}

PLCModbusWorker::~PLCModbusWorker() {
    stopCommunication();
}

void PLCModbusWorker::startCommunication() {
    QMutexLocker locker(&m_mutex);
    if (m_running) return;

    m_modbusDevice = new QModbusRtuSerialClient(this);

    // Configure connection parameters
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_portName);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m_baudRate);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);

    // Set timeout and number of retries
    m_modbusDevice->setTimeout(500); // 500 ms timeout
    m_modbusDevice->setNumberOfRetries(3);

    // Connect signals
    connect(m_modbusDevice, &QModbusClient::stateChanged, this, &PLCModbusWorker::onStateChanged);
    connect(m_modbusDevice, &QModbusClient::errorOccurred, this, &PLCModbusWorker::onErrorOccurred);

    if (!m_modbusDevice->connectDevice()) {
        logError("Failed to connect to Modbus device: " + m_modbusDevice->errorString());
        delete m_modbusDevice;
        m_modbusDevice = nullptr;
        return;
    }

    m_running = true;

    // Set up the timer for periodic tasks
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &PLCModbusWorker::performPeriodicTasks);
    m_timer->start(100); // Every 100 ms
}

void PLCModbusWorker::stopCommunication() {
    QMutexLocker locker(&m_mutex);
    if (!m_running) return;

    m_running = false;

    if (m_timer) {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = nullptr;
    }

    if (m_modbusDevice) {
        m_modbusDevice->disconnectDevice();
        m_modbusDevice->deleteLater();
        m_modbusDevice = nullptr;
    }

    emit connectionStatusChanged(false);
    emit logMessage("Disconnected from PLC.");
}

void PLCModbusWorker::performPeriodicTasks() {
    if (!m_running || !m_modbusDevice) return;

    // Example periodic tasks
    int serverAddress = 2; // Set your Modbus server address (slave ID)
    readRegisters(serverAddress, 0, 6);
    readInputBits(serverAddress, 0, 13);
}

void PLCModbusWorker::writeRegister(int serverAddress, int registerAddress, uint16_t value) {
    if (!m_modbusDevice) return;

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, registerAddress, 1);
    writeUnit.setValue(0, value);

    if (auto *reply = m_modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCModbusWorker::onWriteFinished);
        } else {
            // Broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        logError("Write error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCModbusWorker::writeRegisters(int serverAddress, int startAddress, const QVector<uint16_t> &values) {
    if (!m_modbusDevice) return;

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, values.size());
    for (int i = 0; i < values.size(); ++i) {
        writeUnit.setValue(i, values.at(i));
    }

    if (auto *reply = m_modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCModbusWorker::onWriteFinished);
        } else {
            reply->deleteLater();
        }
    } else {
        logError("Write error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCModbusWorker::readRegisters(int serverAddress, int startAddress, int count) {
    if (!m_modbusDevice) return;

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, count);

    if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCModbusWorker::onReadReady);
        } else {
            // Reply is finished immediately
            reply->deleteLater();
        }
    } else {
        logError("Read error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCModbusWorker::readInputBits(int serverAddress, int startAddress, int count) {
    if (!m_modbusDevice) return;

    QModbusDataUnit readUnit(QModbusDataUnit::DiscreteInputs, startAddress, count);

    if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCModbusWorker::onReadReady);
        } else {
            reply->deleteLater();
        }
    } else {
        logError("Read error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCModbusWorker::onReadReady() {
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        if (unit.registerType() == QModbusDataUnit::HoldingRegisters) {
            QVector<uint16_t> values;
            for (uint i = 0; i < unit.valueCount(); ++i) {
                values.append(unit.value(i));
            }
            emit registersRead(unit.startAddress(), values);
        } else if (unit.registerType() == QModbusDataUnit::DiscreteInputs) {
            QVector<uint8_t> bits;
            for (uint i = 0; i < unit.valueCount(); ++i) {
                bits.append(unit.value(i));
            }
            emit inputBitsRead(unit.startAddress(), bits);
        }
    } else {
        logError("Read response error: " + reply->errorString());
        emit errorOccurred(reply->errorString());
    }

    reply->deleteLater();
}

void PLCModbusWorker::onWriteFinished() {
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        // Determine the address written to
        const QModbusDataUnit unit = reply->result();
        emit writeCompleted(unit.startAddress());
    } else {
        logError("Write response error: " + reply->errorString());
        emit errorOccurred(reply->errorString());
    }

    reply->deleteLater();
}

void PLCModbusWorker::onStateChanged(QModbusDevice::State state) {
    if (state == QModbusDevice::ConnectedState) {
        emit connectionStatusChanged(true);
        emit logMessage("Connected to PLC via Modbus successfully.");
    } else if (state == QModbusDevice::UnconnectedState) {
        emit connectionStatusChanged(false);
        emit logMessage("Disconnected from PLC.");
        m_running = false;
    }
}

void PLCModbusWorker::onErrorOccurred(QModbusDevice::Error error) {
    if (error == QModbusDevice::NoError || !m_modbusDevice)
        return;

    logError("Modbus error: " + m_modbusDevice->errorString());
    emit errorOccurred(m_modbusDevice->errorString());
}

void PLCModbusWorker::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCModbusWorker:" << message;
}
