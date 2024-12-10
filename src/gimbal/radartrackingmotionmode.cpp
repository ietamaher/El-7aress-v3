#include "include/gimbal/radartrackingmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/sensor/sensorsystem.h"

#include <QDebug>

void RadarTrackingMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Radar Tracking Motion Mode";
    /*SensorSystem* sensorSystem = controller->getSensorSystem();
    if (sensorSystem && sensorSystem->getRadarInterface()) {
        connect(sensorSystem->getRadarInterface(), &RadarInterface::targetUpdated,
                this, &RadarTrackingMotionMode::onRadarTargetUpdated);
    }*/
}

void RadarTrackingMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Radar Tracking Motion Mode";
    /*SensorSystem* sensorSystem = controller->getSensorSystem();
    if (sensorSystem && sensorSystem->getRadarInterface()) {
        disconnect(sensorSystem->getRadarInterface(), &RadarInterface::targetUpdated,
                   this, &RadarTrackingMotionMode::onRadarTargetUpdated);
    }*/
}

void RadarTrackingMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value) {
    // Optionally allow operator adjustments
}

void RadarTrackingMotionMode::onRadarTargetUpdated(const RadarTarget &target) {
    // Update the target azimuth and elevation based on the RadarTarget data
    m_targetAzimuth = target.azimuth;
    m_targetElevation = 0.0; // Adjust if elevation data is available
}

void RadarTrackingMotionMode::update(GimbalController* controller) {
    // Use m_targetAzimuth and m_targetElevation to command the gimbal
    controller->sendPositionCommand(m_targetAzimuth, m_targetElevation);
}
