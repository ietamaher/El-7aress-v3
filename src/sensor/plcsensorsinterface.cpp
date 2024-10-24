#include "include/sensor/plcsensorsinterface.h"
#include <QDebug>

PLCSensorInterface::PLCSensorInterface(PLCModbusCommunication *modbusComm, QObject *parent)
    : QObject(parent),
    m_modbusComm(modbusComm),
    m_readTimer(new QTimer(this))
{
    connect(m_readTimer, &QTimer::timeout, this, &PLCSensorInterface::readSensors);
    connect(m_modbusComm, &PLCModbusCommunication::logMessage, this, &PLCSensorInterface::logMessage);
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
    // Read proximity sensor
    QVector<uint16_t> values;
    if (m_modbusComm->readRegisters(PROXIMITY_SENSOR_ADDRESS, 1, values)) {
        bool state = values[0] != 0;
        emit proximitySensorActivated(state);
    } else {
        logError("Failed to read proximity sensor");
    }

    // Read temperature sensor
    if (m_modbusComm->readRegisters(TEMPERATURE_SENSOR_ADDRESS, 1, values)) {
        uint16_t rawValue = values[0];
        double temperature = rawValue / 10.0; // Adjust scaling as needed
        emit temperatureUpdated(temperature);
    } else {
        logError("Failed to read temperature sensor");
    }

    // Read pressure sensor
    if (m_modbusComm->readRegisters(PRESSURE_SENSOR_ADDRESS, 1, values)) {
        uint16_t rawValue = values[0];
        double pressure = rawValue / 100.0; // Adjust scaling as needed
        emit pressureUpdated(pressure);
    } else {
        logError("Failed to read pressure sensor");
    }
}

void PLCSensorInterface::logError(const QString &message) {
    emit logMessage(message);
    qWarning() << "PLCSensorInterface:" << message;
}
