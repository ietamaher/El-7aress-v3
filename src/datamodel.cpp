#include "include/datamodel.h"

DataModel::DataModel(QObject *parent)
    : QObject(parent),
      m_lrfDistance(0.0),
      m_azimuthAngle(0.0),
      m_elevationAngle(0.0),
      m_gimbalSpeed(0.0),
    m_gunEnabled(false),
    m_fireMode(FireMode::SingleShot),
    m_loadAmmunition(false),
    m_stationState(false),
    m_speedSw(false),
    m_homeSw(false),
    m_stabilizationSw(false),
    m_authorizeSw(false),
    m_activeCamera(false),
    m_upSw(false),
    m_downSw(false),
    m_menuValSw(false),
    m_panelTemperature(0),
    m_stationUpperSensor(false),
    m_stationLowerSensor(false),
    m_stationAmmunitionLevel(false),
    m_stationInput1(false),
    m_stationInput2(false),
    m_stationInput3(false),
    m_stationTemperature(0),
    m_stationPressure(0)


{
    m_systemTime = QDateTime::currentDateTime();
}

// Setters

void DataModel::setOperationalStateMode(const OperationalMode &mode) {
    QMutexLocker locker(&m_mutex);
    if (m_operationalStateMode != mode) {
        m_operationalStateMode = mode;
        emit operationalStateModeChange(mode);
    }
}

void DataModel::setMotionMode(const QString &mode) {
    //QMutexLocker locker(&m_mutex);
    m_motionMode = mode;
}

void DataModel::setLRFDistance(double distance) {
    QMutexLocker locker(&m_mutex);
    m_lrfDistance = distance;
}



void DataModel::setGimbalSpeed(double speed) {
    QMutexLocker locker(&m_mutex);
    m_gimbalSpeed = speed;
}

void DataModel::setCrosshairPosition(const QPointF &position) {
    QMutexLocker locker(&m_mutex);
    m_crosshairPosition = position;
}

void DataModel::setWeaponSystemStatus(const QString &status) {
    QMutexLocker locker(&m_mutex);
    m_weaponSystemStatus = status;
}

void DataModel::setTargetInformation(const QString &info) {
    QMutexLocker locker(&m_mutex);
    m_targetInformation = info;
}

void DataModel::setSystemTime(const QDateTime &time) {
    QMutexLocker locker(&m_mutex);
    m_systemTime = time;
}

void DataModel::setGPSCoordinates(const QString &coordinates) {
    QMutexLocker locker(&m_mutex);
    m_gpsCoordinates = coordinates;
}

void DataModel::setSensorReadings(const QString &readings) {
    QMutexLocker locker(&m_mutex);
    m_sensorReadings = readings;
}

void DataModel::setAlertsWarnings(const QString &alerts) {
    QMutexLocker locker(&m_mutex);
    m_alertsWarnings = alerts;
}
void DataModel::setGyroOrientation(double roll, double pitch, double yaw) {
    QMutexLocker locker(&m_mutex);
    m_roll = roll;
    m_pitch = pitch;
    m_yaw = yaw;
}

void DataModel::setDetectionEnabled(bool enabled) {
    QMutexLocker locker(&m_mutex);
    m_detectionEnabled = enabled;
}

void DataModel::setStabilizationEnabled(bool enabled) {
    QMutexLocker locker(&m_mutex);
    m_stabilizationEnabled = enabled;
}
// Getters

OperationalMode DataModel::getOperationalStateMode() {
    QMutexLocker locker(&m_mutex);
    return m_operationalStateMode;
}

QString DataModel::getMotionMode() {
    QMutexLocker locker(&m_mutex);
    return m_motionMode;
}

double DataModel::getLRFDistance() {
    QMutexLocker locker(&m_mutex);
    return m_lrfDistance;
}

void DataModel::setGimbalOrientation(double azimuth, double elevation) {
    QMutexLocker locker(&m_mutex);
    if (azimuth >= 0.0 && azimuth <= 360.0) {
        m_azimuthAngle = azimuth;
    }
    if (elevation >= -90.0 && elevation <= 90.0) {
        m_elevationAngle = elevation;
    }
}

void DataModel::setGunEnabled(bool enabled)
{
    QMutexLocker locker(&m_mutex);
    if (m_gunEnabled != enabled) {
        m_gunEnabled = enabled;
        emit dataModelUpdated();
    }
}

