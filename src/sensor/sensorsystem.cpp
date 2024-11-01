#include "include/sensor/sensorsystem.h"
#include <QThread>
#include <QMetaObject>
#include <QDebug>
#include "include/comm/serialportmanager.h"

SensorSystem::SensorSystem(QObject *parent)
    : QObject(parent),
    m_sensorsActive(false),
    m_lrfActive(false),
    m_stabilizationEnabled(false),
    m_lrfInterface(new LRFInterface(this)),
    m_gyroInterface(new GyroInterface(this)),
    m_radarInterface(new RadarInterface(this)),
    m_plcSensorInterface(nullptr),
    m_roll(0.0),
    m_pitch(0.0),
    m_yaw(0.0)
{
    qDebug() << "SensorSystem constructor called";

    // Initialize LRF Interface
    if (m_lrfInterface->openSerialPort("/dev/pts/1")) {
        setLRFInterface(m_lrfInterface);
        handleLRFConnectionStatusChanged(true);

    } else {
       qDebug() << "Failed to open LRF serial port";
        // Handle failure
    }

    // Initialize Gyro Interface
    if (m_gyroInterface->openSerialPort("/dev/pts/22")) {
        setGyroInterface(m_gyroInterface);
        handleGyroConnectionStatusChanged(true);
    } else {
       qDebug() << "Failed to open Gyro serial port";
        // Handle failure
    }

    // Initialize Radar Interface
    if (m_radarInterface->openSerialPort("/dev/pts/17")) {
        setRadarInterface(m_radarInterface);
        handleRadarConnectionStatusChanged(true);

    } else {
       qDebug() << "Failed to open Radar serial port";
        // Handle failure
    }

    // m_plcSensorInterface is instantiated in the main class!
}

SensorSystem::~SensorSystem(){
    shutdown();
}

void SensorSystem::shutdown() {
    // Stop monitoring sensors
    stopMonitoringSensors();

    // Shutdown interfaces
    if (m_lrfInterface) {
        m_lrfInterface->shutdown();
    }
    if (m_gyroInterface) {
        m_gyroInterface->shutdown();
    }
    if (m_radarInterface) {
        m_radarInterface->shutdown();
    }

    qDebug() << "SensorSystem has been shut down.";
}
// Setter methods
void SensorSystem::setLRFInterface(LRFInterface *lrfInterface) {
    if (m_lrfInterface) {
        // Disconnect previous connections if any
        disconnect(m_lrfInterface, nullptr, this, nullptr);
    }

    m_lrfInterface = lrfInterface;

    if (m_lrfInterface) {
        // Connect LRFInterface signals to SensorSystem signals
        connect(m_lrfInterface, &LRFInterface::errorOccurred, this, &SensorSystem::handleErrorOccurred);
        connect(m_lrfInterface, &LRFInterface::frequencySet, this, &SensorSystem::handleFrequencySet);
        connect(m_lrfInterface, &LRFInterface::settingValueReceived, this, &SensorSystem::handleSettingValueReceived);
        connect(m_lrfInterface, &LRFInterface::laserCountReceived, this, &SensorSystem::handleLaserCountReceived);
        connect(m_lrfInterface, &LRFInterface::selfCheckResult, this, &SensorSystem::handleSelfCheckResult);
        connect(m_lrfInterface, &LRFInterface::rangingDataReceived, this, &SensorSystem::handleRangingDataReceived);

        connect(m_lrfInterface, &LRFInterface::statusChanged, this, &SensorSystem::handleLRFConnectionStatusChanged);

    }
}

void SensorSystem::onLRFInterfaceDestroyed(QObject *obj) {
    if (m_lrfInterface == obj) {
       qDebug() << "LRFInterface has been destroyed.";
        m_lrfInterface = nullptr;
    }
}

