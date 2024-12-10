#include "include/sensor/sensorsystem.h"
#include <QThread>
#include <QMetaObject>
#include <QDebug>
#include "include/comm/serialportmanager.h"

SensorSystem::SensorSystem(DataModel *dataModel, QObject *parent)
    : QObject(parent),
    m_dataModel(dataModel),
    m_sensorsActive(false),
    m_lrfActive(false),
    m_stabilizationEnabled(false),
    //m_lrfInterface(new LRFInterface(this)),
    //m_gyroInterface(new GyroInterface(this)),
    //m_radarInterface(new RadarInterface(this)),
    m_plcStationSensorInterface(nullptr),
    m_plcPanelSensorInterface(new PLCPanelSensorInterface("/dev/pts/13", 115200, 1, this)),

    m_roll(0.0),
    m_pitch(0.0),
    m_yaw(0.0)
{
    qDebug() << "SensorSystem constructor called";

    // Initialize LRF Interface
    /*if (m_lrfInterface->openSerialPort("/dev/pts/1")) {
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
    }*/
    // Connect PLCPanelSensorInterface signals to SensorSystem slots
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::gunStateChanged, this, &SensorSystem::onGunStateChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::fireModeStateInputChanged, this, &SensorSystem::onFireModeStateInputChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::loadAmmunitionStateChanged, this, &SensorSystem::onLoadAmmunitionStateChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::stationStateChanged, this, &SensorSystem::onStationStateChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::speedSwChanged, this, &SensorSystem::onSpeedSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::homeSwChanged, this, &SensorSystem::onHomeSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::stabilizationSwChanged, this, &SensorSystem::onStabilizationSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::authorizeSwChanged, this, &SensorSystem::onAuthorizeSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::camSwChanged, this, &SensorSystem::onCamSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::upSwChanged, this, &SensorSystem::onUpSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::downSwChanged, this, &SensorSystem::onDownSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::menuValSwChanged, this, &SensorSystem::onMenuValSwChanged);
    connect(m_plcPanelSensorInterface, &PLCPanelSensorInterface::panelTemperatureChanged, this, &SensorSystem::onPanelTemperatureChanged);

    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::stationUpperSensorStateChanged, this, &SensorSystem::onStationUpperSensorStateChanged);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::stationLowerSensorStateChanged, this, &SensorSystem::onStationLowerSensorStateChanged);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::stationAmmunitionLevelChanged, this, &SensorSystem::onStationAmmunitionLevelChanged);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::stationInput1Changed, this, &SensorSystem::onStationInput1Changed);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::stationInput2Changed, this, &SensorSystem::onStationInput2Changed);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::stationInput3Changed, this, &SensorSystem::onStationInput3Changed);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::eoTemperatureChanged, this, &SensorSystem::onEOTemperatureChanged);
    connect(m_plcStationSensorInterface, &PLCStationSensorInterface::eoPressureChanged, this, &SensorSystem::onEOPressureChanged);

    // m_plcStationSensorInterface is instantiated in the main class!
    m_plcPanelSensorInterface->connectDevice();
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

void SensorSystem::setPLCStationSensorInterface(PLCStationSensorInterface *sensorInterface) {
    if (m_plcStationSensorInterface) {
        // Disconnect previous connections if any
        disconnect(m_plcStationSensorInterface, nullptr, this, nullptr);
    }
    m_plcStationSensorInterface = sensorInterface;
    if (m_plcStationSensorInterface) {
        // Connect signals

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

PLCStationSensorInterface* SensorSystem::getPLCStationSensorInterface() const {
    return m_plcStationSensorInterface;
}

void SensorSystem::startMonitoringSensors() {

}

void SensorSystem::stopMonitoringSensors() {

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
    // Update DataModel
    m_dataModel->setGyroOrientation(Roll, Pitch, Pitch);
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
    // Update DataModel
    double distanceInMeters = distance / 100.0 + decimalPlaces / 10000.0;
    m_dataModel->setLRFDistance(distanceInMeters);

}

void SensorSystem::onGunStateChanged(bool state)
{
    m_plcPanelSensorInterface->writeData();
    m_dataModel->setGunEnabled(state);
}

void SensorSystem::onFireModeStateInputChanged(int mode)
{
    FireMode fireMode;

    switch (mode) {
    case 0:
        fireMode = FireMode::SingleShot;
        break;
    case 1:
        fireMode = FireMode::ShortBurst;
        break;
    case 2:
        fireMode = FireMode::LongBurst;
        break;
    default:
        // Handle invalid mode value, defaulting to SingleShot
        fireMode = FireMode::SingleShot;
        break;
    }

    m_dataModel->setFireMode(fireMode);
}

void SensorSystem::onLoadAmmunitionStateChanged(bool state)
{
    m_dataModel->setLoadAmmunition(state);
}

void SensorSystem::onStationStateChanged(bool state)
{
    m_dataModel->setStationState(state);
    m_plcPanelSensorInterface->writeData();
    if (state) {
        m_dataModel->setOperationalStateMode(OperationalMode::Surveillance);
    }
    else {
        m_dataModel->setOperationalStateMode(OperationalMode::Idle);
    }
}

void SensorSystem::onSpeedSwChanged(int speed)
{
    m_dataModel->setSpeedSw(speed);
}

void SensorSystem::onHomeSwChanged(bool state)
{
    m_dataModel->setHomeSw(state);
}

void SensorSystem::onStabilizationSwChanged(bool state)
{
    m_dataModel->setStabilizationSw(state);
}

void SensorSystem::onAuthorizeSwChanged(bool state)
{
    m_dataModel->setAuthorizeSw(state);
}

void SensorSystem::onCamSwChanged(bool state)
{
    m_dataModel->setCamActive(state);
}

void SensorSystem::onUpSwChanged(bool state)
{
    m_dataModel->setUpSw(state);
}

void SensorSystem::onDownSwChanged(bool state)
{
    m_dataModel->setDownSw(state);
}

void SensorSystem::onMenuValSwChanged(bool state)
{
    m_dataModel->setMenuValSw(state);
}

void SensorSystem::onPanelTemperatureChanged(int temperature)
{
    m_dataModel->setPanelTemperature(temperature);
}

//PLC Station Slots

void SensorSystem::onStationUpperSensorStateChanged(bool state)
{
    m_dataModel->setStationUpperSensor(state);
}

void SensorSystem::onStationLowerSensorStateChanged(bool state)
{
    m_dataModel->setStationLowerSensor(state);
}

void SensorSystem::onStationAmmunitionLevelChanged(bool state)
{
    m_dataModel->setStationAmmunitionLevel(state);
}

void SensorSystem::onStationInput1Changed(bool state)
{
    m_dataModel->setStationInput1(state);
}
void SensorSystem::onStationInput2Changed(bool state)
{
    m_dataModel->setStationInput2(state);
}
void SensorSystem::onStationInput3Changed(bool state)
{
    m_dataModel->setStationInput3(state);
}

void SensorSystem::onEOTemperatureChanged(int temperature)
{
    m_dataModel->setEOTemperature(temperature);
}
void SensorSystem::onEOPressureChanged(int pressure)
{
    m_dataModel->setEOPressure(pressure);
}
