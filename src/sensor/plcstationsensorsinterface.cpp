#include "include/sensor/plcstationsensorsinterface.h"
#include <QDebug>

PLCStationSensorInterface::PLCStationSensorInterface(PLCStationDriver *modbusComm, QObject *parent)
    : QObject(parent),
    m_modbusComm(modbusComm)
{
    initializeSensorConfigs();

    connect(m_modbusComm, &PLCStationDriver::logMessage, this, &PLCStationSensorInterface::logMessage);
    connect(m_modbusComm, &PLCStationDriver::inputBitsRead, this, &PLCStationSensorInterface::onInputBitsRead);
    connect(m_modbusComm, &PLCStationDriver::inputRegistersRead, this, &PLCStationSensorInterface::onInputRegistersRead);
    connect(m_modbusComm, &PLCStationDriver::errorOccurred, this, &PLCStationSensorInterface::onErrorOccurred);
}

void PLCStationSensorInterface::onInputBitsRead(int address, const QVector<uint8_t> &bits) {
    // Process digital inputs
    // For example, if proximity sensor is at address 0
     int upperSensorIndex = 0;
    int lowerSensorIndex = 1;
    int ammunitionLevelIndex = 2;
    int upSwIndex = 3;
    int downSwIndex = 4;
    int menuValSwIndex = 5;

    if (upperSensorIndex < bits.size()) {
        bool state = bits[upperSensorIndex];
        emit stationUpperSensorStateChanged(state);
    }
    if (lowerSensorIndex < bits.size()) {
        bool state = bits[lowerSensorIndex];
        emit stationLowerSensorStateChanged(state);
    }
    if (ammunitionLevelIndex < bits.size()) {
        bool state = bits[ammunitionLevelIndex];
        emit stationAmmunitionLevelChanged(state);
    }
    if (upSwIndex < bits.size()) {
        bool state = bits[upSwIndex];
        emit stationInput1Changed(state);
    }
    if (downSwIndex < bits.size()) {
        bool state = bits[downSwIndex];
        emit stationInput2Changed(state);
    }
    if (menuValSwIndex < bits.size()) {
        bool state = bits[menuValSwIndex];
        emit stationInput3Changed(state);
    }

}

void PLCStationSensorInterface::onInputRegistersRead(int address, const QVector<uint16_t> &values) {
    // Process analog inputs
    // For example, if temperature sensor is at address 100
    int eoTemperatureIndex = 0; // Adjust based on actual address
    int eoPressurereIndex = 1; // Adjust based on actual address

    if (eoTemperatureIndex < values.size()) {
        double temperature = values[eoTemperatureIndex] / 10.0; // Adjust scaling as needed
        emit eoTemperatureChanged(temperature);
    }
    if (eoPressurereIndex < values.size()) {
        double pressure = values[eoPressurereIndex] / 10.0; // Adjust scaling as needed
        emit eoPressureChanged(pressure);
    }}

void PLCStationSensorInterface::onErrorOccurred(const QString &message) {
    logError(message);
}

// Initialize Sensor Configurations (if needed)
void PLCStationSensorInterface::initializeSensorConfigs() {
    // If you prefer to use configurations
}

void PLCStationSensorInterface::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCStationSensorInterface:" << message;
}
