#include "include/gimbal/gimbalcontroller.h"
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
      m_azimuth(0.0),
      m_elevation(0.0)
{
    // Initialize the motor driver
    if (!m_gimbalMotorDriver->initialize()) {
        qWarning() << "Failed to initialize GimbalMotorDriver";
    }

    // Connect signals from motor driver
    connect(m_gimbalMotorDriver, &GimbalMotorDriver::azimuthDataUpdated,
            this, &GimbalController::onAzimuthDataUpdated);

    connect(m_gimbalMotorDriver, &GimbalMotorDriver::elevationDataUpdated,
            this, &GimbalController::onElevationDataUpdated);

    connect(m_gimbalMotorDriver, &GimbalMotorDriver::logMessage,
            this, [](const QString &message) {
                qDebug() << "GimbalMotorDriver:" << message;
            });
}

GimbalController::~GimbalController() {
    if (m_currentMotionMode) {
        m_currentMotionMode->exit(this);
        delete m_currentMotionMode;
    }
}

void GimbalController::setMotionMode(GimbalMotionMode* mode) {
    if (m_currentMotionMode) {
        m_currentMotionMode->exit(this);
        delete m_currentMotionMode;
    }
    m_currentMotionMode = mode;
    if (m_currentMotionMode) {
        m_currentMotionMode->enter(this);
    }
}

void GimbalController::handleJoystickInput(int axis, float value) {
    if (m_currentMotionMode) {
        m_currentMotionMode->handleJoystickInput(this, axis, value);
    }
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
            // Depending on requirements, enable auto-scan
            break;
        case OperationalMode::Detection:
            enableManualControl(false);
            break;
        case OperationalMode::Tracking:
            // Possibly allow manual adjustments
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
