#include "include/gimbal/plcservointerface.h"
#include <QDebug>

PLCServoInterface::PLCServoInterface(PLCStationDriver *modbusWorker, QObject *parent)
    : QObject(parent),
    m_modbusWorker(modbusWorker),
    m_operationMode(0),
    m_elevationSpeed(0),
    m_azimuthSpeed(0),
    m_elevationDirection(0),
    m_azimuthDirection(0),
    m_elevationTargetAngle(0),
    m_azimuthTargetAngle(0)
{
    connect(m_modbusWorker, &PLCStationDriver::logMessage, this, &PLCServoInterface::logMessage);
    connect(m_modbusWorker, &PLCStationDriver::writeCompleted, this, &PLCServoInterface::onWriteCompleted);
    connect(m_modbusWorker, &PLCStationDriver::errorOccurred, this, &PLCServoInterface::onErrorOccurred);
}

// Setters
void PLCServoInterface::setOperationMode(uint16_t mode) {
    m_operationMode = mode;
}

void PLCServoInterface::setElevationSpeed(uint16_t speed) {
    m_elevationSpeed = speed;
}

void PLCServoInterface::setAzimuthSpeed(uint16_t speed) {
    m_azimuthSpeed = speed;
}

void PLCServoInterface::setElevationDirection(uint16_t direction) {
    m_elevationDirection = direction;
}

void PLCServoInterface::setAzimuthDirection(uint16_t direction) {
    m_azimuthDirection = direction;
}

void PLCServoInterface::setElevationTargetAngle(uint16_t angle) {
    m_elevationTargetAngle = angle;
}

void PLCServoInterface::setAzimuthTargetAngle(uint16_t angle) {
    m_azimuthTargetAngle = angle;
}

void PLCServoInterface::setActualAzimuth(uint16_t angle)
{
    m_actualAzimuthAngle = angle;
}

void PLCServoInterface::setActualElevation(uint16_t angle)
{
    m_actualElevationAngle = angle;
}

// Getters (if needed)
uint16_t PLCServoInterface::getOperationMode() {
    return m_operationMode;
}

uint16_t PLCServoInterface::getElevationTargetAngle()
{
    return m_actualElevationAngle;
}

uint16_t PLCServoInterface::getAzimuthTargetAngle()
{
    return m_actualAzimuthAngle;
}
// Send all parameters to PLC
void PLCServoInterface::sendParameters() {
    int serverAddress = 2; // Set your Modbus server address (slave ID)

    // Prepare the values to write in order
    QVector<uint16_t> values = {
        m_operationMode,
        m_elevationSpeed,
        m_azimuthSpeed,
        m_elevationDirection,
        m_azimuthDirection,
        m_elevationTargetAngle,
        m_azimuthTargetAngle,
        m_actualElevationAngle,
        m_actualAzimuthAngle
    };

    // Write multiple registers starting from HR_OPERATION_MODE
    m_modbusWorker->writeRegisters(serverAddress, HR_OPERATION_MODE, values);
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
