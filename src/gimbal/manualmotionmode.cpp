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

void ManualMotionMode::update(GimbalController* controller) {
    // Define maximum angular velocity (degrees per second)
    const float maxAngularVelocity = 100.0f; // Adjust as needed

    // Compute desired angular velocities from joystick inputs
    float desiredAngularVelocityAzimuth = m_azimuthInput * maxAngularVelocity;
    float desiredAngularVelocityElevation = m_elevationInput * maxAngularVelocity;

    // Initialize stabilization corrections
    float stabilizationAngularVelocityAzimuth = 0.0f;
    float stabilizationAngularVelocityElevation = 0.0f;

    // Get stabilization corrections if enabled
    SensorSystem* sensorSystem = controller->getSensorSystem();
    if (sensorSystem && controller->isStabilizationEnabled()) {
        double gyroAngularRateRoll;    // Angular velocity around X-axis
        double gyroAngularRatePitch;   // Angular velocity around Y-axis
        double gyroAngularRateYaw;     // Angular velocity around Z-axis

        // Get gyroscope angular rates (degrees per second)
        sensorSystem->getGyroRates(gyroAngularRateRoll, gyroAngularRatePitch, gyroAngularRateYaw);

        // Stabilization gains (adjust as needed)
        const float stabilizationGainAzimuth = 1.0f;
        const float stabilizationGainElevation = 1.0f;

        // Compute stabilization corrections (negative to counteract disturbances)
        stabilizationAngularVelocityAzimuth = -gyroAngularRateYaw * stabilizationGainAzimuth;
        stabilizationAngularVelocityElevation = -gyroAngularRatePitch * stabilizationGainElevation;
    }

    // Combine manual inputs with stabilization corrections
    float commandAngularVelocityAzimuth = desiredAngularVelocityAzimuth + stabilizationAngularVelocityAzimuth;
    float commandAngularVelocityElevation = desiredAngularVelocityElevation + stabilizationAngularVelocityElevation;

    // Apply limits
    commandAngularVelocityAzimuth = std::clamp(commandAngularVelocityAzimuth, -maxAngularVelocity, maxAngularVelocity);
    commandAngularVelocityElevation = std::clamp(commandAngularVelocityElevation, -maxAngularVelocity, maxAngularVelocity);

    // Convert angular velocities to motor commands
    const int stepsPerRevolution = 3200; // Adjust based on your motor's specifications

    // Convert degrees per second to pulses per second
    float pulsesPerSecondAzimuth = (commandAngularVelocityAzimuth / 360.0f) * stepsPerRevolution;
    float pulsesPerSecondElevation = (commandAngularVelocityElevation / 360.0f) * stepsPerRevolution;

    // Determine directions
    uint16_t azimuthDirection = (pulsesPerSecondAzimuth >= 0) ? 1 : 0;
    uint16_t elevationDirection = (pulsesPerSecondElevation >= 0) ? 1 : 0;

    // Absolute values for speeds
    uint16_t azimuthSpeedValue = static_cast<uint16_t>(fabs(pulsesPerSecondAzimuth));
    uint16_t elevationSpeedValue = static_cast<uint16_t>(fabs(pulsesPerSecondElevation));

    // Send commands via PLCServoInterface
    if (controller->getPLCServoInterface()) {
        controller->getPLCServoInterface()->setOperationMode(1); // Manual mode
        controller->getPLCServoInterface()->setAzimuthSpeed(azimuthSpeedValue);
        controller->getPLCServoInterface()->setElevationSpeed(elevationSpeedValue);
        controller->getPLCServoInterface()->setAzimuthDirection(azimuthDirection);
        controller->getPLCServoInterface()->setElevationDirection(elevationDirection);
        controller->getPLCServoInterface()->sendParameters();
    }
}
