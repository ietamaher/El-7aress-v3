#include "include/states/idlestate.h"
#include "include/states/statemanager.h"
#include <QDebug>

void IdleState::enter(StateManager* manager) {
    qDebug() << "Entering Idle Mode";
    if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(nullptr); // No motion mode
    }
    if (manager->getCameraSystem()) {
        manager->getCameraSystem()->start();
        manager->getCameraSystem()->setProcessingMode(CameraSystem::IdleMode);
    }
    if (manager->getWeaponSystem()) manager->getWeaponSystem()->arm(false);
    //if (manager->getSensorSystem()) manager->getSensorSystem()->activateSensors(false);
}


void IdleState::exit(StateManager* manager) {
    qDebug() << "Exiting Idle Mode";
    // Perform any cleanup if necessary
}
