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
    m_azimuth = controller->getAzimuthPosition();
    m_elevation = controller->getElevationPosition();
}

void ManualMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Manual Motion Mode";
}

void ManualMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value)
{
    // Store the joystick input values
    if (axis == 0) { // Azimuth axis
        m_azimuthInput = value;
    } else if (axis == 1) { // Elevation axis
        m_elevationInput = value;
    }
}

void ManualMotionMode::update(GimbalController* controller)
{
    // Define sensitivity or maximum speed
    const float maxSpeed = 100.0f; // Maximum speed in degrees per second

    // Calculate desired speeds based on joystick input
    float azimuthSpeed = m_azimuthInput * maxSpeed;
    float elevationSpeed = m_elevationInput * maxSpeed;

    // Determine directions
    uint16_t azimuthDirection = (azimuthSpeed >= 0) ? 1 : 0;
    uint16_t elevationDirection = (elevationSpeed >= 0) ? 1 : 0;

    // Absolute values for speeds
    uint16_t azimuthSpeedValue = static_cast<uint16_t>(fabs(azimuthSpeed));
    uint16_t elevationSpeedValue = static_cast<uint16_t>(fabs(elevationSpeed));

    // Send commands via PLCServoInterface
    if (controller->getPLCServoInterface()) {
        controller->getPLCServoInterface()->setOperationMode(1); // Manual mode
        controller->getPLCServoInterface()->setAzimuthSpeed(azimuthSpeedValue);
        controller->getPLCServoInterface()->setElevationSpeed(elevationSpeedValue);
        controller->getPLCServoInterface()->setAzimuthDirection(azimuthDirection);
        controller->getPLCServoInterface()->setElevationDirection(elevationDirection);
        controller->getPLCServoInterface()->setActualAzimuth(m_azimuth);
        controller->getPLCServoInterface()->setActualElevation(m_elevation);
        // Since we're in manual mode, target angles might not be used
        controller->getPLCServoInterface()->setAzimuthTargetAngle(0);
        controller->getPLCServoInterface()->setElevationTargetAngle(0);

        // Send parameters to PLC
        controller->getPLCServoInterface()->sendParameters();
    }
}
