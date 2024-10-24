#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QObject>
#include "operationalstate.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/camera/camerasystem.h"
#include "include/weapon/weaponsystem.h"
#include "include/sensor/sensorsystem.h"
#include "include/comm/communicationsystem.h"

class StateManager : public QObject {
    Q_OBJECT
public:
    explicit StateManager(QObject *parent = nullptr);

    OperationalMode currentMode() const;
    void setMode(OperationalMode mode);

    void setGimbalController(GimbalController *controller);
    void setCameraSystem(CameraSystem *cameraSystem);
    void setWeaponSystem(WeaponSystem *weaponSystem);
    void setSensorSystem(SensorSystem *sensorSystem);
    void setCommunicationSystem(CommunicationSystem *communicationSystem);

    GimbalController* getGimbalController() const;
    CameraSystem* getCameraSystem() const;
    WeaponSystem* getWeaponSystem() const;
    SensorSystem* getSensorSystem() const;
    CommunicationSystem* getCommunicationSystem() const;

    void enableRadarMode(bool enable);
    bool isRadarModeEnabled() const;

signals:
    void modeChanged(OperationalMode mode);
    void radarModeChanged(bool enabled);

private:
    OperationalState* m_currentState;
    GimbalController *m_gimbalController;
    CameraSystem *m_cameraSystem;
    WeaponSystem *m_weaponSystem;
    SensorSystem *m_sensorSystem;
    CommunicationSystem *m_communicationSystem;

    OperationalState* createState(OperationalMode mode);
    bool m_radarModeEnabled;

};

#endif // STATEMANAGER_H
