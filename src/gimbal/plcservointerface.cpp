#include "include/gimbal/plcservointerface.h"
#include <QDebug>

PLCServoInterface::PLCServoInterface(PLCStationDriver *modbusWorker, QObject *parent)
    : QObject(parent),
    m_modbusWorker(modbusWorker)
{
    connect(m_modbusWorker, &PLCStationDriver::logMessage, this, &PLCServoInterface::logMessage);
    connect(m_modbusWorker, &PLCStationDriver::writeCompleted, this, &PLCServoInterface::onWriteCompleted);
    connect(m_modbusWorker, &PLCStationDriver::errorOccurred, this, &PLCServoInterface::onErrorOccurred);
}

void PLCServoInterface::setServoParameters(int azimuthPulse, bool azimuthDirection, int elevationPulse, bool elevationDirection) {
    m_azimuthPulse = static_cast<uint16_t>(azimuthPulse);
    m_azimuthDirection = azimuthDirection ? 1 : 0;
    m_elevationPulse = static_cast<uint16_t>(elevationPulse);
    m_elevationDirection = elevationDirection ? 1 : 0;
}

void PLCServoInterface::sendServoParameters() {
    int serverAddress = 2; // Set your Modbus server address (slave ID)

    // Prepare the values to write
    QVector<uint16_t> values = {
        m_azimuthPulse,
        m_azimuthDirection,
        m_elevationPulse,
        m_elevationDirection
    };

    // Write multiple registers starting from AZIMUTH_PULSE_ADDRESS
    m_modbusWorker->writeRegisters(serverAddress, AZIMUTH_PULSE_ADDRESS, values);
}

void PLCServoInterface::onWriteCompleted(int address) {
    emit logMessage(QString("Write to address %1 completed successfully.").arg(address));
}

void PLCServoInterface::onErrorOccurred(const QString &message) {
    logError(message);
}

void PLCServoInterface::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCServoInterface:" << message;
}