void DataModel::setFireMode(FireMode mode)
{
    QMutexLocker locker(&m_mutex);
    if (m_fireMode != mode) {
        m_fireMode = mode;
        emit fireModeChanged(mode);
    }
}

void DataModel::setLoadAmmunition(bool loaded)
{
    QMutexLocker locker(&m_mutex);
    if (m_loadAmmunition != loaded) {
        m_loadAmmunition = loaded;
        emit dataModelUpdated();
    }
}

void DataModel::setStationState(bool state)
{
    QMutexLocker locker(&m_mutex);
    if (m_stationState != state) {
        m_stationState = state;
        emit dataModelUpdated();
    }
}

void DataModel::setSpeedSw(int speed)
{
    QMutexLocker locker(&m_mutex);
    if (m_speedSw != speed) {
        m_speedSw = speed;
        emit dataModelUpdated();
    }
}

void DataModel::setHomeSw(bool state)
{
    QMutexLocker locker(&m_mutex);
    if (m_homeSw != state) {
        m_homeSw = state;
        emit dataModelUpdated();
    }
}

void DataModel::setStabilizationSw(bool state)
{
    QMutexLocker locker(&m_mutex);
    if (m_stabilizationSw != state) {
        m_stabilizationSw = state;
        emit dataModelUpdated();
    }
}

void DataModel::setAuthorizeSw(bool state)
{
    QMutexLocker locker(&m_mutex);
    if (m_authorizeSw != state) {
        m_authorizeSw = state;
        emit dataModelUpdated();
    }
}

void DataModel::setCamActive(bool state)
{
    QMutexLocker locker(&m_mutex);
    if (m_activeCamera != state) {
        m_activeCamera = state;
        emit dataModelUpdated();
    }
}

void DataModel::setUpSw(bool state)
{
    //QMutexLocker locker(&m_mutex);
    if (m_upSw != state) {
        m_upSw = state;
        emit upSwChanged(state);
    }
}



void DataModel::setDownSw(bool state)
{
    //QMutexLocker locker(&m_mutex);
    if (m_downSw != state) {
        m_downSw = state;
        emit downSwChanged( state);
    }
}

void DataModel::setMenuValSw(bool state)
{
    //QMutexLocker locker(&m_mutex);
    if (m_menuValSw != state) {
        m_menuValSw = state;
        emit menuValSwChanged( state);
    }
}

void DataModel::setPanelTemperature(int temperature)
{
    QMutexLocker locker(&m_mutex);
    if (m_panelTemperature != temperature) {
        m_panelTemperature = temperature;
        emit dataModelUpdated();
    }
}


void DataModel::setStationUpperSensor(bool state)
{
    if (m_stationUpperSensor != state) {
        m_stationUpperSensor = state;
        // You can emit a signal here if needed
    }
}

void DataModel::setStationLowerSensor(bool state)
{
    if (m_stationLowerSensor != state) {
        m_stationLowerSensor = state;
        // Emit signal if necessary
    }
}

void DataModel::setStationAmmunitionLevel(bool state)
{
    if (m_stationAmmunitionLevel != state) {
        m_stationAmmunitionLevel = state;
        // Emit signal if necessary
    }
}

void DataModel::setStationInput1(bool state)
{
    if (m_stationInput1 != state) {
        m_stationInput1 = state;
        // Emit signal if necessary
    }
}

void DataModel::setStationInput2(bool state)
{
    if (m_stationInput2 != state) {
        m_stationInput2 = state;
        // Emit signal if necessary
    }
}

void DataModel::setStationInput3(bool state)
{
    if (m_stationInput3 != state) {
        m_stationInput3 = state;
        // Emit signal if necessary
    }
}

void DataModel::setEOTemperature(int temperature)
{
    if (m_stationTemperature != temperature) {
        m_stationTemperature = temperature;
        // Emit signal if necessary
    }
}

void DataModel::setEOPressure(int pressure)
{
    if (m_stationPressure != pressure) {
        m_stationPressure = pressure;
        // Emit signal if necessary
    }
}


void DataModel::setReticleStyle(const QString &style) {
    QMutexLocker locker(&m_mutex);
    if (m_reticleStyle != style) {
        m_reticleStyle = style;
        emit reticleStyleChanged(style);
    }
}


