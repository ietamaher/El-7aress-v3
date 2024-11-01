#include "include/states/statemanager.h"


#include <QDebug>

#include <QDebug>

StateManager::StateManager(QObject *parent)
    : QObject(parent),
    m_currentState(nullptr),
    m_gimbalController(new GimbalController(this)),
    m_cameraSystem(new CameraSystem(this)),
    m_weaponSystem(new WeaponSystem(this)),
    m_sensorSystem(new SensorSystem(this))
{
    // Initialize to Idle state by default
    setMode(OperationalMode::Idle);
}

StateManager::~StateManager() {
    if (m_currentState) {
        m_currentState->exit(this, OperationalMode::Idle);
    }
}

OperationalMode StateManager::currentMode() const {
    if (m_currentState) {
        return m_currentState->getMode();
    }
    return OperationalMode::Idle;
}

OperationalState* StateManager::getCurrentState() const {
    return m_currentState.get();
}

TrackingState* StateManager::getTrackingState() const {
    return dynamic_cast<TrackingState*>(m_currentState.get());
}


OperationalState* StateManager::createState(OperationalMode mode, bool isManualTracking) {
    switch (mode) {
    case OperationalMode::Idle:
        return new IdleState();
    case OperationalMode::Surveillance:
        return new SurveillanceState();
    case OperationalMode::Tracking:
        m_trackingState = new TrackingState(isManualTracking);
        return m_trackingState;
    case OperationalMode::Engagement:
        return new EngagementState();
    case OperationalMode::EmergencyOverride:
        return new EmergencyOverrideState();
    case OperationalMode::SystemError:
        return new SystemErrorState();
    default:
        return nullptr;
    }
}


void StateManager::setMode(OperationalMode mode, bool isManualTracking) {
    if (m_currentState && m_currentState->getMode() == mode)
        return;
    OperationalMode previousMode = currentMode();
    if (m_currentState) {
        m_currentState->exit(this, mode);
    }

    m_currentState = std::unique_ptr<OperationalState>(createState(mode, isManualTracking));

    if (m_currentState) {
        m_currentState->enter(this);
        emit modeChanged(mode);
    }

    if (previousMode == OperationalMode::Tracking && mode != OperationalMode::Tracking) {
        m_trackingState = nullptr;
    }
}

/*void StateManager::setGimbalController(GimbalController *controller) {
    m_gimbalController = controller;
}

void StateManager::setCameraSystem(CameraSystem *cameraSystem) {
    m_cameraSystem = cameraSystem;
}

void StateManager::setWeaponSystem(WeaponSystem *weaponSystem) {
    m_weaponSystem = weaponSystem;
}

void StateManager::setSensorSystem(SensorSystem *sensorSystem) {
    m_sensorSystem = sensorSystem;
}*/

GimbalController* StateManager::getGimbalController() const {
    return m_gimbalController;
}

CameraSystem* StateManager::getCameraSystem() const {
    return m_cameraSystem;
}

WeaponSystem* StateManager::getWeaponSystem() const {
    return m_weaponSystem;
}

SensorSystem* StateManager::getSensorSystem() const {
    return m_sensorSystem;
}

void StateManager::handleSystemError(const QString &error) {
    qDebug() << "System Error:" << error;
    setMode(OperationalMode::SystemError);
}

void StateManager::requestMotionModeChange(MotionModeType modeType) {
    // Ensure that motion mode changes are only allowed in appropriate states
    if (currentMode() == OperationalMode::Surveillance) {
        if (m_currentState) {
            SurveillanceState* survState = dynamic_cast<SurveillanceState*>(m_currentState.get());
            if (survState) {
                survState->setMotionMode(modeType);
                //emit motionModeChanged(modeType);
            } else {
                qWarning() << "StateManager: Current state is Surveillance but casting failed.";
            }
        }
    } else     if (currentMode() == OperationalMode::Tracking) {
        if (m_currentState) {
            TrackingState* trckState = dynamic_cast<TrackingState*>(m_currentState.get());
            if (trckState) {
                trckState->setMotionMode(modeType);
                //emit motionModeChanged(modeType);
            } else {
                qWarning() << "StateManager: Current state is Tracking but casting failed.";
            }
        }
    }


    else {
        qWarning() << "StateManager: Motion mode change requested, but not in Surveillance Mode or Tracking Mode.";
    }
}
