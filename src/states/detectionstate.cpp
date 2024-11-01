#include "include/states/detectionstate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/patternmotionmode.h"
#include <QDebug>

void DetectionState::enter(StateManager* manager) {
    qDebug() << "Entering Detection Mode";
    /*if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(new PatternMotionMode());
    }*/
    if (manager->getCameraSystem()) {
        //manager->getCameraSystem()->start();
        manager->getCameraSystem()->setProcessingMode(CameraSystem::DetectionMode);
    }
}

void DetectionState::exit(StateManager* manager) {
    qDebug() << "Exiting Detection Mode";
    //if (manager->getSensorSystem()) manager->getSensorSystem()->activateSensors(false);
    //if (manager->getGimbalController()) manager->getGimbalController()->stopDetectionScan();
}
