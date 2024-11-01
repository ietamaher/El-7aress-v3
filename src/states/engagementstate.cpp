#include "include/states/engagementstate.h"
#include "include/states/statemanager.h"
#include "include/gimbal/manualmotionmode.h"
#include <QDebug>

EngagementState::EngagementState()
    : manager(nullptr), m_previousMotionMode(MotionModeType::Manual)
{
}

void EngagementState::enter(StateManager* manager) {
    qDebug() << "Entering Engagement Mode";
    this->manager = manager;

    if (manager->getWeaponSystem()) {
        manager->getWeaponSystem()->arm(true);
    }

    if (manager->getGimbalController()) {
        // Get the current motion mode from the Gimbal Controller
        MotionModeType currentMode = manager->getGimbalController()->getCurrentMotionMode();

        // Store the previous motion mode
        m_previousMotionMode = currentMode;

        // Check if coming from Tracking State by checking the current motion mode
        if (currentMode == MotionModeType::ManualTracking || currentMode == MotionModeType::TargetTracking) {
            // Keep the same tracking motion mode
            manager->getGimbalController()->setMotionMode(currentMode);
        } else {
            // Coming from Surveillance or other state, set to Manual mode
            manager->getGimbalController()->setMotionMode(MotionModeType::Manual);

            // Disable detection if applicable
            if (manager->getCameraSystem()) {
                manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::IdleMode);
            }
        }
    }

    // Set Camera Processing Mode
    if (manager->getCameraSystem()) {
        MotionModeType currentMode = manager->getGimbalController()->getCurrentMotionMode();
        if (currentMode == MotionModeType::ManualTracking) {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::ManualTrackingMode);
        } else if (currentMode == MotionModeType::TargetTracking) {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::TrackingMode);
        } else {
            manager->getCameraSystem()->setProcessingMode(CameraSystem::ProcessMode::IdleMode);
        }
    }

    // Do not allow switching between motion modes in Engagement Mode
    // You can enforce this by overriding setMotionMode and ignoring calls
}

void EngagementState::exit(StateManager* manager, OperationalMode nextMode) {
    qDebug() << "Exiting Engagement Mode";

    if (manager->getWeaponSystem()) {
        manager->getWeaponSystem()->arm(false);
    }

    if (manager->getGimbalController()) {
        manager->getGimbalController()->enableManualControl(false);
    }

    // Optionally reset motion mode or perform other cleanup
}

void EngagementState::setMotionMode(MotionModeType modeType) {
    // Prevent changing motion modes in Engagement Mode
    qWarning() << "EngagementState: Motion mode change is not allowed during engagement.";
    // Optionally, you can notify the user or log this event
}
