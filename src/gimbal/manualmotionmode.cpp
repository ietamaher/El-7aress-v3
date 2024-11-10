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
    // Get joystick input adjustments (already handled in handleJoystickInput)
    double targetAzimuth = m_azimuth;
    double targetElevation = m_elevation;

    if (controller->isStabilizationEnabled()) {
        // Get stabilization adjustments
        double rollRate, pitchRate, yawRate;
        controller->getDataModel()->getGyroOrientation(rollRate, pitchRate, yawRate);

        // Apply stabilization corrections
        targetAzimuth -= rollRate * STABILIZATION_FACTOR;
        targetElevation -= pitchRate * STABILIZATION_FACTOR;
    }

    // Send position command
    controller->sendPositionCommand(targetAzimuth, targetElevation);
}
