#include "include/gimbal/gimbalmotordriver.h"
#include <QDebug>

GimbalMotorDriver::GimbalMotorDriver(QObject *parent)
    : QObject(parent),
    //m_mduinoController(new MduinoController("/dev/pts/12", 115200, 1, this)), // Adjust port and slave ID
    m_azimuthServoDriver(new ServoDriverInterface("azServo", "/dev/pts/15", 115200, 1, this)),
    m_elevationServoDriver(new ServoDriverInterface("elServo", "/dev/pts/18", 115200, 1, this)),
    m_azimuthPosition(0.0),
    m_elevationPosition(0.0)
{
    // Connect signals from ServoDriverInterface
    connect(m_azimuthServoDriver, &ServoDriverInterface::dataRead,
            this, &GimbalMotorDriver::processAzimuthServoData);

    connect(m_elevationServoDriver, &ServoDriverInterface::dataRead,
            this, &GimbalMotorDriver::processElevationServoData);

    // Connect log messages
    connect(m_azimuthServoDriver, &ServoDriverInterface::logMessage,
            this, &GimbalMotorDriver::logMessage);

    connect(m_elevationServoDriver, &ServoDriverInterface::logMessage,
            this, &GimbalMotorDriver::logMessage);

    //connect(m_mduinoController, &MduinoController::logMessage,
      //      this, &GimbalMotorDriver::logMessage);
}

GimbalMotorDriver::~GimbalMotorDriver() {
    m_azimuthServoDriver->disconnectDevice();
    m_elevationServoDriver->disconnectDevice();
    //m_mduinoController->disconnectDevice();
}

bool GimbalMotorDriver::initialize() {
    // Connect ServoDriverInterface instances
    bool azimuthConnected = m_azimuthServoDriver->connectDevice();
    bool elevationConnected = m_elevationServoDriver->connectDevice();

    if (!azimuthConnected || !elevationConnected) {
        emit logMessage("Failed to connect to servo drivers.");
        return false;
    }

    // Connect to mduino controller
    //if (!m_mduinoController->connectDevice()) {
      //  emit logMessage("Failed to connect to mduino industrial shield.");
       // return false;
    //}

    emit logMessage("GimbalMotorDriver initialized successfully.");
    return true;
}

void GimbalMotorDriver::sendPositionCommand(double azimuth, double elevation) {
    // Convert positions to pulses or appropriate units
    int azimuthPulse = static_cast<int>(azimuth * /* conversion factor */ 1000); // Adjust as needed
    int elevationPulse = static_cast<int>(elevation * 1000); // Adjust as needed

    // Determine direction based on whether the pulse value is positive or negative
    bool azimuthDirection = azimuthPulse >= 0;
    bool elevationDirection = elevationPulse >= 0;

    // Absolute value of pulses
    azimuthPulse = abs(azimuthPulse);
    elevationPulse = abs(elevationPulse);

    // Send commands to mduino controller
    m_mduinoController->setAzimuthPulse(azimuthPulse);
    m_mduinoController->setAzimuthDirection(azimuthDirection);

    m_mduinoController->setElevationPulse(elevationPulse);
    m_mduinoController->setElevationDirection(elevationDirection);
}

void GimbalMotorDriver::sendSpeedCommand(double azimuthSpeed, double elevationSpeed) {
    // Implement if needed
}

double GimbalMotorDriver::getAzimuthPosition() const {
    return m_azimuthPosition;
}

double GimbalMotorDriver::getElevationPosition() const {
    return m_elevationPosition;
}

void GimbalMotorDriver::processAzimuthServoData(const QVector<uint16_t> &data) {
    if (data.size() >= 50) {
        int32_t position = (data[6] << 16) | data[7];
        int32_t speed = (data[8] << 16) | data[9];
        int32_t torque = (data[16] << 16) | data[17];
        int32_t motorTemp = (data[46] << 16) | data[47];
        int32_t driverTemp = (data[48] << 16) | data[49];

        m_azimuthPosition = position / 1000.0; // Adjust scaling as needed

        emit azimuthDataUpdated(m_azimuthPosition, speed, torque, motorTemp, driverTemp);
    }
}

void GimbalMotorDriver::processElevationServoData(const QVector<uint16_t> &data) {
    if (data.size() >= 50) {
        int32_t position = (data[6] << 16) | data[7];
        int32_t speed = (data[8] << 16) | data[9];
        int32_t torque = (data[16] << 16) | data[17];
        int32_t motorTemp = (data[46] << 16) | data[47];
        int32_t driverTemp = (data[48] << 16) | data[49];

        m_elevationPosition = position / 1000.0; // Adjust scaling as needed

        emit elevationDataUpdated(m_elevationPosition, speed, torque, motorTemp, driverTemp);
    }
}
