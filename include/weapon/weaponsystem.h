#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

#include <QObject>
#include "servoactuatorinterface.h"
#include "plcsolenoidinterface.h"

class WeaponSystem : public QObject {
    Q_OBJECT
public:
    explicit WeaponSystem(QObject *parent = nullptr);
    ~WeaponSystem();

    void arm(bool arm);
    void prepareToFire();
    void fire();
    void cancelFire();
    void switchWeaponType();

    bool isArmed() const;
    ServoActuatorInterface* getServoActuatorInterface() const;
    void setPLCSolenoidInterface(PLCSolenoidInterface *solenoidInterface);

    void startFiring(int frequency);
    void stopFiring();

signals:
    void armedStatusChanged(bool armed);

private:
    bool m_armed;
    bool m_prepared;
    ServoActuatorInterface *m_servoActuatorInterface;
    PLCSolenoidInterface *m_plcSolenoidInterface;
};

#endif // WEAPONSYSTEM_H
