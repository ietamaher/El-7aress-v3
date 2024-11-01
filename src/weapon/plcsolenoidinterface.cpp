#include "include/weapon/plcsolenoidinterface.h"
#include <QDebug>

PLCSolenoidInterface::PLCSolenoidInterface(PLCModbusWorker *modbusComm, QObject *parent)
    : QObject(parent),
    m_modbusComm(modbusComm),
    m_firingTimer(new QTimer(this))
{
    connect(m_firingTimer, &QTimer::timeout, this, &PLCSolenoidInterface::triggerSolenoid);
    connect(m_modbusComm, &PLCModbusWorker::logMessage, this, &PLCSolenoidInterface::logMessage);
    connect(m_modbusComm, &PLCModbusWorker::writeCompleted, this, &PLCSolenoidInterface::onWriteCompleted);
    connect(m_modbusComm, &PLCModbusWorker::errorOccurred, this, &PLCSolenoidInterface::onErrorOccurred);
}

void PLCSolenoidInterface::startFiring(int frequency) {
    if (frequency <= 0) {
        logError("Invalid firing frequency");
        return;
    }

    int interval = 1000 / frequency; // Calculate interval in milliseconds
    m_firingTimer->start(interval);
    emit logMessage(QString("Started firing at %1 Hz").arg(frequency));
}

void PLCSolenoidInterface::stopFiring() {
    if (m_firingTimer->isActive()) {
        m_firingTimer->stop();
        emit logMessage("Stopped firing");
    }
}

void PLCSolenoidInterface::triggerSolenoid() {
    // Send command to trigger solenoid
    uint16_t value = 1; // Assuming 1 triggers the solenoid
    int address = SOLENOID_CONTROL_ADDRESS;
    m_pendingWrites.insert(address);
    int serverAddress = 2;
    m_modbusComm->writeRegister(serverAddress, address, value);
    // Optionally reset the solenoid control if required by hardware
}

void PLCSolenoidInterface::onWriteCompleted(int address) {
    if (m_pendingWrites.contains(address)) {
        m_pendingWrites.remove(address);
        emit logMessage(QString("Solenoid at address %1 triggered successfully.").arg(address));
    }
}

void PLCSolenoidInterface::onErrorOccurred(const QString &message) {
    logError(message);
}

void PLCSolenoidInterface::logError(const QString &message) {
    emit logMessage(message);
    qDebug() << "PLCSolenoidInterface:" << message;
}
