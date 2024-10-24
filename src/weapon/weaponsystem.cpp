#include "include/weapon/weaponsystem.h"
#include <QDebug>

WeaponSystem::WeaponSystem(QObject *parent)
    : QObject(parent),
      m_armed(true),
      m_prepared(false),
      m_servoActuatorInterface(new ServoActuatorInterface(this)),
      m_plcSolenoidInterface(nullptr)

{
    // Initialize the serial port for the servo actuator
    QSerialPort *servoSerial = new QSerialPort(this);
    servoSerial->setPortName("/dev/ttyUSB2"); // Adjust the port name as needed
    servoSerial->setBaudRate(QSerialPort::Baud9600); // Adjust baud rate as needed
    servoSerial->setDataBits(QSerialPort::Data8);
    servoSerial->setParity(QSerialPort::NoParity);
    servoSerial->setStopBits(QSerialPort::OneStop);
    servoSerial->setFlowControl(QSerialPort::NoFlowControl);

    m_servoActuatorInterface->setSerialPort(servoSerial);

    // Connect signals from the servo actuator
    connect(m_servoActuatorInterface, &ServoActuatorInterface::positionReached,
            this, [](int position) {
                qDebug() << "Actuator reached position:" << position;
                // Handle position reached
            });

    connect(m_servoActuatorInterface, &ServoActuatorInterface::alarmDetected,
            this, [](const QString &alarmMessage) {
                qWarning() << "Actuator alarm detected:" << alarmMessage;
                // Handle alarm
            });
}

WeaponSystem::~WeaponSystem() {
    // Clean up...
}

void WeaponSystem::setPLCSolenoidInterface(PLCSolenoidInterface *solenoidInterface) {
    m_plcSolenoidInterface = solenoidInterface;
}

void WeaponSystem::startFiring(int frequency) {
    if (m_armed && m_plcSolenoidInterface) {
        m_plcSolenoidInterface->startFiring(frequency);
    } else {
        qWarning() << "Weapon is not armed or solenoid interface is not set.";
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
