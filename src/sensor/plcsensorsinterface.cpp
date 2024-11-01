#include "include/sensor/plcsensorsinterface.h"
#include <QDebug>


PLCSensorInterface::PLCSensorInterface(PLCModbusWorker *modbusComm, QObject *parent)
    : QObject(parent),
    m_modbusComm(modbusComm),
    m_readTimer(new QTimer(this))
{
    initializeSensorConfigs();

    connect(m_readTimer, &QTimer::timeout, this, &PLCSensorInterface::readSensors);
    connect(m_modbusComm, &PLCModbusWorker::logMessage, this, &PLCSensorInterface::logMessage);
    connect(m_modbusComm, &PLCModbusWorker::registersRead, this, &PLCSensorInterface::onRegistersRead);
    connect(m_modbusComm, &PLCModbusWorker::errorOccurred, this, &PLCSensorInterface::onErrorOccurred);


    // Initialize startAddress and totalRegisters based on m_sensorConfigs
    // Assuming m_sensorConfigs is populated elsewhere
    // Calculate startAddress and totalRegisters once
    if (!m_sensorConfigs.isEmpty()) {
        m_startAddress = m_sensorConfigs.first().address;
        uint16_t endAddress = m_startAddress + m_sensorConfigs.first().registerCount - 1;

        for (const auto &sensor : m_sensorConfigs) {
            uint16_t sensorStart = sensor.address;
            uint16_t sensorEnd = sensor.address + sensor.registerCount - 1;

            if (sensorStart < m_startAddress) {
                m_startAddress = sensorStart;
            }
            if (sensorEnd > endAddress) {
                endAddress = sensorEnd;
            }
        }

        m_totalRegisters = endAddress - m_startAddress + 1;
    } else {
        logError("No sensor configurations available.");
    }
}

void PLCSensorInterface::startMonitoring(int intervalMs) {
    m_readTimer->start(intervalMs);
    emit logMessage("Started sensor monitoring");
}

void PLCSensorInterface::stopMonitoring() {
    if (m_readTimer->isActive()) {
        m_readTimer->stop();
        emit logMessage("Stopped sensor monitoring");
    }
}

void PLCSensorInterface::readSensors() {
    if (m_sensorConfigs.isEmpty()) {
        logError("No sensor configurations available.");
        return;
    }

    // Issue asynchronous read
    int serverAddress = 2;
    m_modbusComm->readRegisters(serverAddress, m_startAddress, m_totalRegisters);
}

void PLCSensorInterface::onRegistersRead(int address, const QVector<uint16_t> &values) {
    if (address != m_startAddress) {
        // Not the data we requested
        return;
    }

    // Process data
    for (const auto &sensor : m_sensorConfigs) {
        int index = sensor.address - m_startAddress; // Calculate the index in the values vector
        if (index + sensor.registerCount <= values.size()) {
            sensor.processData(values, index);
        } else {
            logError(QString("Insufficient data received for %1.").arg(sensor.name));
        }
    }
}

void PLCSensorInterface::onErrorOccurred(const QString &message) {
    logError(message);
}


// Initialize Sensor Configurations
void PLCSensorInterface::initializeSensorConfigs() {
    // Proximity Sensor Configuration
    m_sensorConfigs.append(SensorConfig{
        "ProximitySensor",
        PROXIMITY_SENSOR_ADDRESS,
        1,
        [this](const QVector<uint16_t> &values, int index) {
            bool state = values[index] != 0;
            emit proximitySensorActivated(state);
        }
    });

    // Temperature Sensor Configuration
    m_sensorConfigs.append(SensorConfig{
        "TemperatureSensor",
        TEMPERATURE_SENSOR_ADDRESS,
        1,
        [this](const QVector<uint16_t> &values, int index) {
            double temperature = values[index] / 10.0; // Adjust scaling as needed
            emit temperatureUpdated(temperature);
        }
    });

    // Pressure Sensor Configuration
    m_sensorConfigs.append(SensorConfig{
        "PressureSensor",
        PRESSURE_SENSOR_ADDRESS,
        1,
        [this](const QVector<uint16_t> &values, int index) {
            double pressure = values[index] / 100.0; // Adjust scaling as needed
            emit pressureUpdated(pressure);
        }
    });

    // Add more sensors as needed
}

void PLCSensorInterface::logError(const QString &message) {
    emit logMessage(message);
   qDebug() << "PLCSensorInterface:" << message;
}
