#include "include/camera/dayCamerainterface.h"
#include <QDebug>
#include <QTimer>

DayCameraInterface::DayCameraInterface(QObject *parent)
    : QObject(parent), cameraSerial(new QSerialPort(this)), m_isConnected(false)
{
}

DayCameraInterface::~DayCameraInterface() {
    shutdown();
}

bool DayCameraInterface::openSerialPort(const QString &portName) {
    if (cameraSerial->isOpen()) {
        cameraSerial->close();
    }

    cameraSerial->setPortName(portName);
    cameraSerial->setBaudRate(QSerialPort::Baud9600);
    cameraSerial->setDataBits(QSerialPort::Data8);
    cameraSerial->setParity(QSerialPort::NoParity);
    cameraSerial->setStopBits(QSerialPort::OneStop);
    cameraSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (cameraSerial->open(QIODevice::ReadWrite)) {
        connect(cameraSerial, &QSerialPort::readyRead, this, &DayCameraInterface::processIncomingData);
        connect(cameraSerial, &QSerialPort::errorOccurred, this, &DayCameraInterface::handleSerialError);
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        qDebug() << "Opened day camera serial port:" << portName;
        return true;
    } else {
        qWarning() << "Failed to open day camera serial port:" << cameraSerial->errorString();
        emit errorOccurred(cameraSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void DayCameraInterface::closeSerialPort() {
    if (cameraSerial->isOpen()) {
        cameraSerial->close();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        qDebug() << "Closed day camera serial port:" << cameraSerial->portName();
    }
}

void DayCameraInterface::shutdown() {
    closeSerialPort();
    // Additional cleanup if necessary
}

void DayCameraInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
        qWarning() << "Day camera serial port error occurred:" << cameraSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &DayCameraInterface::attemptReconnection);
    }
}

void DayCameraInterface::attemptReconnection() {
    if (!cameraSerial->isOpen()) {
        if (openSerialPort(cameraSerial->portName())) {
            qDebug() << "Day camera serial port reconnected.";
            // Reinitialize if necessary
        } else {
            qWarning() << "Failed to reopen day camera serial port:" << cameraSerial->errorString();
            QTimer::singleShot(5000, this, &DayCameraInterface::attemptReconnection);
        }
    }
}

void DayCameraInterface::sendCommand(const QByteArray &command) {
    if (cameraSerial && cameraSerial->isOpen()) {
        cameraSerial->write(command);
        if (!cameraSerial->waitForBytesWritten(100)) {
            emit errorOccurred("Failed to write to day camera serial port.");
        }
    } else {
        emit errorOccurred("Day camera serial port is not open.");
    }
}

void DayCameraInterface::processIncomingData() {
    incomingBuffer.append(cameraSerial->readAll());

    // Process incoming data as per Visca protocol
    // For simplicity, emit the raw response
    emit responseReceived(incomingBuffer);
    incomingBuffer.clear();
}

// Visca Command Implementations
void DayCameraInterface::zoomIn() {
    // Command: 8x 01 04 07 2p FF (where p=2 for zoom tele standard speed)
    QByteArray command = QByteArray::fromHex("8101040725FF");
    sendCommand(command);
}

void DayCameraInterface::zoomOut() {
    // Command: 8x 01 04 07 3p FF (where p=2 for zoom wide standard speed)
    QByteArray command = QByteArray::fromHex("8101040735FF");
    sendCommand(command);
}

void DayCameraInterface::zoomStop() {
    // Command: 8x 01 04 07 00 FF
    QByteArray command = QByteArray::fromHex("8101040700FF");
    sendCommand(command);
}

void DayCameraInterface::setZoomPosition(quint16 position) {
    // Command: 8x 01 04 47 0p 0q 0r 0s FF (p,q,r,s are zoom position bytes)
    // Zoom position is typically a 14-bit value (0x0000 to 0x4000)
    quint16 zoomPos = position & 0x3FFF; // Ensure 14-bit
    QByteArray command = QByteArray::fromHex("81010447");
    command.append((zoomPos >> 12) & 0x0F);
    command.append((zoomPos >> 8) & 0x0F);
    command.append((zoomPos >> 4) & 0x0F);
    command.append(zoomPos & 0x0F);
    command.append(0xFF);
    sendCommand(command);
}

void DayCameraInterface::focusNear() {
    // Command: 8x 01 04 08 03 FF
    QByteArray command = QByteArray::fromHex("8101040803FF");
    sendCommand(command);
}

void DayCameraInterface::focusFar() {
    // Command: 8x 01 04 08 02 FF
    QByteArray command = QByteArray::fromHex("8101040802FF");
    sendCommand(command);
}

void DayCameraInterface::focusStop() {
    // Command: 8x 01 04 08 00 FF
    QByteArray command = QByteArray::fromHex("8101040800FF");
    sendCommand(command);
}

void DayCameraInterface::setFocusAuto(bool enabled) {
    // Command: 8x 01 04 38 02 FF (Auto Focus On)
    // Command: 8x 01 04 38 03 FF (Auto Focus Off)
    QByteArray command = QByteArray::fromHex("81010438");
    command.append(enabled ? 0x02 : 0x03);
    command.append(0xFF);
    sendCommand(command);
}

void DayCameraInterface::setFocusPosition(quint16 position) {
    // Command: 8x 01 04 48 0p 0q 0r 0s FF (p,q,r,s are focus position bytes)
    // Focus position is typically a 12-bit value (0x0000 to 0x1000)
    quint16 focusPos = position & 0x0FFF; // Ensure 12-bit
    QByteArray command = QByteArray::fromHex("81010448");
    command.append((focusPos >> 12) & 0x0F);
    command.append((focusPos >> 8) & 0x0F);
    command.append((focusPos >> 4) & 0x0F);
    command.append(focusPos & 0x0F);
    command.append(0xFF);
    sendCommand(command);
}

void DayCameraInterface::getCameraStatus() {
    // Implement status inquiry commands as needed
    // For example, inquire zoom position: 8x 09 04 47 FF
    QByteArray command = QByteArray::fromHex("81090447FF");
    sendCommand(command);
}
