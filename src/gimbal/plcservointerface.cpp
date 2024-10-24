#include "include/gimbal/plcservointerface.h"
#include <QDebug>

PLCServoInterface::PLCServoInterface(PLCModbusCommunication *modbusComm, QObject *parent)
    : QObject(parent),
    m_modbusComm(modbusComm)
{
    // Connect log messages
    connect(m_modbusComm, &PLCModbusCommunication::logMessage, this, &PLCServoInterface::logMessage);
}

void PLCServoInterface::setAzimuthPulse(int pulse) {
    uint16_t value = static_cast<uint16_t>(pulse);
    if (!m_modbusComm->writeRegister(AZIMUTH_PULSE_ADDRESS, value)) {
        logError("Failed to set azimuth pulse");
    }
}

void PLCServoInterface::setAzimuthDirection(bool direction) {
    uint16_t value = direction ? 1 : 0;
    if (!m_modbusComm->writeRegister(AZIMUTH_DIRECTION_ADDRESS, value)) {
        logError("Failed to set azimuth direction");
    }
}

void PLCServoInterface::setElevationPulse(int pulse) {
    uint16_t value = static_cast<uint16_t>(pulse);
    if (!m_modbusComm->writeRegister(ELEVATION_PULSE_ADDRESS, value)) {
        logError("Failed to set elevation pulse");
    }
}

void PLCServoInterface::setElevationDirection(bool direction) {
    uint16_t value = direction ? 1 : 0;
    if (!m_modbusComm->writeRegister(ELEVATION_DIRECTION_ADDRESS, value)) {
        logError("Failed to set elevation direction");
    }
}

void PLCServoInterface::logError(const QString &message) {
    emit logMessage(message);
    qWarning() << "PLCServoInterface:" << message;
}

