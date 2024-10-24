#include "include/gimbal/manualmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/gimbal/gimbalmotordriver.h"
#include <QDebug>

ManualMotionMode::ManualMotionMode(QObject *parent)
    : QObject(parent),
    m_azimuth(0.0),
    m_elevation(0.0)
{
}

void ManualMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Manual Motion Mode";
    // Initialize positions
    m_azimuth = controller->getGimbalMotorDriver()->getAzimuthPosition();
    m_elevation = controller->getGimbalMotorDriver()->getElevationPosition();
}

void ManualMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Manual Motion Mode";
}

void ManualMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value) {
    // Adjust positions based on joystick input
    const double sensitivity = 0.1; // Adjust as needed

    if (axis == 0) { // Assuming axis 0 is azimuth
        m_azimuth += value * sensitivity;
    } else if (axis == 1) { // Assuming axis 1 is elevation
        m_elevation += value * sensitivity;
    }
}

void ManualMotionMode::update(GimbalController* controller) {
    // Send position commands
    controller->getGimbalMotorDriver()->sendPositionCommand(m_azimuth, m_elevation);

   /* double azimuthCommand = ...; // Calculate desired azimuth
    double elevationCommand = ...; // Calculate desired elevation

    // Convert to pulses and directions as needed
    int azimuthPulse = ...;
    bool azimuthDirection = ...;
    int elevationPulse = ...;
    bool elevationDirection = ...;

    // Send commands using PLCServoInterface
    controller->getPLCServoInterface()->setAzimuthPulse(azimuthPulse);
    controller->getPLCServoInterface()->setAzimuthDirection(azimuthDirection);
    controller->getPLCServoInterface()->setElevationPulse(elevationPulse);
    controller->getPLCServoInterface()->setElevationDirection(elevationDirection);   */

}