void SensorSystem::setGyroInterface(GyroInterface *gyroInterface) {
    if (m_gyroInterface) {
        disconnect(m_gyroInterface, nullptr, this, nullptr);
    }
    m_gyroInterface = gyroInterface;
    if (m_gyroInterface) {
        connect(m_gyroInterface, &GyroInterface::gyroDataReceived, this, &SensorSystem::onGyroDataReceived);
        connect(m_gyroInterface, &GyroInterface::errorOccurred, this, &SensorSystem::handleErrorOccurred);

        connect(m_gyroInterface, &GyroInterface::statusChanged, this, &SensorSystem::handleGyroConnectionStatusChanged);

        // Connect other signals as needed
    }
}

void SensorSystem::setRadarInterface(RadarInterface *radarInterface) {
    if (m_radarInterface) {
        disconnect(m_radarInterface, nullptr, this, nullptr);
    }
    m_radarInterface = radarInterface;
    if (m_radarInterface) {
        //connect(m_radarInterface, &RadarInterface::targetUpdated, this, &SensorSystem::onRadarDataReceived);
        connect(m_radarInterface, &RadarInterface::errorOccurred, this, &SensorSystem::handleErrorOccurred);

        connect(m_radarInterface, &RadarInterface::statusChanged, this, &SensorSystem::handleRadarConnectionStatusChanged);

        // Connect other signals as needed
    }
}

void SensorSystem::setPLCSensorInterface(PLCSensorInterface *sensorInterface) {
    if (m_plcSensorInterface) {
        // Disconnect previous connections if any
        disconnect(m_plcSensorInterface, nullptr, this, nullptr);
    }
    m_plcSensorInterface = sensorInterface;
    if (m_plcSensorInterface) {
        // Connect signals
        connect(m_plcSensorInterface, &PLCSensorInterface::proximitySensorActivated, this, &SensorSystem::proximitySensorActivated);
        connect(m_plcSensorInterface, &PLCSensorInterface::temperatureUpdated, this, &SensorSystem::temperatureUpdated);
        connect(m_plcSensorInterface, &PLCSensorInterface::pressureUpdated, this, &SensorSystem::pressureUpdated);
    }
}


void SensorSystem::handleLRFConnectionStatusChanged(bool connected){
    emit lrfConnectionStatusChanged(connected);
}
void SensorSystem::handleRadarConnectionStatusChanged(bool connected){

    emit radarConnectionStatusChanged(connected);
}

void SensorSystem::handleGyroConnectionStatusChanged(bool connected){

    emit gyroConnectionStatusChanged(connected);
}
// Getter methods
LRFInterface* SensorSystem::getLRFInterface() const {
    return m_lrfInterface;
}

GyroInterface* SensorSystem::getGyroInterface() const {
    return m_gyroInterface;
}

RadarInterface* SensorSystem::getRadarInterface() const {
    return m_radarInterface;
}

PLCSensorInterface* SensorSystem::getPLCSensorInterface() const {
    return m_plcSensorInterface;
}

void SensorSystem::startMonitoringSensors() {
    if (m_plcSensorInterface) {
        m_plcSensorInterface->startMonitoring();
    }
}

void SensorSystem::stopMonitoringSensors() {
    if (m_plcSensorInterface) {
        m_plcSensorInterface->stopMonitoring();
    }
}

// Methods for GYRO
void SensorSystem::getGyroRates(double& Roll, double& Pitch, double& Yaw) {
    Roll = m_roll;
    Pitch = m_pitch;
    Yaw = m_yaw;
}

void SensorSystem::onGyroDataReceived(double Roll, double Pitch, double Yaw) {
    m_roll = Roll;
    m_pitch = Pitch;
    m_yaw = Yaw;
    emit gyroDataUpdated(m_roll, m_pitch, m_yaw);
}

// Methods for RADAR
// to implment ...


void SensorSystem::sendSelfCheck()
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "sendSelfCheck", Qt::QueuedConnection);
    } else {
       qDebug() << "m_lrfInterface is null. Cannot send self-check command.";
        emit errorOccurred("Unable to send self-check command: LRF interface is not initialized.");
    }
}

