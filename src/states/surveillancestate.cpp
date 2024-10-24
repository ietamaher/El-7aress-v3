#include "include/states/surveillancestate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/patternmotionmode.h"

#include <QDebug>

void SurveillanceState::enter(StateManager* manager) {
    qDebug() << "Entering Surveillance Mode";
    if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(new PatternMotionMode());
    }
    if (manager->getCameraSystem()) {
        manager->getCameraSystem()->start();
        manager->getCameraSystem()->setProcessingMode(CameraSystem::DetectionMode);
    }
}

void SurveillanceState::exit(StateManager* manager) {
    qDebug() << "Exiting Surveillance Mode";
    //if (manager->getGimbalController()) manager->getGimbalController()->stopAutoScan();
}
