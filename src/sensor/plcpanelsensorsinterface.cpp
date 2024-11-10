#include "include/sensor/plcpanelsensorsinterface.h"
#include <QModbusReply>
#include <QSerialPort>
#include <QVariant>
#include <QDebug>
#include <QMutexLocker>


#define DIGITAL_INPUTS_START_ADDRESS 0
#define ANALOG_INPUTS_START_ADDRESS 0
#define DIGITAL_OUTPUTS_START_ADDRESS 0

PLCPanelSensorInterface::PLCPanelSensorInterface(const QString &device,
                                                 int baudRate,
                                                 int slaveId,
                                                 QObject *parent)
    : QObject(parent),
    m_device(device),
    m_baudRate(baudRate),
    m_slaveId(slaveId),
    m_modbusDevice(new QModbusRtuSerialClient(this)),
    m_readTimer(new QTimer(this)),
    m_timeoutTimer(new QTimer(this)),
    m_gunState(false),
    m_reconnectAttempts(0)
{
    // Configure Modbus device
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_device);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m_baudRate);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);

    m_modbusDevice->setTimeout(500); // Increased timeout to 1 second
    m_modbusDevice->setNumberOfRetries(3);

    // Connect signals
    connect(m_modbusDevice, &QModbusClient::stateChanged, this, &PLCPanelSensorInterface::onStateChanged);
    connect(m_modbusDevice, &QModbusClient::errorOccurred, this, &PLCPanelSensorInterface::onErrorOccurred);

    connect(m_readTimer, &QTimer::timeout, this, &PLCPanelSensorInterface::readData);
    m_readTimer->setInterval(100); // Reduced read frequency to 500 ms

    connect(m_timeoutTimer, &QTimer::timeout, this, &PLCPanelSensorInterface::handleTimeout);
    m_timeoutTimer->setSingleShot(true);

}

PLCPanelSensorInterface::~PLCPanelSensorInterface() {
    disconnectDevice();
}

bool PLCPanelSensorInterface::connectDevice() {
    if (m_modbusDevice->state() != QModbusDevice::UnconnectedState) {
        m_modbusDevice->disconnectDevice();
    }

    if (!m_modbusDevice->connectDevice()) {
        logError(QString("Failed to connect to Panel Modbus device: %1").arg(m_modbusDevice->errorString()));
        emit connectionStatusChanged(false);
        return false;
    }

    logMessage("Attempting to connect to PLC Modbus device...");
    // Connection confirmation is handled asynchronously in onStateChanged()
    return true;
}

void PLCPanelSensorInterface::disconnectDevice() {
    if (m_modbusDevice->state() != QModbusDevice::UnconnectedState) {
        m_modbusDevice->disconnectDevice();
    }
    m_readTimer->stop();
    m_timeoutTimer->stop();
    emit connectionStatusChanged(false);
}

void PLCPanelSensorInterface::onStateChanged(QModbusDevice::State state) {
    if (state == QModbusDevice::ConnectedState) {
        logMessage("PLC Modbus connection established.");
        emit connectionStatusChanged(true);
        m_readTimer->start();
        m_reconnectAttempts = 0; // Reset reconnection attempts on success
    } else if (state == QModbusDevice::UnconnectedState) {
        logMessage("PLC Modbus device disconnected.");
        emit connectionStatusChanged(false);
        m_readTimer->stop();
    }
}

void PLCPanelSensorInterface::onErrorOccurred(QModbusDevice::Error error) {
    if (error == QModbusDevice::NoError)
        return;
    logError(QString("Modbus error: %1").arg(m_modbusDevice->errorString()));
    emit errorOccurred(m_modbusDevice->errorString());
}

void PLCPanelSensorInterface::readData() {
    if (!m_modbusDevice || m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return;

    // Read Digital Inputs
    {
        QMutexLocker locker(&m_mutex);

        int startAddress = DIGITAL_INPUTS_START_ADDRESS;
        int numberOfEntries = 13; // Number of digital inputs

        QModbusDataUnit readUnit(QModbusDataUnit::DiscreteInputs, startAddress, numberOfEntries);

        if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, m_slaveId)) {
            if (!reply->isFinished()) {
                connect(reply, &QModbusReply::finished, this, &PLCPanelSensorInterface::onDigitalInputsReadReady);
                if (!m_timeoutTimer->isActive())
                    m_timeoutTimer->start(1000);
            } else {
                reply->deleteLater();
            }
        } else {
            logError(QString("Read digital inputs error: %1").arg(m_modbusDevice->errorString()));
            emit errorOccurred(m_modbusDevice->errorString());
            emit connectionStatusChanged(false);
        }


    }

    // Read Analog Inputs
{
        QMutexLocker locker(&m_mutex);

        int startAddress = ANALOG_INPUTS_START_ADDRESS;
        int numberOfEntries = 6; // Number of analog inputs

        QModbusDataUnit readUnit(QModbusDataUnit::InputRegisters, startAddress, numberOfEntries);

        if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, m_slaveId)) {
            if (!reply->isFinished()) {
                connect(reply, &QModbusReply::finished, this, &PLCPanelSensorInterface::onAnalogInputsReadReady);
                if (!m_timeoutTimer->isActive())
                    m_timeoutTimer->start(1000);
            } else {
                reply->deleteLater();
            }
        } else {
            logError(QString("Read analog inputs error: %1").arg(m_modbusDevice->errorString()));
            emit errorOccurred(m_modbusDevice->errorString());
            emit connectionStatusChanged(false);
        }
    }
}

