#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

#include <QObject>
#include "servoactuatorinterface.h"
#include "plcsolenoidinterface.h"
#include "include/datamodel.h"

class WeaponSystem : public QObject {
    Q_OBJECT
public:
    explicit WeaponSystem(DataModel *dataModel, QObject *parent = nullptr);
    ~WeaponSystem();


    void setFireMode(int slaveId, int address, int mode);

    void arm(bool arm);
    void prepareToFire();
    void fire();
    void cancelFire();
    void switchWeaponType();

    bool isArmed() const;
    ServoActuatorInterface* getServoActuatorInterface() const;
    void setPLCSolenoidInterface(PLCSolenoidInterface *solenoidInterface);

    void startFiring();
    void stopFiring();

public slots:
    void handleActuatorStatusChanged(bool connected);
    void handleErrorOccurred(const QString &error);

signals:
    void errorOccurred(const QString &error);
    void armedStatusChanged(bool armed);
    void actuatorStatusChanged(bool connected);

private:
    bool m_armed;
    bool m_prepared;
    DataModel *m_dataModel;

    ServoActuatorInterface *m_servoActuatorInterface;
    PLCSolenoidInterface *m_plcSolenoidInterface;

    void setServoInterface(ServoActuatorInterface *servoInterface);
};

#endif // WEAPONSYSTEM_H
