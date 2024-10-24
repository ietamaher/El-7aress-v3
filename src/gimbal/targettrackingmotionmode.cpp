#include "include/gimbal/targettrackingmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/camera/camerasystem.h"
#include "include/gimbal/gimbalmotordriver.h"
#include <QDebug>

void TargetTrackingMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Target Tracking Motion Mode";
    // Connect to target position updates from CameraSystem
    CameraSystem* cameraSystem = controller->getCameraSystem();
    if (cameraSystem) {
        connect(cameraSystem, &CameraSystem::targetPositionUpdated,
                this, &TargetTrackingMotionMode::onTargetPositionUpdated);
    }
}

void TargetTrackingMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Target Tracking Motion Mode";
    // Disconnect from CameraSystem signals
    CameraSystem* cameraSystem = controller->getCameraSystem();
    if (cameraSystem) {
        disconnect(cameraSystem, &CameraSystem::targetPositionUpdated,
                   this, &TargetTrackingMotionMode::onTargetPositionUpdated);
    }
}

void TargetTrackingMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value) {
    // Optionally adjust tracking parameters based on joystick input
}

void TargetTrackingMotionMode::update(GimbalController* controller) {
    // Use the latest target position to calculate motor commands
    controller->getGimbalMotorDriver()->sendPositionCommand(m_targetAzimuth, m_targetElevation);
}

void TargetTrackingMotionMode::onTargetPositionUpdated(double azimuth, double elevation) {
    m_targetAzimuth = azimuth;
    m_targetElevation = elevation;
}
