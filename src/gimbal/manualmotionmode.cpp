#include "include/gimbal/manualmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"

#include <QDebug>
#include <Eigen/Dense>

ManualMotionMode::ManualMotionMode(QObject *parent)
    : QObject(parent)
{
}

void ManualMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Manual Motion Mode";
}

void ManualMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Manual Motion Mode";
}

void ManualMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value)
{
    if (axis == 0) { // Azimuth axis
        m_azimuthJoystickInput = value;
    } else if (axis == 1) { // Elevation axis
        m_elevationJoystickInput = value;
    }
}


void ManualMotionMode::update(GimbalController* controller) {
    // Access DataModel from the controller
    DataModel* dataModel = controller->getDataModel();

    // Check if the station state is ON
    if (!dataModel->getStationState()) {
        // Station is OFF; do not send movement commands
        qDebug() << "Station state is OFF. Gimbal movement is disabled.";
        return;
    }

    // Check if the dead man switch (joystick button 4) is active
    if (!dataModel->getDeadManSwitchState()) {
        // Dead man switch is not active; do not send movement commands
        qDebug() << "Dead man switch is not active. Gimbal movement is disabled.";
        return;
    }

    // Set maxAngularVelocity based on the speed switch
    float maxAngularVelocity = dataModel->getSpeedSw(); // Degrees per second

    // Compute desired angular velocities from joystick inputs
    float desiredAngularVelocityAzimuth = m_azimuthJoystickInput * maxAngularVelocity;
    float desiredAngularVelocityElevation = m_elevationJoystickInput * maxAngularVelocity;

    // Initialize stabilization corrections
    float stabilizationAngularVelocityAzimuth = 0.0f;
    float stabilizationAngularVelocityElevation = 0.0f;

    // Get stabilization corrections if enabled
    if (dataModel->getStabilizationSw()) {
        // Get gyroscope angular rates (degrees per second)
        double gyroAngularRateRoll;    // p (roll rate)
        double gyroAngularRatePitch;   // q (pitch rate)
        double gyroAngularRateYaw;     // r (yaw rate)

        dataModel->getGyroOrientation(gyroAngularRateRoll, gyroAngularRatePitch, gyroAngularRateYaw);

        // Convert angular rates to vector
        Eigen::Vector3d omega_body(gyroAngularRateRoll, gyroAngularRatePitch, gyroAngularRateYaw);

        // Get current gimbal angles (degrees)
        double azimuthAngle = dataModel->getGimbalAzimuthUpdated();    // α
        double elevationAngle = dataModel->getGimbalElevationUpdated(); // ε

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

    // Apply limits to angular velocities
    commandAngularVelocityAzimuth = std::clamp(commandAngularVelocityAzimuth, -maxAngularVelocity, maxAngularVelocity);
    commandAngularVelocityElevation = std::clamp(commandAngularVelocityElevation, -maxAngularVelocity, maxAngularVelocity);

    // Get current elevation angle
    double elevationAngle = dataModel->getGimbalElevationUpdated();

    // Elevation angle limits
    const double minElevationAngle = -15.0; // Degrees
    const double maxElevationAngle = 50.0;  // Degrees

    // Check limit sensors
    bool upperLimitSensorActivated = dataModel->getStationUpperSensor();
    bool lowerLimitSensorActivated = dataModel->getStationLowerSensor();

    // Prevent movement beyond upper elevation limit
    if ((elevationAngle >= maxElevationAngle || upperLimitSensorActivated) && commandAngularVelocityElevation > 0) {
        commandAngularVelocityElevation = 0.0f;
        qDebug() << "Upper elevation limit reached or sensor activated. Preventing upward movement.";
    }

    // Prevent movement beyond lower elevation limit
    if ((elevationAngle <= minElevationAngle || lowerLimitSensorActivated) && commandAngularVelocityElevation < 0) {
        commandAngularVelocityElevation = 0.0f;
        qDebug() << "Lower elevation limit reached or sensor activated. Preventing downward movement.";
    }

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



