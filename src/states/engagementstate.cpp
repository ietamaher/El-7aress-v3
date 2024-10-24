#include "include/states/engagementstate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/manualmotionmode.h"
#include <QDebug>

void EngagementState::enter(StateManager* manager) {
    qDebug() << "Entering Engagement Mode";
    if (manager->getWeaponSystem()) manager->getWeaponSystem()->arm(true);
    if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(new ManualMotionMode());
    }
    //if (manager->getSensorSystem()) manager->getSensorSystem()->activateEngagementSensors(true);
    if (manager->getCameraSystem()) {
        manager->getCameraSystem()->start();
        manager->getCameraSystem()->setProcessingMode(CameraSystem::ManualTrackingMode);
    }
}

void EngagementState::exit(StateManager* manager) {
    qDebug() << "Exiting Engagement Mode";
    if (manager->getWeaponSystem()) manager->getWeaponSystem()->arm(false);
    if (manager->getGimbalController()) manager->getGimbalController()->enableManualControl(false);
    //if (manager->getSensorSystem()) manager->getSensorSystem()->activateEngagementSensors(false);
}
