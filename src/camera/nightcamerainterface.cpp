#include "include/camera/nightcamerainterface.h"
#include <QDebug>
#include <QTimer>

NightCameraInterface::NightCameraInterface(QObject *parent)
    : QObject(parent), cameraSerial(new QSerialPort(this)), m_isConnected(false)
{
}

NightCameraInterface::~NightCameraInterface() {
    shutdown();
}

bool NightCameraInterface::openSerialPort(const QString &portName) {
    if (cameraSerial->isOpen()) {
        cameraSerial->close();
    }

    cameraSerial->setPortName(portName);
    cameraSerial->setBaudRate(QSerialPort::Baud115200);//Baud921600); // Boson default baud rate
    cameraSerial->setDataBits(QSerialPort::Data8);
    cameraSerial->setParity(QSerialPort::NoParity);
    cameraSerial->setStopBits(QSerialPort::OneStop);
    cameraSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (cameraSerial->open(QIODevice::ReadWrite)) {
        connect(cameraSerial, &QSerialPort::readyRead, this, &NightCameraInterface::processIncomingData);
        connect(cameraSerial, &QSerialPort::errorOccurred, this, &NightCameraInterface::handleSerialError);
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        qDebug() << "Opened night camera serial port:" << portName;
        return true;
    } else {
        qWarning() << "Failed to open night camera serial port:" << cameraSerial->errorString();
        emit errorOccurred(cameraSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void NightCameraInterface::closeSerialPort() {
    if (cameraSerial->isOpen()) {
        cameraSerial->close();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        qDebug() << "Closed night camera serial port:" << cameraSerial->portName();
    }
}

void NightCameraInterface::shutdown() {
    closeSerialPort();
    // Additional cleanup if necessary
}

void NightCameraInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
        qWarning() << "Night camera serial port error occurred:" << cameraSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &NightCameraInterface::attemptReconnection);
    }
}

void NightCameraInterface::attemptReconnection() {
    if (!cameraSerial->isOpen()) {
        if (openSerialPort(cameraSerial->portName())) {
            qDebug() << "Night camera serial port reconnected.";
            // Reinitialize if necessary
        } else {
            qWarning() << "Failed to reopen night camera serial port:" << cameraSerial->errorString();
            QTimer::singleShot(5000, this, &NightCameraInterface::attemptReconnection);
        }
    }
}

void NightCameraInterface::sendCommand(const QByteArray &command) {
    if (cameraSerial && cameraSerial->isOpen()) {
        cameraSerial->write(command);
        if (!cameraSerial->waitForBytesWritten(100)) {
            emit errorOccurred("Failed to write to night camera serial port.");
        }
    } else {
        emit errorOccurred("Night camera serial port is not open.");
    }
}

void NightCameraInterface::processIncomingData() {
    incomingBuffer.append(cameraSerial->readAll());

    // Process incoming data as per FLIR Boson protocol
    // For simplicity, emit the raw response
    emit responseReceived(incomingBuffer);
    incomingBuffer.clear();
}

// Implement camera control methods
void NightCameraInterface::performFFC() {
    // Command to perform Flat Field Correction
    // The actual command depends on the Boson protocol
    QByteArray command; // Fill with appropriate command bytes
    sendCommand(command);
}

void NightCameraInterface::setDigitalZoom(quint8 zoomLevel) {
    // Command to set digital zoom
    QByteArray command; // Fill with appropriate command bytes
    sendCommand(command);
}

void NightCameraInterface::getCameraStatus() {
    // Command to get camera status
    QByteArray command; // Fill with appropriate command bytes
    sendCommand(command);
}