void PLCPanelSensorInterface::onDigitalInputsReadReady() {
    auto *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (m_timeoutTimer->isActive())
        m_timeoutTimer->stop();

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        QVector<std::pair<int, bool>> signalsToEmit;

        {
            QMutexLocker locker(&m_mutex);
            m_digitalInputs.clear();
            for (uint i = 0; i < unit.valueCount(); ++i) {
                m_digitalInputs.append(unit.value(i));
            }

            int gunStateIndex = 8;
            int stationStateIndex = 9;

            int loadAmmunitionStateIndex = 0;
            int authorizeSwIndex = 1;
            int homeSwIndex = 2;
            int stabilizationSwIndex = 3;
            int cameraIndex = 4;
            int upSwIndex = 5;
            int downSwIndex = 6;
            int menuValSwIndex = 7;

            if (gunStateIndex < unit.valueCount()) {
                bool state = unit.value(gunStateIndex);
                if (m_digitalOutputs.size() <= 0) m_digitalOutputs.resize(2);
                if (m_digitalOutputs[0] != state){
                    m_digitalOutputs[0] = state;
                    signalsToEmit.emplace_back(0, state);
                }
            }

            if (loadAmmunitionStateIndex < unit.valueCount()) {
                bool state = unit.value(loadAmmunitionStateIndex);
                signalsToEmit.emplace_back(1, state);
            }
            if (stationStateIndex < unit.valueCount()) {
                bool state = unit.value(stationStateIndex);
                if (m_digitalOutputs.size() <= 1) m_digitalOutputs.resize(2);
                if (m_digitalOutputs[1] != state){
                    m_digitalOutputs[1] = state;
                    signalsToEmit.emplace_back(2, state);
                }
            }

            if (homeSwIndex < unit.valueCount()) {
                bool state = unit.value(homeSwIndex);
                signalsToEmit.emplace_back(3, state);
            }
            if (stabilizationSwIndex < unit.valueCount()) {
                bool state = unit.value(stabilizationSwIndex);
                signalsToEmit.emplace_back(4, state);
            }
            if (authorizeSwIndex < unit.valueCount()) {
                bool state = unit.value(authorizeSwIndex);
                signalsToEmit.emplace_back(5, state);
            }
            if (cameraIndex < unit.valueCount()) {
                bool state = unit.value(cameraIndex);
                signalsToEmit.emplace_back(6, state);
            }
            if (upSwIndex < unit.valueCount()) {
                bool state = unit.value(upSwIndex);
                signalsToEmit.emplace_back(7, state);
            }
            if (downSwIndex < unit.valueCount()) {
                bool state = unit.value(downSwIndex);
                signalsToEmit.emplace_back(8, state);
            }
            if (menuValSwIndex < unit.valueCount()) {
                bool state = unit.value(menuValSwIndex);
                signalsToEmit.emplace_back(9, state);
            }
            emit connectionStatusChanged(true);
        }

        // Emit signals outside the mutex lock
        for (const auto &signal : signalsToEmit) {
            switch (signal.first) {
            case 0:
                emit gunStateChanged(signal.second);
                break;
            case 1:
                emit loadAmmunitionStateChanged(signal.second);
                break;
            case 2:
                emit stationStateChanged(signal.second);
                break;
            case 3:
                emit homeSwChanged(signal.second);
                break;
            case 4:
                emit stabilizationSwChanged(signal.second);
                break;
            case 5:
                emit authorizeSwChanged(signal.second);
                break;
            case 6:
                emit camSwChanged(signal.second);
                break;
            case 7:
                emit upSwChanged(signal.second);
                break;
            case 8:
                emit downSwChanged(signal.second);
                break;
            case 9:
                emit menuValSwChanged(signal.second);
                break;
            default:
                break;
            }
        }

    } else {
        logError(QString("Read digital inputs response error: %1").arg(reply->errorString()));
        emit errorOccurred(reply->errorString());
        emit connectionStatusChanged(false);
    }

    reply->deleteLater();
}


