#include "include/weapon/weaponsystem.h"
#include <QDebug>

WeaponSystem::WeaponSystem(DataModel *dataModel, QObject *parent)
    : QObject(parent),
      m_dataModel(dataModel),
      m_armed(true),
      m_prepared(false),
      m_servoActuatorInterface(new ServoActuatorInterface(this)),
      m_plcSolenoidInterface(nullptr)

{
    // Initialize the serial port for the servo actuator
    if (m_servoActuatorInterface->openSerialPort("/dev/pts/23")) {
        setServoInterface(m_servoActuatorInterface);
    } else {
       qDebug() << "Failed to open m_servoActuatorserial port";
        // Handle failure
    }

}

WeaponSystem::~WeaponSystem() {
    // Clean up...
}

void WeaponSystem::setServoInterface(ServoActuatorInterface *servoInterface) {
    if (m_servoActuatorInterface) {
        disconnect(m_servoActuatorInterface, nullptr, this, nullptr);
    }
    m_servoActuatorInterface = servoInterface;
    if (m_servoActuatorInterface) {
        //connect(m_radarInterface, &RadarInterface::targetUpdated, this, &SensorSystem::onRadarDataReceived);
        connect(m_servoActuatorInterface, &ServoActuatorInterface::errorOccurred, this, &WeaponSystem::handleErrorOccurred);
        connect(m_servoActuatorInterface, &ServoActuatorInterface::statusChanged, this, &WeaponSystem::handleActuatorStatusChanged);

        // Connect signals from the servo actuator
        connect(m_servoActuatorInterface, &ServoActuatorInterface::positionReached,
                this, [](int position) {
                    qDebug() << "Actuator reached position:" << position;
                    // Handle position reached
                });

        connect(m_servoActuatorInterface, &ServoActuatorInterface::alarmDetected,
                this, [](const QString &alarmMessage) {
                   qDebug() << "Actuator alarm detected:" << alarmMessage;
                    // Handle alarm
                });
    }
}

void WeaponSystem::handleActuatorStatusChanged(bool connected){
    emit actuatorStatusChanged(connected);
}

void WeaponSystem::handleErrorOccurred(const QString &error) {
    // Optionally process the error before emitting
    qDebug() << "SensorSystem received errorOccurred:" << error;
    emit errorOccurred(error);
}

void WeaponSystem::setPLCSolenoidInterface(PLCSolenoidInterface *solenoidInterface) {
    m_plcSolenoidInterface = solenoidInterface;
}

void WeaponSystem::startFiring(int frequency) {
    if (m_armed && m_plcSolenoidInterface) {
        m_plcSolenoidInterface->startFiring(frequency);
    } else {
       qDebug() << "Weapon is not armed or solenoid interface is not set.";
    }
}

void WeaponSystem::stopFiring() {
    if (m_plcSolenoidInterface) {
        m_plcSolenoidInterface->stopFiring();
    }
}

ServoActuatorInterface* WeaponSystem::getServoActuatorInterface() const {
    return m_servoActuatorInterface;
}

void WeaponSystem::arm(bool arm) {
    m_armed = arm;
    if (m_armed) {
        // Arm weapon system
    } else {
        // Disarm weapon system
    }
}

void WeaponSystem::prepareToFire() {
    if (!m_armed)
        return;
    if (m_prepared)
        return;
    // Prepare weapon for firing
    m_prepared = true;
}

void WeaponSystem::fire() {
    if (!m_armed || !m_prepared)
        return;
    // Execute firing sequence
    m_prepared = false;
}

void WeaponSystem::cancelFire() {
    m_prepared = false;
    // Cancel firing process
}

void WeaponSystem::switchWeaponType() {
    if (!m_armed)
        return;
    // Switch between weapon types
}

bool WeaponSystem::isArmed() const {
    return m_armed;
}
