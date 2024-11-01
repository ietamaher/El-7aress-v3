#include "include/states/emergencyoverridestate.h".h"
#include "include/states/statemanager.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/camera/camerasystem.h"

#include <QDebug>

void EmergencyOverrideState::enter(StateManager* manager) {
    qDebug() << "Entering System Error State";

    // Disable critical systems
    if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(MotionModeType::None);
    }

    if (manager->getCameraSystem()) {
        manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::IdleMode);
        manager->getCameraSystem()->shutdown();
    }

    // Additional safety measures
    if (manager->getWeaponSystem()) {
        manager->getWeaponSystem()->arm(false);
    }

    // Notify operator via GUI
    //emit manager->communicationSystem()->notifyOperator("System Error Occurred. Entering Safe Mode.");
}

void EmergencyOverrideState::exit(StateManager* manager, OperationalMode nextMode) {
    qDebug() << "Exiting Emergency OverrideState";
    // Reset systems or prepare for recovery
}