void PLCPanelSensorInterface::onAnalogInputsReadReady() {
    auto *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    // Stop the timeout timer as a response has been received
    if (m_timeoutTimer->isActive())
        m_timeoutTimer->stop();

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        QMutexLocker locker(&m_mutex);

        m_analogInputs.clear();
        for (uint i = 0; i < unit.valueCount(); ++i) {
            m_analogInputs.append(unit.value(i));
        }
        int fireModeStateInputIndex = 0;
        int speedSwIndex = 1;
        int panelTemperatureIndex = 2;

        // Adjust based on actual address mapping
        if (fireModeStateInputIndex < unit.valueCount()) {
            int mode = unit.value(fireModeStateInputIndex);
            // Assuming fire mode is represented by multiple bits or a specific pattern
            //int mode = state ? 1 : 0; // Adjust based on actual encoding
            emit fireModeStateInputChanged(mode);
        }
        if (speedSwIndex < unit.valueCount()) {
            int speed = unit.value(speedSwIndex);
            emit speedSwChanged(speed);
        }
        if (panelTemperatureIndex < unit.valueCount()) {
            // Assuming temperature is scaled by 10, adjust as necessary
            int temperature = static_cast<int>(unit.value(panelTemperatureIndex));
            emit panelTemperatureChanged(temperature);
        }


        emit connectionStatusChanged(true);

    } else {
        logError(QString("Read analog inputs response error: %1").arg(reply->errorString()));
        emit errorOccurred(reply->errorString());
        emit connectionStatusChanged(false);
    }

    reply->deleteLater();
}


void PLCPanelSensorInterface::writeData() {
    if (!m_modbusDevice || m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return;

    QMutexLocker locker(&m_mutex);

    // Prepare 8 digital outputs (coils)
    QVector<quint16> coilValues;
    for (int i = 0; i < m_digitalOutputs.size() && i < 8; ++i) {
        coilValues.append(m_digitalOutputs.at(i));

    }

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, DIGITAL_OUTPUTS_START_ADDRESS, coilValues.size());
    for (int i = 0; i < coilValues.size(); ++i) {
        writeUnit.setValue(i, coilValues.at(i));
    }

    if (auto *reply = m_modbusDevice->sendWriteRequest(writeUnit, m_slaveId)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &PLCPanelSensorInterface::onWriteReady);
        } else {
            reply->deleteLater();
        }
    } else {
        logError(QString("Write error: %1").arg(m_modbusDevice->errorString()));
        emit errorOccurred(m_modbusDevice->errorString());
    }
}

void PLCPanelSensorInterface::onWriteReady() {
    auto *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() != QModbusDevice::NoError) {
        logError(QString("Write response error: %1").arg(reply->errorString()));
        emit errorOccurred(reply->errorString());
    } else {
        emit logMessage("Write to PLC completed successfully.");
    }

    reply->deleteLater();
}

void PLCPanelSensorInterface::handleTimeout() {
    logError("Timeout waiting for response from PLC.");
    emit errorOccurred("Timeout waiting for response from PLC.");

    if (m_reconnectAttempts >= MAX_RECONNECT_ATTEMPTS) {
        logError("Maximum reconnection attempts reached. Stopping reconnection attempts.");
        emit maxReconnectionAttemptsReached(); // You need to define this signal
        return;
    }

    m_reconnectAttempts++;
    int delay = BASE_RECONNECT_DELAY_MS * qPow(2, m_reconnectAttempts - 1); // Exponential backoff

    logMessage(QString("Attempting to reconnect... (Attempt %1, Delay %2 ms)").arg(m_reconnectAttempts).arg(delay));

    if (m_modbusDevice) {
        m_modbusDevice->disconnectDevice();
        QTimer::singleShot(delay, this, &PLCPanelSensorInterface::connectDevice);
    }
}


void PLCPanelSensorInterface::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCPanelSensorInterface:" << message;
}

// Getters and setters for digital inputs
QVector<bool> PLCPanelSensorInterface::digitalInputs() const {
    QMutexLocker locker(const_cast<QMutex*>(&m_mutex)); // Use const_cast here
    return m_digitalInputs;
}

// Getters and setters for analog inputs
QVector<uint16_t> PLCPanelSensorInterface::analogInputs() const {
    QMutexLocker locker(const_cast<QMutex*>(&m_mutex)); // Use const_cast here
    return m_analogInputs;
}

// Set digital outputs
void PLCPanelSensorInterface::setDigitalOutputs(const QVector<bool> &outputs) {
    {
        QMutexLocker locker(&m_mutex);
        m_digitalOutputs = outputs;
    }
    writeData();
}