/* GETTERS */

double DataModel::getGimbalSpeed() {
    QMutexLocker locker(&m_mutex);
    return m_gimbalSpeed;
}

void DataModel::getGimbalOrientation(double &azimuth, double &elevation) {
    QMutexLocker locker(&m_mutex);
    azimuth = m_azimuthAngle;
    elevation =  m_elevationAngle;
}
QPointF DataModel::getCrosshairPosition() {
    QMutexLocker locker(&m_mutex);
    return m_crosshairPosition;
}

QString DataModel::getWeaponSystemStatus() {
    QMutexLocker locker(&m_mutex);
    return m_weaponSystemStatus;
}

QString DataModel::getTargetInformation() {
    QMutexLocker locker(&m_mutex);
    return m_targetInformation;
}

QDateTime DataModel::getSystemTime() {
    QMutexLocker locker(&m_mutex);
    return m_systemTime;
}

QString DataModel::getGPSCoordinates() {
    QMutexLocker locker(&m_mutex);
    return m_gpsCoordinates;
}

QString DataModel::getSensorReadings() {
    QMutexLocker locker(&m_mutex);
    return m_sensorReadings;
}

QString DataModel::getAlertsWarnings() {
    QMutexLocker locker(&m_mutex);
    return m_alertsWarnings;
}

void DataModel::getGyroOrientation(double &roll, double &pitch, double &yaw) {
    QMutexLocker locker(&m_mutex);
    roll = m_roll;
    pitch = m_pitch;
    yaw = m_yaw;
}

bool DataModel::isDetectionEnabled() {
    QMutexLocker locker(&m_mutex);
    return m_detectionEnabled;
}


bool DataModel::isStabilizationEnabled() {
    QMutexLocker locker(&m_mutex);
    return m_stabilizationEnabled;
}


bool DataModel::isGunEnabled()
{
    QMutexLocker locker(&m_mutex);
    return m_gunEnabled;
}

FireMode DataModel::getFireMode()
{
    QMutexLocker locker(&m_mutex);
    return m_fireMode;
}

bool DataModel::isLoadAmmunition()
{
    QMutexLocker locker(&m_mutex);
    return m_loadAmmunition;
}

bool DataModel::getStationState()
{
    QMutexLocker locker(&m_mutex);
    return m_stationState;
}

int DataModel::getSpeedSw()
{
    QMutexLocker locker(&m_mutex);
    return m_speedSw;
}



bool DataModel::getHomeSw()
{
    QMutexLocker locker(&m_mutex);
    return m_homeSw;
}

bool DataModel::getStabilizationSw()
{
    QMutexLocker locker(&m_mutex);
    return m_stabilizationSw;
}

bool DataModel::getAuthorizeSw()
{
    QMutexLocker locker(&m_mutex);
    return m_authorizeSw;
}

bool DataModel::getCamera()
{
    QMutexLocker locker(&m_mutex);
    return m_activeCamera;
}

bool DataModel::getUpSw()
{
    QMutexLocker locker(&m_mutex);
    return m_upSw;
}

bool DataModel::getDownSw()
{
    QMutexLocker locker(&m_mutex);
    return m_downSw;
}

bool DataModel::getMenuValSw()
{
    QMutexLocker locker(&m_mutex);
    return m_menuValSw;
}

int DataModel::getPanelTemperature()
{
    QMutexLocker locker(&m_mutex);
    return m_panelTemperature;
}

bool DataModel::getStationUpperSensor()
{
    return m_stationUpperSensor;
}

bool DataModel::getStationLowerSensor()
{
    return m_stationLowerSensor;
}

bool DataModel::getStationAmmunitionLevel()
{
    return m_stationAmmunitionLevel;
}

bool DataModel::getStationInput1()
{
    return m_stationInput1;
}

bool DataModel::getStationInput2()
{
    return m_stationInput2;
}

bool DataModel::getStationInput3()
{
    return m_stationInput3;
}

int DataModel::getEOTemperature()
{
    return m_stationTemperature;
}

int DataModel::getEOPressure()
{
    return m_stationPressure;
}


QString DataModel::getReticleStyle() {
    //QMutexLocker locker(&m_mutex);
    return m_reticleStyle;
}