void SensorSystem::sendSingleRanging()
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "sendSingleRanging", Qt::QueuedConnection);
    } else {
       qDebug() << "m_lrfInterface is null. Cannot send single ranging command.";
        emit errorOccurred("Unable to send single ranging command: LRF interface is not initialized.");
    }
}

void SensorSystem::sendContinuousRanging()
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "sendContinuousRanging", Qt::QueuedConnection);
    } else {
       qDebug() << "m_lrfInterface is null. Cannot send continuous ranging command.";
        emit errorOccurred("Unable to send continuous ranging command: LRF interface is not initialized.");
    }
}

void SensorSystem::stopRanging()
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "stopRanging", Qt::QueuedConnection);
    } else {
       qDebug() << "m_lrfInterface is null. Cannot stop ranging.";
        emit errorOccurred("Unable to stop ranging: LRF interface is not initialized.");
    }
}

void SensorSystem::setFrequency(int frequency)
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "setFrequency", Qt::QueuedConnection, Q_ARG(int, frequency));
    } else {
       qDebug() << "m_lrfInterface is null. Cannot set frequency.";
        emit errorOccurred("Unable to set frequency: LRF interface is not initialized.");
    }
}

void SensorSystem::querySettingValue()
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "querySettingValue", Qt::QueuedConnection);
    } else {
       qDebug() << "m_lrfInterface is null. Cannot query setting value.";
        emit errorOccurred("Unable to query setting value: LRF interface is not initialized.");
    }
}

void SensorSystem::queryAccumulatedLaserCount()
{
    if (m_lrfInterface) {
        QMetaObject::invokeMethod(m_lrfInterface, "queryAccumulatedLaserCount", Qt::QueuedConnection);
    } else {
       qDebug() << "m_lrfInterface is null. Cannot query accumulated laser count.";
        emit errorOccurred("Unable to query accumulated laser count: LRF interface is not initialized.");
    }
}


void SensorSystem::handleErrorOccurred(const QString &error) {
    // Optionally process the error before emitting
    qDebug() << "SensorSystem received errorOccurred:" << error;
    emit errorOccurred(error);
}

void SensorSystem::handleFrequencySet(quint8 frequency, quint8 majorVersion, quint8 secondaryVersion, quint8 maintenanceVersion) {
    // Optionally process the frequency set data
    qDebug() << "SensorSystem received frequencySet:" << frequency << majorVersion << secondaryVersion << maintenanceVersion;
    emit frequencySet(frequency, majorVersion, secondaryVersion, maintenanceVersion);
}

void SensorSystem::handleSettingValueReceived(quint8 value) {
    // Optionally process the setting value
    qDebug() << "SensorSystem received settingValueReceived:" << value;
    emit settingValueReceived(value);
}

void SensorSystem::handleLaserCountReceived(quint32 count) {
    // Optionally process the laser count
    qDebug() << "SensorSystem received laserCountReceived:" << count;
    emit laserCountReceived(count);
}

void SensorSystem::handleSelfCheckResult(quint8 systemStatus, quint8 temperatureAlarm, quint8 biasVoltageFault, quint8 counterMalfunction) {
    // Optionally process self-check results
    qDebug() << "SensorSystem received selfCheckResult:" << systemStatus << temperatureAlarm << biasVoltageFault << counterMalfunction;
    emit selfCheckResult(systemStatus, temperatureAlarm, biasVoltageFault, counterMalfunction);
}

void SensorSystem::handleRangingDataReceived(quint8 status, quint16 distance, quint8 decimalPlaces, quint8 echoStatus) {
    // Optionally process ranging data
    qDebug() << "SensorSystem received rangingDataReceived:" << status << distance << decimalPlaces << echoStatus;
    emit rangingDataReceived(status, distance, decimalPlaces, echoStatus);
}
