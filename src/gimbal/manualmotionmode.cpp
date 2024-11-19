#include "include/gimbal/manualmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/gimbal/gimbalmotordriver.h"
#include <QDebug>
#include <Eigen/Dense>

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
        // Get gyroscope angular rates (degrees per second)
        double gyroAngularRateRoll;    // p (roll rate)
        double gyroAngularRatePitch;   // q (pitch rate)
        double gyroAngularRateYaw;     // r (yaw rate)

        sensorSystem->getGyroRates(gyroAngularRateRoll, gyroAngularRatePitch, gyroAngularRateYaw);

        // Convert angular rates to vector
        Eigen::Vector3d omega_body(gyroAngularRateRoll, gyroAngularRatePitch, gyroAngularRateYaw);

        // Get current gimbal angles (degrees)
        double azimuthAngle = controller->getAzimuthPosition();    // α
        double elevationAngle = controller->getElevationPosition(); // ε

        // Convert angles to radians
        double alpha = azimuthAngle * (M_PI / 180.0);
        double epsilon = elevationAngle * (M_PI / 180.0);

        // Compute rotation matrices
        Eigen::Matrix3d R_azimuth;
        R_azimuth << cos(alpha), -sin(alpha), 0,
            sin(alpha),  cos(alpha), 0,
            0,           0,     1;

        Eigen::Matrix3d R_elevation;
        R_elevation << cos(epsilon), 0, sin(epsilon),
            0,       1,      0,
            -sin(epsilon), 0, cos(epsilon);

        // Compute combined rotation matrix
        Eigen::Matrix3d R_gimbal_body = R_elevation * R_azimuth;

        // Transform angular velocity to gimbal frame
        Eigen::Vector3d omega_gimbal = R_gimbal_body * omega_body;

        // Extract gimbal axis rates
        double omega_azimuth = omega_gimbal(2);   // ω_az (rotation around Z-axis)
        double omega_elevation = omega_gimbal(1); // ω_el (rotation around Y-axis)

        // Stabilization gains (adjust as needed)
        const float stabilizationGainAzimuth = 1.0f;
        const float stabilizationGainElevation = 1.0f;

        // Compute stabilization corrections (negative to counteract disturbances)
        stabilizationAngularVelocityAzimuth = -omega_azimuth * stabilizationGainAzimuth;
        stabilizationAngularVelocityElevation = -omega_elevation * stabilizationGainElevation;
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

void ManualMotionMode::onTargetPositionUpdated(double azimuth, double elevation) {
    //m_targetAzimuth = azimuth;
    //m_targetElevation = elevation;
}
