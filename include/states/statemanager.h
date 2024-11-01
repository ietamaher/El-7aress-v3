#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QObject>
#include "operationalstate.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/camera/camerasystem.h"
#include "include/weapon/weaponsystem.h"
#include "include/sensor/sensorsystem.h"

#include "include/states/idlestate.h"
#include "include/states/surveillancestate.h"
#include "include/states/trackingstate.h"
#include "include/states/engagementstate.h"
#include "include/states/emergencyoverridestate.h"
#include "include/states/systemerrorstate.h"

class OperationalState;
class GimbalController;
class CameraSystem;
class WeaponSystem;
class SensorSystem;

class StateManager : public QObject {
    Q_OBJECT
public:
    explicit StateManager(QObject *parent = nullptr);
    ~StateManager();

    OperationalMode currentMode() const;

    void setMode(OperationalMode mode, bool isManualTracking = false);


    // Setter methods
    /*void setGimbalController(GimbalController *controller);
    void setCameraSystem(CameraSystem *cameraSystem);
    void setWeaponSystem(WeaponSystem *weaponSystem);
    void setSensorSystem(SensorSystem *sensorSystem);*/

    // Getter methods
    GimbalController* getGimbalController() const;
    CameraSystem* getCameraSystem() const;
    WeaponSystem* getWeaponSystem() const;
    SensorSystem* getSensorSystem() const;
    OperationalState* getCurrentState() const;
    TrackingState* getTrackingState() const;

public slots:
    void handleSystemError(const QString &error);
    void requestMotionModeChange(MotionModeType modeType); // New slot for motion mode changes

signals:
     void modeChanged(OperationalMode mode);
     void motionModeChanged(MotionModeType modeType); // New signal for motion mode changes



private:
    OperationalState* createState(OperationalMode mode, bool isManualTracking = false);

    std::unique_ptr<OperationalState> m_currentState;

    GimbalController* m_gimbalController;
    CameraSystem* m_cameraSystem;
    WeaponSystem* m_weaponSystem;
    SensorSystem* m_sensorSystem;

    TrackingState* m_trackingState = nullptr;
};

#endif // STATEMANAGER_H


