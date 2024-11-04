#include "include/datamodel.h"

DataModel::DataModel(QObject *parent)
    : QObject(parent),
      m_lrfDistance(0.0),
      m_azimuthAngle(0.0),
      m_elevationAngle(0.0),
      m_gimbalSpeed(0.0)
{
    m_systemTime = QDateTime::currentDateTime();
}

// Setters

void DataModel::setOperationalStateMode(const QString &mode) {
    QMutexLocker locker(&m_mutex);
    m_operationalStateMode = mode;
}

void DataModel::setMotionMode(const QString &mode) {
    QMutexLocker locker(&m_mutex);
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

QString DataModel::getOperationalStateMode() {
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
