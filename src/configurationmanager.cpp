  // devicemanager.cpp (partial)
#include "devicemanager.h"
#include "configurationmanager.h"

void DeviceManager::initializeDevices() {
    // Load configurations
    QSettings* settings = ConfigurationManager::instance().settings();

    // Initialize Modbus Communication
    QString portName = ConfigurationManager::instance().modbusPortName();
    int baudRate = ConfigurationManager::instance().modbusBaudRate();
    QString parityStr = settings->value("Modbus/Parity", "N").toString();
    char parity = parityStr.isEmpty() ? 'N' : parityStr[0].toLatin1();
    int dataBits = settings->value("Modbus/DataBits", 8).toInt();
    int stopBits = settings->value("Modbus/StopBits", 1).toInt();
    int timeout = settings->value("Modbus/Timeout", 1000).toInt();

    m_modbusComm = new PLCModbusCommunication(portName, baudRate, parity, dataBits, stopBits, timeout, this);
    connect(m_modbusComm, &PLCModbusCommunication::logMessage, this, &DeviceManager::logMessage);
    if (!m_modbusComm->connectDevice()) {
        emit logMessage("Failed to connect Modbus device.");
    }

    // Initialize Video Capture
    QString videoDevice = ConfigurationManager::instance().videoDevice();
    int resWidth = settings->value("Video/ResolutionWidth", 1920).toInt();
    int resHeight = settings->value("Video/ResolutionHeight", 1080).toInt();
    int frameRate = settings->value("Video/FrameRate", 30).toInt();
    m_videoCapture = new VideoCapture(videoDevice, resWidth, resHeight, frameRate, this);
    connect(m_videoCapture, &VideoCapture::logMessage, this, &DeviceManager::logMessage);
    m_videoCapture->start();

    // Initialize Joystick
    QString joystickDevice = ConfigurationManager::instance().joystickDevice();
    int deadzone = settings->value("Joystick/Deadzone", 8000).toInt();
    m_joystick = new Joystick(joystickDevice, deadzone, this);
    connect(m_joystick, &Joystick::logMessage, this, &DeviceManager::logMessage);
    m_joystick->initialize();
}

