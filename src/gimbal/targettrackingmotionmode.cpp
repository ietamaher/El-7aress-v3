#include "include/gimbal/targettrackingmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/camera/camerasystem.h"

#include <QDebug>

void TargetTrackingMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Target Tracking Motion Mode";
    CameraSystem* cameraSystem = controller->getCameraSystem();
    qDebug() << "CameraSystem instance in enter():" << cameraSystem;
    if (cameraSystem) {
        bool connected = connect(cameraSystem, &CameraSystem::targetPositionUpdated,
                                 this, &TargetTrackingMotionMode::onTargetPositionUpdated);
        qDebug() << "Connected targetPositionUpdated signal:" << connected;
    } else {
        qWarning() << "CameraSystem is null in TargetTrackingMotionMode::enter()";
    }
}

void TargetTrackingMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Target Tracking Motion Mode";
    CameraSystem* cameraSystem = controller->getCameraSystem();
    qDebug() << "CameraSystem instance in exit():" << cameraSystem;
    if (cameraSystem) {
        bool disconnected = disconnect(cameraSystem, &CameraSystem::targetPositionUpdated,
                                       this, &TargetTrackingMotionMode::onTargetPositionUpdated);
        qDebug() << "Disconnected targetPositionUpdated signal:" << disconnected;
    } else {
        qWarning() << "CameraSystem is null in TargetTrackingMotionMode::exit()";
    }
}

void TargetTrackingMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value) {
    // Optionally adjust tracking parameters based on joystick input
}

void TargetTrackingMotionMode::update(GimbalController* controller) {
    // Use the latest target position to calculate motor commands
    if (controller->getPLCServoInterface()) {
        // Set parameters
        controller->getPLCServoInterface()->setOperationMode(2); // Assuming 2 for Target Tracking mode
        //controller->getPLCServoInterface()->setAzimuthSpeed(/* Calculate speed based on target */);
        //controller->getPLCServoInterface()->setElevationSpeed(/* Calculate speed based on target */);
        controller->getPLCServoInterface()->setAzimuthDirection(m_targetAzimuth >= 0 ? 1 : 0);
        controller->getPLCServoInterface()->setElevationDirection(m_targetElevation >= 0 ? 1 : 0);
        controller->getPLCServoInterface()->setAzimuthTargetAngle(static_cast<uint16_t>(abs(m_targetAzimuth)));
        controller->getPLCServoInterface()->setElevationTargetAngle(static_cast<uint16_t>(abs(m_targetElevation)));

        // Send parameters to PLC
        controller->getPLCServoInterface()->sendParameters();
    }
}

void TargetTrackingMotionMode::onTargetPositionUpdated(double azimuth, double elevation) {
    m_targetAzimuth = azimuth;
    m_targetElevation = elevation;
}
