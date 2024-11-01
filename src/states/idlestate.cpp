#include "include/states/idlestate.h"
#include "include/states/statemanager.h"
#include <QDebug>

void IdleState::enter(StateManager* manager) {
    qDebug() << "Entering Idle Mode";
    if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(MotionModeType::None); // No motion mode
    }
    if (manager->getCameraSystem()) {
        //manager->getCameraSystem()->shutdown();
        manager->getCameraSystem()->setProcessingMode(CameraSystem::IdleMode);
    }
    if (manager->getWeaponSystem()) manager->getWeaponSystem()->arm(false);
    //if (manager->getSensorSystem()) manager->getSensorSystem()->activateSensors(false);
}


void IdleState::exit(StateManager* manager, OperationalMode nextMode) {
    qDebug() << "Exiting Idle Mode";
    // Perform any cleanup if necessary
}
