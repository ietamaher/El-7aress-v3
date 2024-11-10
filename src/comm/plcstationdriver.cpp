#include "include/comm/plcstationdriver.h"
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QSerialPort>
#include <QVariant>

#include <QDebug>

PLCStationDriver::PLCStationDriver(const QString &portName, int baudRate, QObject *parent)
    : QObject(parent),
    m_modbusDevice(nullptr),
    m_timer(nullptr),
    m_portName(portName),
    m_baudRate(baudRate),
    m_running(false)
{
}

PLCStationDriver::~PLCStationDriver() {
    stopCommunication();
}

void PLCStationDriver::startCommunication() {
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
    connect(m_modbusDevice, &QModbusClient::stateChanged, this, &PLCStationDriver::onStateChanged);
    connect(m_modbusDevice, &QModbusClient::errorOccurred, this, &PLCStationDriver::onErrorOccurred);

    if (!m_modbusDevice->connectDevice()) {
        logError("Failed to connect to Modbus device: " + m_modbusDevice->errorString());
        delete m_modbusDevice;
        m_modbusDevice = nullptr;
        return;
    }
    qDebug() << "PLC STATION is  connected ....";


    if (!m_timer) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &PLCStationDriver::performPeriodicTasks);
    }
    m_timer->start(250);

    m_running = true;
}

void PLCStationDriver::startPeriodicReads(int intervalMs) {
    QMutexLocker locker(&m_mutex);
    if (!m_running || !m_modbusDevice) return;

    if (!m_timer) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &PLCStationDriver::performPeriodicTasks);
    }
    m_timer->start(intervalMs);
}

void PLCStationDriver::performPeriodicTasks() {
    if (!m_running || !m_modbusDevice) return;

    int serverAddress = 2; // Modbus slave ID

    // Read input bits (digital inputs)
    readInputBits(serverAddress, DIGITAL_INPUTS_START_ADDRESS, DIGITAL_INPUTS_COUNT);

    // Read input registers (analog inputs)
    readInputRegisters(serverAddress, ANALOG_INPUTS_START_ADDRESS, ANALOG_INPUTS_COUNT);
}

void PLCStationDriver::stopCommunication() {
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

void PLCStationDriver::writeRegister(int serverAddress, int registerAddress, uint16_t value) {
    if (!m_modbusDevice) return;

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, registerAddress, 1);
    writeUnit.setValue(0, value);

    if (auto *reply = m_modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCStationDriver::onWriteFinished);
        } else {
            // Broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        logError("Write error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCStationDriver::writeRegisters(int serverAddress, int startAddress, const QVector<uint16_t> &values) {
    if (!m_modbusDevice) return;

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, values.size());
    for (int i = 0; i < values.size(); ++i) {
        writeUnit.setValue(i, values.at(i));
    }

    if (auto *reply = m_modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCStationDriver::onWriteFinished);
        } else {
            reply->deleteLater();
        }
    } else {
        logError("Write error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCStationDriver::readRegisters(int serverAddress, int startAddress, int count) {
    if (!m_modbusDevice) return;

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, count);

    if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCStationDriver::onReadReady);
        } else {
            // Reply is finished immediately
            reply->deleteLater();
        }
    } else {
        logError("Read error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}
void PLCStationDriver::readInputRegisters(int serverAddress, int startAddress, int count) {
    if (!m_modbusDevice) return;

    QModbusDataUnit readUnit(QModbusDataUnit::InputRegisters, startAddress, count);

    if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCStationDriver::onReadReady);
        } else {
            reply->deleteLater();
        }
    } else {
        logError("Read error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCStationDriver::readInputBits(int serverAddress, int startAddress, int count) {
    if (!m_modbusDevice) return;

    QModbusDataUnit readUnit(QModbusDataUnit::DiscreteInputs, startAddress, count);

    if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCStationDriver::onReadReady);
        } else {
            reply->deleteLater();
        }
    } else {
        logError("Read error: " + m_modbusDevice->errorString());
        emit errorOccurred(m_modbusDevice->errorString());
    }
}


void PLCStationDriver::onReadReady() {
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
        } else if (unit.registerType() == QModbusDataUnit::InputRegisters) {
            QVector<uint16_t> values;
            for (uint i = 0; i < unit.valueCount(); ++i) {
                values.append(unit.value(i));
            }
            emit inputRegistersRead(unit.startAddress(), values);
        }
    } else {
        logError("Read response error: " + reply->errorString());
        emit errorOccurred(reply->errorString());
    }

    reply->deleteLater();
}
void PLCStationDriver::onWriteFinished() {
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

void PLCStationDriver::onStateChanged(QModbusDevice::State state) {
    if (state == QModbusDevice::ConnectedState) {
        emit connectionStatusChanged(true);
        emit logMessage("Connected to PLC via Modbus successfully.");
    } else if (state == QModbusDevice::UnconnectedState) {
        emit connectionStatusChanged(false);
        emit logMessage("Disconnected from PLC.");
        m_running = false;
    }
}

void PLCStationDriver::onErrorOccurred(QModbusDevice::Error error) {
    if (error == QModbusDevice::NoError || !m_modbusDevice)
        return;

    logError("Modbus error: " + m_modbusDevice->errorString());
    emit errorOccurred(m_modbusDevice->errorString());
}

void PLCStationDriver::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCStationDriver:" << message;
}
