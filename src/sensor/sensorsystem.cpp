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
    SerialPortManager *portManager = new SerialPortManager(this);


    // Initialize LRF Interface
    m_lrfInterface = new LRFInterface();
    QSerialPort* lrfSerial = new QSerialPort(this);
    lrfSerial->setPortName("/dev/pts/1"); // Adjust as necessary
    lrfSerial->setBaudRate(QSerialPort::Baud9600);
    lrfSerial->setDataBits(QSerialPort::Data8);
    lrfSerial->setParity(QSerialPort::NoParity);
    lrfSerial->setStopBits(QSerialPort::OneStop);
    lrfSerial->setFlowControl(QSerialPort::NoFlowControl);


    if (lrfSerial->open(QIODevice::ReadWrite)) {
        m_lrfInterface->setSerialPort(lrfSerial);
    } else {
        qWarning() << "Failed to open LRF serial port";
        lrfSerial->deleteLater();
    }
    setLRFInterface(m_lrfInterface);



    //in case inned to move it to thread uncomment this
    //m_lrfThread = new QThread(this);
    //m_lrfInterface->moveToThread(m_lrfThread);


    m_radarInterface = new RadarInterface();
    radarSerial = portManager->configureSerialPort("/dev/pts/6",QSerialPort::Baud4800,QSerialPort::Data8);
    m_radarInterface->setSerialPort(radarSerial);

    m_gyroInterface = new GyroInterface();
    gyroSerial = portManager->configureSerialPort("/dev/pts/9",QSerialPort::Baud115200,QSerialPort::Data8);
    m_gyroInterface->setSerialPort(gyroSerial);

    //m_plcSensorInterface = new PLCSensorInterface();
    //plcSerial = portManager->configureSerialPort("/dev/pts/5",QSerialPort::Baud115200,QSerialPort::Data8);
    //m_plcSensorInterface->setSerialPort(plcSerial);

}

SensorSystem::~SensorSystem()
{
    //m_lrfThread->quit();
    //m_lrfThread->wait();
    delete m_lrfInterface;
}

// Setter methods
void SensorSystem::setLRFInterface(LRFInterface *lrfInterface) {
    m_lrfInterface = lrfInterface;
    // Clean up when thread finishes
    //connect(m_lrfThread, &QThread::finished, m_lrfInterface, &QObject::deleteLater);

    // Connect LRFInterface signals to SensorSystem signals
    connect(m_lrfInterface, &LRFInterface::errorOccurred, this, &SensorSystem::handleErrorOccurred);
    connect(m_lrfInterface, &LRFInterface::frequencySet, this, &SensorSystem::handleFrequencySet);
    connect(m_lrfInterface, &LRFInterface::settingValueReceived, this, &SensorSystem::handleSettingValueReceived);
    connect(m_lrfInterface, &LRFInterface::laserCountReceived, this, &SensorSystem::handleLaserCountReceived);
    connect(m_lrfInterface, &LRFInterface::selfCheckResult, this, &SensorSystem::handleSelfCheckResult);
    connect(m_lrfInterface, &LRFInterface::rangingDataReceived, this, &SensorSystem::handleRangingDataReceived);

    //m_lrfThread->start();
}

void SensorSystem::setGyroInterface(GyroInterface *gyroInterface) {
    m_gyroInterface = gyroInterface;
    connect(m_gyroInterface, &GyroInterface::gyroDataReceived, this, &SensorSystem::onGyroDataReceived);
}

void SensorSystem::setRadarInterface(RadarInterface *radarInterface) {
    m_radarInterface = radarInterface;
    // Connect signals and slots if necessary
}

void SensorSystem::setPLCSensorInterface(PLCSensorInterface *sensorInterface) {
    m_plcSensorInterface = sensorInterface;
    // Connect signals
    connect(m_plcSensorInterface, &PLCSensorInterface::proximitySensorActivated, this, &SensorSystem::proximitySensorActivated);
    connect(m_plcSensorInterface, &PLCSensorInterface::temperatureUpdated, this, &SensorSystem::temperatureUpdated);
    connect(m_plcSensorInterface, &PLCSensorInterface::pressureUpdated, this, &SensorSystem::pressureUpdated);}


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

void SensorSystem::activateSensors(bool activate)
{
    m_sensorsActive = activate;
    // Activate other sensors if necessary
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

void SensorSystem::activateLRF()
{
    if (!m_sensorsActive)
        return;

    m_lrfActive = true;
    sendContinuousRanging();
}

void SensorSystem::deactivateLRF()
{
    m_lrfActive = false;
    stopRanging();
}


void SensorSystem::enableStabilization() {
    m_stabilizationEnabled = true;
    // Start gyro data acquisition
    m_gyroInterface->start();
}

void SensorSystem::disableStabilization() {
    m_stabilizationEnabled = false;
    // Stop gyro data acquisition
    m_gyroInterface->stop();
}


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

void SensorSystem::activateTrackingSensors(bool activate)
{
    m_trackingSensorsActive = activate;
    if (activate) {
        // Activate sensors needed for tracking
        qDebug() << "Tracking sensors activated.";
        // For example, start receiving data from tracking sensors
    } else {
        // Deactivate tracking sensors
        qDebug() << "Tracking sensors deactivated.";
        // Stop receiving data from tracking sensors
    }
}

void SensorSystem::activateEngagementSensors(bool activate)
{
    m_engagementSensorsActive = activate;
    if (activate) {
        // Activate sensors needed for engagement
        qDebug() << "Engagement sensors activated.";
        // For example, prepare LRF or other engagement-related sensors
        activateLRF();
    } else {
        // Deactivate engagement sensors
        qDebug() << "Engagement sensors deactivated.";
        // Stop LRF or other engagement-related sensors
        deactivateLRF();
    }
}

// Methods to send commands to LRFInterface
void SensorSystem::sendSelfCheck()
{
    QMetaObject::invokeMethod(m_lrfInterface, "sendSelfCheck", Qt::QueuedConnection);
}

void SensorSystem::sendSingleRanging()
{
    QMetaObject::invokeMethod(m_lrfInterface, "sendSingleRanging", Qt::QueuedConnection);
}

void SensorSystem::sendContinuousRanging()
{
    QMetaObject::invokeMethod(m_lrfInterface, "sendContinuousRanging", Qt::QueuedConnection);
}

void SensorSystem::stopRanging()
{
    QMetaObject::invokeMethod(m_lrfInterface, "stopRanging", Qt::QueuedConnection);
}

void SensorSystem::setFrequency(int frequency)
{
    QMetaObject::invokeMethod(m_lrfInterface, "setFrequency", Qt::QueuedConnection, Q_ARG(int, frequency));
}

void SensorSystem::querySettingValue()
{
    QMetaObject::invokeMethod(m_lrfInterface, "querySettingValue", Qt::QueuedConnection);
}

void SensorSystem::queryAccumulatedLaserCount()
{
    QMetaObject::invokeMethod(m_lrfInterface, "queryAccumulatedLaserCount", Qt::QueuedConnection);
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
