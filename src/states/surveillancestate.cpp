#include "include/states/surveillancestate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/patternmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/camera/camerasystem.h"
#include <QDebug>

void SurveillanceState::enter(StateManager* mgr) {
    qDebug() << "Entering Surveillance Mode";
    manager = mgr;

    // Set default motion mode to Pattern
    if (manager->getGimbalController()) {
        manager->getGimbalController()->setMotionMode(MotionModeType::Manual); // Correct usage
    }

    // Start Camera System but keep processing mode as per detectionEnabled
    if (manager->getCameraSystem()) {
        //manager->getCameraSystem()->start();
        setDetectionEnabled(detectionEnabled);
    }
}

void SurveillanceState::exit(StateManager* mgr, OperationalMode nextMode) {
    qDebug() << "Exiting Surveillance Mode";

    // If transitioning to Tracking, keep camera and gimbal running
    if (nextMode == OperationalMode::Tracking) {
        // Do not stop the camera or reset the gimbal
    } else {
        // Stop Camera System
        if (manager->getCameraSystem()) {
           // manager->getCameraSystem()->shutdown(); // Or use stop()
           // May be  I'll set Pipeline to NULL if i need to Turn video OFF
        }

        // Reset Gimbal Motion Mode
        if (manager->getGimbalController()) {
            manager->getGimbalController()->setMotionMode(MotionModeType::None);
        }
    }
}

void SurveillanceState::setMotionMode(MotionModeType modeType) {
    // Validate that the modeType is allowed within Surveillance State
    if (modeType == MotionModeType::Manual ||
        modeType == MotionModeType::Pattern ||
        modeType == MotionModeType::Radar) {

        if (manager && manager->getGimbalController()) {
            manager->getGimbalController()->setMotionMode(modeType);
            qDebug() << "SurveillanceState: Motion mode changed to" << static_cast<int>(modeType);
        }
    } else {
        qWarning() << "SurveillanceState: Invalid MotionModeType requested:" << static_cast<int>(modeType);
    }
}


void SurveillanceState::setDetectionEnabled(bool enabled) {
    detectionEnabled = enabled;
    if (manager->getCameraSystem()) {
        if (enabled) {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::DetectionMode);
        } else {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::IdleMode);
        }
    }
}


