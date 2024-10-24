#include "include/states/statemanager.h"
#include "include/states/idlestate.h"
#include "include/states/surveillancestate.h"
#include "include/states/detectionstate.h"
#include "include/states/trackingstate.h"
#include "include/states/engagementstate.h"
#include <QDebug>

StateManager::StateManager(QObject *parent)
    : QObject(parent),
    m_currentState(nullptr),
    m_gimbalController(nullptr),
    m_cameraSystem(nullptr),
    m_weaponSystem(nullptr),
    m_sensorSystem(nullptr),
    m_communicationSystem(nullptr),
    m_radarModeEnabled(false)
{
    // Initialize to Idle state by default
    setMode(OperationalMode::Idle);
}

OperationalMode StateManager::currentMode() const {
    if (m_currentState) {
        return m_currentState->getMode();
    }
    return OperationalMode::Idle;
}

void StateManager::setMode(OperationalMode mode) {
    if (m_currentState && m_currentState->getMode() == mode)
        return;

    if (m_currentState) {
        m_currentState->exit(this);
        delete m_currentState;
        m_currentState = nullptr;
    }

    m_currentState = createState(mode);
    if (m_currentState) {
        m_currentState->enter(this);
        emit modeChanged(mode);
    }
}

OperationalState* StateManager::createState(OperationalMode mode) {
    switch (mode) {
    case OperationalMode::Idle:
        return new IdleState();
    case OperationalMode::Surveillance:
        return new SurveillanceState();
    case OperationalMode::Detection:
        return new DetectionState();
    case OperationalMode::Tracking:
        return new TrackingState();
    case OperationalMode::Engagement:
        return new EngagementState();
    default:
        return nullptr;
    }
}

// Setter methods
void StateManager::setGimbalController(GimbalController *controller) {
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
}

void StateManager::setCommunicationSystem(CommunicationSystem *communicationSystem) {
    m_communicationSystem = communicationSystem;
}

// Getter methods
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

CommunicationSystem* StateManager::getCommunicationSystem() const {
    return m_communicationSystem;
}

void StateManager::enableRadarMode(bool enable) {
    if (m_radarModeEnabled == enable)
        return;

    m_radarModeEnabled = enable;
    emit radarModeChanged(enable);

    // If in TrackingState, update the motion mode
    if (currentMode() == OperationalMode::Tracking && m_gimbalController) {
        // Re-enter the current state to apply changes   !!!!! TODO
        m_currentState->exit(this);
        m_currentState->enter(this);
    }
}

bool StateManager::isRadarModeEnabled() const {
    return m_radarModeEnabled;
}
