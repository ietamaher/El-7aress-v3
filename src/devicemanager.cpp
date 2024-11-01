// devicemanager.cpp
#include "include/devicemanager.h"
#include "include/comm/plcmodbusworker.h"
#include <QSerialPort>
//#include <QCamera>
#include <QDebug>
//#include "joystick.h" // Assume you have a Joystick class

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

DeviceManager& DeviceManager::instance()
{
    static DeviceManager instance;
    return instance;
}

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent)
{
    // Initialize all devices
    if (!initializePLCModbusCommunication()) {
        emit logMessage("Failed to initialize PLC Modbus Communication.");
    }
    if (!initializeSerialPorts()) {
        emit logMessage("Failed to initialize Serial Ports.");
    }
    if (!initializeCameras()) {
        emit logMessage("Failed to initialize Cameras.");
    }
    if (!initializeJoystick()) {
        emit logMessage("Failed to initialize Joystick.");
    }
}

DeviceManager::~DeviceManager()
{
    // Properly shutdown devices if necessary
}

bool DeviceManager::initializePLCModbusCommunication()
{
    // Example initialization parameters
    QString portName = "/dev/pts/333"; // Or read from config
    int baudRate = 115200;

    m_plcModbusComm = std::make_shared<PLCModbusCommunication>(portName, baudRate);
    connect(m_plcModbusComm.get(), &PLCModbusCommunication::logMessage, this, &DeviceManager::logMessage);
    return m_plcModbusComm->connectDevice();
}

bool DeviceManager::initializeSerialPorts()
{
    // Suppose you have 2 additional serial ports
    QStringList serialPortNames = {"/dev/pts/5", "/dev/pts/7", "/dev/pts/9"}; // Or read from config

    for (const auto &portName : serialPortNames) {
        auto serialPort = std::make_shared<QSerialPort>(portName);
        // Configure serial port parameters as needed
        serialPort->setBaudRate(QSerialPort::Baud9600);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (!serialPort->open(QIODevice::ReadWrite)) {
            emit logMessage(QString("Failed to open serial port: %1").arg(portName));
            continue; // Proceed with other ports
        }

        m_serialPorts.push_back(serialPort);
    }

    return !m_serialPorts.empty();
}

bool DeviceManager::initializeCameras()
{
    // Suppose you have 2 video devices: /dev/video1 and /dev/video2
/*    QStringList cameraDevicePaths = {"/dev/video1", "/dev/video2"};

    for (const auto &devicePath : cameraDevicePaths) {
        auto camera = std::make_shared<QCamera>(devicePath);
        // Configure camera parameters as needed
        camera->setCaptureMode(QCamera::CaptureVideo);

        camera->start(); // Start the camera

        if (camera->status() != QCamera::ActiveStatus) {
            emit logMessage(QString("Failed to start camera: %1").arg(devicePath));
            continue;
        }

        m_cameras.push_back(camera);
    }*/

    return true; //!m_cameras.empty();
}

bool DeviceManager::initializeJoystick()
{
    // Initialize your Joystick class (implementation depends on your joystick handling)
    /*m_joystick = std::make_shared<Joystick>();
    if (!m_joystick->initialize("/dev/input/js0")) { // Example device path
        emit logMessage("Failed to initialize Joystick.");
        return false;
    }

    connect(m_joystick.get(), &Joystick::logMessage, this, &DeviceManager::logMessage);*/
    return true;
}

std::shared_ptr<PLCModbusCommunication> DeviceManager::getPLCModbusCommunication()
{
    return m_plcModbusComm;
}

std::shared_ptr<QSerialPort> DeviceManager::getSerialPort(int index)
{
    if (index < 0 || index >= static_cast<int>(m_serialPorts.size()))
        return nullptr;
    return m_serialPorts[index];
}

std::shared_ptr<QCamera> DeviceManager::getCamera(int index)
{
    if (index < 0 || index >= static_cast<int>(m_cameras.size()))
        return nullptr;
    return m_cameras[index];
}

std::shared_ptr<Joystick> DeviceManager::getJoystick()
{
    return m_joystick;
}


bool DeviceManager::initializeFromConfig(const QString &configFilePath)
{
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly)) {
        emit logMessage("Failed to open config file.");
        return false;
    }

    QByteArray data = configFile.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    if (doc.isNull() || !doc.isObject()) {
        emit logMessage("Invalid config file format.");
        return false;
    }

    QJsonObject obj = doc.object();

    // Initialize PLC Modbus
    if (obj.contains("plcModbus") && obj["plcModbus"].isObject()) {
        QJsonObject plcObj = obj["plcModbus"].toObject();
        QString portName = plcObj["portName"].toString("COM3");
        int baudRate = plcObj["baudRate"].toInt(9600);
        m_plcModbusComm = std::make_shared<PLCModbusCommunication>(portName, baudRate);
        connect(m_plcModbusComm.get(), &PLCModbusWorker::logMessage, this, &DeviceManager::logMessage);
        if (!m_plcModbusComm->connectDevice()) {
            emit logMessage("Failed to connect PLC Modbus.");
        }
    }

    // Initialize Serial Ports
    if (obj.contains("serialPorts") && obj["serialPorts"].isArray()) {
        QJsonArray serialArray = obj["serialPorts"].toArray();
        for (const auto &portVal : serialArray) {
            if (portVal.isObject()) {
                QJsonObject portObj = portVal.toObject();
                QString portName = portObj["name"].toString();
                int baudRate = portObj["baudRate"].toInt(9600);
                auto serialPort = std::make_shared<QSerialPort>(portName);
                serialPort->setBaudRate(baudRate);
                // Set other serial port parameters as needed
                if (!serialPort->open(QIODevice::ReadWrite)) {
                    emit logMessage(QString("Failed to open serial port: %1").arg(portName));
                    continue;
                }
                m_serialPorts.push_back(serialPort);
            }
        }
    }

    // Initialize Cameras
    /*if (obj.contains("cameras") && obj["cameras"].isArray()) {
        QJsonArray camArray = obj["cameras"].toArray();
        for (const auto &camVal : camArray) {
            QString devicePath = camVal.toString();
            auto camera = std::make_shared<QCamera>(devicePath);
            camera->setCaptureMode(QCamera::CaptureVideo);
            camera->start();
            if (camera->status() != QCamera::ActiveStatus) {
                emit logMessage(QString("Failed to start camera: %1").arg(devicePath));
                continue;
            }
            m_cameras.push_back(camera);
        }
    }*/

    // Initialize Joystick
    /*if (obj.contains("joystick") && obj["joystick"].isString()) {
        QString joystickPath = obj["joystick"].toString();
        m_joystick = std::make_shared<Joystick>();
        if (!m_joystick->initialize(joystickPath)) {
            emit logMessage("Failed to initialize Joystick.");
        }
        connect(m_joystick.get(), &Joystick::logMessage, this, &DeviceManager::logMessage);
    }*/

    return true;
}
