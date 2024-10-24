#include "include/weapon/plcsolenoidinterface.h"
#include <QDebug>

PLCSolenoidInterface::PLCSolenoidInterface(PLCModbusCommunication *modbusComm, QObject *parent)
    : QObject(parent),
    m_modbusComm(modbusComm),
    m_firingTimer(new QTimer(this))
{
    connect(m_firingTimer, &QTimer::timeout, this, &PLCSolenoidInterface::triggerSolenoid);
    connect(m_modbusComm, &PLCModbusCommunication::logMessage, this, &PLCSolenoidInterface::logMessage);
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
    if (!m_modbusComm->writeRegister(SOLENOID_CONTROL_ADDRESS, value)) {
        logError("Failed to trigger solenoid");
    }
    // Optionally reset the solenoid control if required by hardware
}

void PLCSolenoidInterface::logError(const QString &message) {
    emit logMessage(message);
    qWarning() << "PLCSolenoidInterface:" << message;
}

