#include "include/gimbal/gimbalcontroller.h"
#include "include/gimbal/manualmotionmode.h"
#include "include/gimbal/patternmotionmode.h"
#include "include/gimbal/targettrackingmotionmode.h"
#include "include/gimbal/radartrackingmotionmode.h"
#include <QDebug>

GimbalController::GimbalController(QObject *parent)
    : QObject(parent),
      m_enabled(false),
      m_manualControlEnabled(false),
      m_currentOpsMode(OperationalMode::Idle),
      m_currentMotionMode(nullptr),
      m_gimbalMotorDriver(new GimbalMotorDriver(this)),
      m_plcServoInterface(nullptr),
      m_sensorSystem(nullptr),
      m_cameraSystem(nullptr),
    m_currentMotionModeType(MotionModeType::Manual),
    m_stabilizationEnabled(false),
      m_azimuth(0.0),
      m_elevation(0.0)
{
    // Initialize the motor driver
    qDebug() << "GimbalController constructor called";

    if (!m_gimbalMotorDriver->initialize()) {
       qDebug() << "Failed to initialize GimbalMotorDriver";
    }

    // Connect signals from motor driver
    connect(m_gimbalMotorDriver, &GimbalMotorDriver::azimuthDataUpdated, this, &GimbalController::onAzimuthDataUpdated);
    connect(m_gimbalMotorDriver, &GimbalMotorDriver::elevationDataUpdated, this, &GimbalController::onElevationDataUpdated);

    connect(m_gimbalMotorDriver, &GimbalMotorDriver::elevationConnectionStatusChanged, this, &GimbalController::handleElevationConnectionStatusChanged);
    connect(m_gimbalMotorDriver, &GimbalMotorDriver::azimuthConnectionStatusChanged, this, &GimbalController::handleAzimuthConnectionStatusChanged);

    // Connect joystick button signal
    //connect(m_joystickHandler, &JoystickHandler::buttonPressed, this, &GimbalController::handleJoystickButtonPressed);

    connect(m_gimbalMotorDriver, &GimbalMotorDriver::logMessage,
            this, [](const QString &message) {
                qDebug() << "GimbalMotorDriver:" << message;
            });
}

GimbalController::~GimbalController() {
    if (m_currentMotionMode) {
        m_currentMotionMode->exit(this);
    }
}

void GimbalController::setMotionMode(MotionModeType modeType) {
    if (m_currentMotionModeType == modeType)
        return; // No change needed

    // Exit current motion mode
    if (m_currentMotionMode) {
        m_currentMotionMode->exit(this);
    }

    // Instantiate the new motion mode
    switch (modeType) {
    case MotionModeType::Manual:
        m_currentMotionMode = std::make_unique<ManualMotionMode>();
        break;
    case MotionModeType::Pattern:
        m_currentMotionMode = std::make_unique<PatternMotionMode>();
        break;
    case MotionModeType::TargetTracking:
        m_currentMotionMode = std::make_unique<TargetTrackingMotionMode>();
        break;
    case MotionModeType::Radar:
        m_currentMotionMode = std::make_unique<RadarTrackingMotionMode>();
        break;
    default:
        qWarning() << "GimbalController: Unknown MotionModeType";
        m_currentMotionMode = nullptr;
        break;
    }

    m_currentMotionModeType = modeType;

    // Enter the new motion mode
    if (m_currentMotionMode) {
        m_currentMotionMode->enter(this);
    }

    qDebug() << "GimbalController: Motion mode set to" << static_cast<int>(modeType);

    // Emit the signal after setting the mode
    //emit motionModeChangeRequested(modeType);

}

void GimbalController::setStabilizationEnabled(bool enabled) {
    m_stabilizationEnabled = enabled;
}

bool GimbalController::isStabilizationEnabled() const {
    return m_stabilizationEnabled;
}

void GimbalController::handleAzimuthConnectionStatusChanged(bool connected){
    emit azimuthConnectionStatusChanged(connected);
}
void GimbalController::handleElevationConnectionStatusChanged(bool connected){

    emit elevationConnectionStatusChanged(connected);
}


void GimbalController::update() {
    if (m_currentMotionMode) {
        m_currentMotionMode->update(this);
    }
}

void GimbalController::setPLCServoInterface(PLCServoInterface *servoInterface) {
    m_plcServoInterface = servoInterface;
}

GimbalMotorDriver* GimbalController::getGimbalMotorDriver() const {
    return m_gimbalMotorDriver;
}

SensorSystem* GimbalController::getSensorSystem() const {
    return m_sensorSystem;
}

void GimbalController::setSensorSystem(SensorSystem* sensorSystem) {
    m_sensorSystem = sensorSystem;
}

CameraSystem* GimbalController::getCameraSystem() const {
    return m_cameraSystem;
}

void GimbalController::setCameraSystem(CameraSystem* cameraSystem) {
    m_cameraSystem = cameraSystem;
}

void GimbalController::onAzimuthDataUpdated(double position, double speed, double torque, double motorTemp, double driverTemp) {
    m_azimuth = position;
    emit positionUpdated(m_azimuth, m_elevation);
    // Process other parameters as needed
}

void GimbalController::onElevationDataUpdated(double position, double speed, double torque, double motorTemp, double driverTemp) {
    m_elevation = position;
    emit positionUpdated(m_azimuth, m_elevation);
    // Process other parameters as needed
}
void GimbalController::onModeChanged(OperationalMode mode) {
    m_currentOpsMode = mode;

    switch (mode) {
        case OperationalMode::Idle:
            enable(false);
            break;
        case OperationalMode::Surveillance:
            enableManualControl(true);
            break;
        case OperationalMode::Tracking:
            enableManualControl(false);
            break;
        case OperationalMode::Engagement:
            enableManualControl(true);
            break;
    }
}

void GimbalController::enable(bool enabled) {
    // Implement logic to enable or disable the gimbal controller
    // For example:
    // m_enabled = enabled;
}

void GimbalController::enableManualControl(bool enabled) {
    // Implement logic to enable or disable manual control
    // For example:
    // m_manualControlEnabled = enabled;
}

MotionModeType GimbalController::getCurrentMotionMode() const {
    return m_currentMotionModeType;
}
