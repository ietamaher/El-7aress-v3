#include "include/states/trackingstate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/targettrackingmotionmode.h"
#include "include/gimbal/radartrackingmotionmode.h"
#include <QDebug>


TrackingState::TrackingState(bool isManualTracking)
    : m_isManualTracking(isManualTracking)
{
}
void TrackingState::setManualTracking(bool manual) {
    m_isManualTracking = manual;
}

void TrackingState::enter(StateManager* mgr) {
    manager = mgr;
    qDebug() << "Entering Tracking Mode";

    // Set Gimbal Motion Mode
    if (manager->getGimbalController()) {
        if (m_isManualTracking) {
            manager->getGimbalController()->setMotionMode(MotionModeType::ManualTracking);
        } else {
            manager->getGimbalController()->setMotionMode(MotionModeType::TargetTracking);
        }
    }

    // Set Camera Processing Mode
    if (manager->getCameraSystem()) {
        if (m_isManualTracking) {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::ManualTrackingMode);
        } else {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::TrackingMode);
            //manager->getCameraSystem()->startTracking(m_targetID);
        }

        // Connect targetLost signal
        //connect(manager->getCameraSystem(), &CameraSystem::targetLost, this, &TrackingState::onTargetLost);
    }
}


void TrackingState::exit(StateManager* manager, OperationalMode nextMode) {
    qDebug() << "Exiting Tracking Mode";

    // Disconnect signals
    if (manager->getCameraSystem()) {
       // disconnect(manager->getCameraSystem(), &CameraSystem::targetLost, this, &TrackingState::onTargetLost);
    }

    // Reset manual tracking flag
    m_isManualTracking = false;

}


void TrackingState::setMotionMode(MotionModeType modeType) {
    // Validate that the modeType is allowed within Surveillance State
    if (modeType == MotionModeType::TargetTracking ||
        modeType == MotionModeType::ManualTracking ) {

        if (manager && manager->getGimbalController()) {
            manager->getGimbalController()->setMotionMode(modeType);
            switch(modeType) {
            case MotionModeType::TargetTracking:
                manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::TrackingMode);
                break;
            case MotionModeType::ManualTracking:
                manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::ManualTrackingMode);
                break;
            }
            qDebug() << "TrackingState: Motion mode changed to" << static_cast<int>(modeType);
        }
    } else {
        qWarning() << "TrackingState: Invalid MotionModeType requested:" << static_cast<int>(modeType);
    }
}

void TrackingState::onEngageCommand() {
    // Request state change to Engagement Mode
    manager->setMode(OperationalMode::Engagement);
}

void TrackingState::onCancelTracking() {
    // Request state change back to Surveillance Mode
    manager->setMode(OperationalMode::Surveillance);
}

void TrackingState::onTargetLost() {
    // Notify operator and transition back to Surveillance Mode
    manager->setMode(OperationalMode::Surveillance);
}
