#include "include/gimbal/plcservointerface.h"
#include <QDebug>

PLCServoInterface::PLCServoInterface(PLCModbusWorker *modbusWorker, QObject *parent)
    : QObject(parent),
    m_modbusWorker(modbusWorker)
{
    connect(m_modbusWorker, &PLCModbusWorker::logMessage, this, &PLCServoInterface::logMessage);
    connect(m_modbusWorker, &PLCModbusWorker::writeCompleted, this, &PLCServoInterface::onWriteCompleted);
    connect(m_modbusWorker, &PLCModbusWorker::errorOccurred, this, &PLCServoInterface::onErrorOccurred);
}

void PLCServoInterface::setAzimuthPulse(int pulse) {
    uint16_t value = static_cast<uint16_t>(pulse);
    int address = AZIMUTH_PULSE_ADDRESS;
    m_pendingWrites.insert(address);

    int serverAddress = 2; // Set your Modbus server address (slave ID)
    m_modbusWorker->writeRegister(serverAddress, address, value);
}

void PLCServoInterface::setAzimuthDirection(bool direction) {
    uint16_t value = direction ? 1 : 0;
    int address = AZIMUTH_DIRECTION_ADDRESS;
    m_pendingWrites.insert(address);

    int serverAddress = 2;
    m_modbusWorker->writeRegister(serverAddress, address, value);
}


void PLCServoInterface::setElevationPulse(int pulse) {
    uint16_t value = static_cast<uint16_t>(pulse);
    int address = ELEVATION_PULSE_ADDRESS;
    m_pendingWrites.insert(address);
    int serverAddress = 2;
    m_modbusWorker->writeRegister(serverAddress, address, value);
}

void PLCServoInterface::setElevationDirection(bool direction) {
    uint16_t value = direction ? 1 : 0;
    int address = ELEVATION_DIRECTION_ADDRESS;
    m_pendingWrites.insert(address);
    int serverAddress = 2;
    m_modbusWorker->writeRegister(serverAddress, address, value);
}

void PLCServoInterface::onWriteCompleted(int address) {
    if (m_pendingWrites.contains(address)) {
        m_pendingWrites.remove(address);
        emit logMessage(QString("Write to address %1 completed successfully.").arg(address));
    }
}

void PLCServoInterface::onErrorOccurred(const QString &message) {
    logError(message);
}

void PLCServoInterface::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCServoInterface:" << message;
}

