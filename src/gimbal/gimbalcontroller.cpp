#include "include/gimbal/gimbalcontroller.h"
#include "include/gimbal/manualmotionmode.h"
#include "include/gimbal/patternmotionmode.h"
#include "include/gimbal/targettrackingmotionmode.h"
#include "include/gimbal/radartrackingmotionmode.h"
#include <QDebug>

GimbalController::GimbalController(DataModel *dataModel, QObject *parent)
    : QObject(parent),
      m_dataModel(dataModel),
      m_plcServoInterface(nullptr),
      m_azimuthServoDriver(new ServoDriverInterface("azServo", "/dev/pts/5", 115200, 2, this)),
      m_elevationServoDriver(new ServoDriverInterface("elServo", "/dev/pts/8", 115200, 2, this)),
      m_azimuthPosition(0.0),
      m_elevationPosition(0.0),
      m_enabled(false),
      m_manualControlEnabled(false),
      m_currentOpsMode(OperationalMode::Idle),
      m_currentMotionMode(nullptr),
      m_sensorSystem(nullptr),
      m_cameraSystem(nullptr),
      m_currentMotionModeType(MotionModeType::Manual),
      m_stabilizationEnabled(false),
      m_azimuth(0.0),
      m_elevation(0.0)
{

    // Connect ServoDriverInterface instances
    bool azimuthConnected = m_azimuthServoDriver->connectDevice();
    bool elevationConnected = m_elevationServoDriver->connectDevice();

    if (!azimuthConnected || !elevationConnected) {
        emit logMessage("Failed to connect to servo drivers.");
        qDebug() << "Failed to connect to servo drivers.";
    }

    // Connect to mduino controller
    //if (!m_mduinoController->connectDevice()) {
    //  emit logMessage("Failed to connect to mduino industrial shield.");
    // return false;
    //}

    emit logMessage("GimbalMotorDriver initialized successfully.");



    // Connect signals from motor driver
    connect(m_azimuthServoDriver, &ServoDriverInterface::dataRead,  this, &GimbalController::onAzimuthDataUpdated);
    connect(m_elevationServoDriver, &ServoDriverInterface::dataRead,  this, &GimbalController::onElevationDataUpdated);

    connect(m_elevationServoDriver, &ServoDriverInterface::connectionStatusChanged, this, &GimbalController::handleElevationConnectionStatusChanged);
    connect(m_azimuthServoDriver, &ServoDriverInterface::connectionStatusChanged, this, &GimbalController::handleAzimuthConnectionStatusChanged);



    // Connect log messages
    connect(m_azimuthServoDriver, &ServoDriverInterface::logMessage, this, &GimbalController::logMessage);

    connect(m_elevationServoDriver, &ServoDriverInterface::logMessage, this, &GimbalController::logMessage);

}

GimbalController::~GimbalController() {
    shutdown();
}
void GimbalController::shutdown() {
    m_azimuthServoDriver->disconnectDevice();
    m_elevationServoDriver->disconnectDevice();
    if (m_currentMotionMode) {
        m_currentMotionMode->exit(this);
    }
}

double GimbalController::getAzimuthPosition() const {
    return m_azimuthPosition;
}

double GimbalController::getElevationPosition() const {
    return m_elevationPosition;
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
    if (m_plcServoInterface) {
        // Disconnect previous connections if any
        disconnect(m_plcServoInterface, nullptr, this, nullptr);
    }
    m_plcServoInterface = servoInterface;
    if (m_plcServoInterface) {
        // Connect signals
        //connect(m_plcServoInterface, &PLCStationSensorInterface::proximitySensorActivated, this, &SensorSystem::proximitySensorActivated);
        //connect(m_plcServoInterface, &PLCStationSensorInterface::temperatureUpdated, this, &SensorSystem::temperatureUpdated);
        //connect(m_plcServoInterface, &PLCStationSensorInterface::pressureUpdated, this, &SensorSystem::pressureUpdated);
    }
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

void GimbalController::sendSpeedCommand(double azimuthSpeed, double elevationSpeed) {
    // Implement if needed
}


void GimbalController::sendPositionCommand(double azimuth, double elevation) {
    // Convert positions to pulses or appropriate units
    int azimuthPulse = static_cast<int>(azimuth * /* conversion factor */ 1000); // Adjust as needed
    int elevationPulse = static_cast<int>(elevation * 1000); // Adjust as needed

    // Determine direction based on whether the pulse value is positive or negative
    bool azimuthDirection = azimuthPulse >= 0;
    bool elevationDirection = elevationPulse >= 0;

    // Absolute value of pulses
    azimuthPulse = abs(azimuthPulse);
    elevationPulse = abs(elevationPulse);

    // Send commands to PLC controller to control PULSE/DIR Drivers
    m_plcServoInterface->setServoParameters(azimuthPulse, azimuthDirection, elevationPulse, elevationDirection);

}
void GimbalController::onAzimuthDataUpdated(const QVector<uint16_t> &data) {
    if (data.size() >= 50) {
        int32_t position = (data[6] << 16) | data[7];
        int32_t speed = (data[8] << 16) | data[9];
        int32_t torque = (data[16] << 16) | data[17];
        int32_t motorTemp = (data[46] << 16) | data[47];
        int32_t driverTemp = (data[48] << 16) | data[49];

        m_azimuth = position / 1000.0; // Adjust scaling as needed

        emit positionUpdated(m_azimuth, m_elevation);
    }
}

void GimbalController::onElevationDataUpdated(const QVector<uint16_t> &data) {
    if (data.size() >= 50) {
        int32_t position = (data[6] << 16) | data[7];
        int32_t speed = (data[8] << 16) | data[9];
        int32_t torque = (data[16] << 16) | data[17];
        int32_t motorTemp = (data[46] << 16) | data[47];
        int32_t driverTemp = (data[48] << 16) | data[49];

        double m_elevation = position / 1000.0; // Adjust scaling as needed

        emit positionUpdated(m_azimuth, m_elevation);
    }
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
void GimbalController::setPanSpeed(float speed) {
    m_panSpeed = speed;
    // Update the hardware or internal logic to adjust the pan speed
}

void GimbalController::setTiltSpeed(float speed) {
    m_tiltSpeed = speed;
    // Update the hardware or internal logic to adjust the tilt speed
}
