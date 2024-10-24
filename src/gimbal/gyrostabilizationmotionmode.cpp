#include "include/gimbal/gyrostabilizationmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/sensor/sensorsystem.h"
#include "include/gimbal/gimbalmotordriver.h"
#include <QDebug>
#include <Eigen/Dense>
#include <cmath>

void GyroStabilizationMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Gyro Stabilization Motion Mode";
    // Enable gyrostabilization in SensorSystem

    //TO MODIFY in GIMBAL CONTROLLER CLASS !!!
    /*if (controller->getSensorSystem()) {
        controller->getSensorSystem()->enableStabilization();
    }*/
}

void GyroStabilizationMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Gyro Stabilization Motion Mode";
    // Disable gyrostabilization in SensorSystem
    /*if (controller->getSensorSystem()) {
        controller->getSensorSystem()->disableStabilization();
    }*/
}

void GyroStabilizationMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value) {
    // Optionally adjust stabilization parameters based on joystick input
}

void GyroStabilizationMotionMode::update(GimbalController* controller) {
    // Use gyro data to adjust motor commands
    SensorSystem* sensorSystem = controller->getSensorSystem();
    if (sensorSystem) {
        double psi, theta, phi;
        double compensationAzimuth;
        double compensationElevation;

        sensorSystem->getGyroRates(psi, theta, phi);

        // Create rotation matrix from body to inertial frame
        Eigen::Matrix3d R_body_inertial;
        R_body_inertial = Eigen::AngleAxisd(psi, Eigen::Vector3d::UnitZ()) *
                          Eigen::AngleAxisd(theta, Eigen::Vector3d::UnitY()) *
                          Eigen::AngleAxisd(phi, Eigen::Vector3d::UnitX());

        // Desired gimbal orientation in inertial frame (e.g., stabilize to horizon)
        Eigen::Matrix3d R_gimbal_inertial = Eigen::Matrix3d::Identity();

        // Compute rotation from body frame to desired gimbal orientation
        Eigen::Matrix3d R_gimbal_body = R_body_inertial.transpose() * R_gimbal_inertial;

        // Extract azimuth and elevation angles from R_gimbal_body
        compensationAzimuth = atan2(R_gimbal_body(1, 0), R_gimbal_body(0, 0)); // Azimuth angle
        compensationElevation = asin(-R_gimbal_body(2, 0)); // Elevation angle

        // Convert radians to degrees
        compensationAzimuth = compensationAzimuth * (180.0 / M_PI);
        compensationElevation = compensationElevation * (180.0 / M_PI);

        // Send motion command to GimbalMotorDriver
         controller->getGimbalMotorDriver()->sendPositionCommand(compensationAzimuth, compensationElevation);

    }
}
