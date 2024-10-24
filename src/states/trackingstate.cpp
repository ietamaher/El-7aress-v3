#include "include/states/trackingstate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/targettrackingmotionmode.h"
#include "include/gimbal/radartrackingmotionmode.h"
#include <QDebug>

void TrackingState::enter(StateManager* manager) {
    qDebug() << "Entering Tracking Mode";
    if (manager->getGimbalController()) {
        if (manager->isRadarModeEnabled()) {
            manager->getGimbalController()->setMotionMode(new RadarTrackingMotionMode());
        } else {
            manager->getGimbalController()->setMotionMode(new TargetTrackingMotionMode());
        }
    }
    if (manager->getCameraSystem()) {
        manager->getCameraSystem()->start();
        manager->getCameraSystem()->setProcessingMode(CameraSystem::TrackingMode);
    }
}

void TrackingState::exit(StateManager* manager) {
    qDebug() << "Exiting Tracking Mode";
    //if (manager->getGimbalController()) manager->getGimbalController()->enableAutoTracking(false);
    //if (manager->getSensorSystem()) manager->getSensorSystem()->activateTrackingSensors(false);
}
