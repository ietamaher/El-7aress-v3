#include "include/weapon/servoactuatorinterface.h"
#include <QDebug>

ServoActuatorInterface::ServoActuatorInterface(QObject *parent)
    : QObject(parent),
      servoSerial(new QSerialPort(this)), m_isConnected(false),
      timeoutTimer(new QTimer(this))
{
    connect(timeoutTimer, &QTimer::timeout, this, &ServoActuatorInterface::handleTimeout);
}

ServoActuatorInterface::~ServoActuatorInterface()
{
    shutdown();
}

bool ServoActuatorInterface::openSerialPort(const QString &portName) {
    if (servoSerial->isOpen()) {
        servoSerial->close();
    }

    servoSerial->setPortName(portName);
    servoSerial->setBaudRate(QSerialPort::Baud4800);
    servoSerial->setDataBits(QSerialPort::Data8);
    servoSerial->setParity(QSerialPort::NoParity);
    servoSerial->setStopBits(QSerialPort::OneStop);
    servoSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (servoSerial->open(QIODevice::ReadOnly)) {
        connect(servoSerial, &QSerialPort::readyRead, this, &ServoActuatorInterface::processIncomingData);
        connect(servoSerial, &QSerialPort::errorOccurred, this, &ServoActuatorInterface::handleSerialError);
        qDebug() << "Opened radar serial port:" << portName;
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        return true;
    } else {
       qDebug() << "Failed to open actuator serial port:" << servoSerial->errorString();
        emit errorOccurred(servoSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void ServoActuatorInterface::closeSerialPort() {
    if (servoSerial->isOpen()) {
        servoSerial->close();
        qDebug() << "Closed radar serial port:" << servoSerial->portName();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
    }
}

void ServoActuatorInterface::shutdown() {
    closeSerialPort();
    // Additional cleanup if necessary
}



void ServoActuatorInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
       qDebug() << "Radar serial port error occurred:" << servoSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &ServoActuatorInterface::attemptReconnection);
    }
}

void ServoActuatorInterface::attemptReconnection() {
    if (!servoSerial->isOpen()) {
        if (openSerialPort(servoSerial->portName())) {
            qDebug() << "Radar serial port reconnected.";
            // Reinitialize if necessary
        } else {
           qDebug() << "Failed to reopen actuator serial port:" << servoSerial->errorString();
            // Retry after some time
            QTimer::singleShot(5000, this, &ServoActuatorInterface::attemptReconnection);
        }
    }
}

void ServoActuatorInterface::sendCommand(const QString &command) {
    if (servoSerial && servoSerial->isOpen()) {
        QString fullCommand = command + "\r";
        servoSerial->write(fullCommand.toUtf8());
        if (servoSerial->waitForBytesWritten(100)) {
            emit commandSent(command);
            // Start timeout timer to wait for a response
            timeoutTimer->start(1000); // Adjust timeout as needed
        } else {
           qDebug() << "Failed to write command to servo actuator";
        }
    } else {
       qDebug() << "Servo serial port is not open";
    }
}

void ServoActuatorInterface::moveToPosition(int position) {
    QString command = QString("TA %1").arg(position);
    sendCommand(command);
}

void ServoActuatorInterface::checkStatus() {
    QString command = "STATUS"; // Replace with actual status command
    sendCommand(command);
}

void ServoActuatorInterface::checkAlarms() {
    QString command = "ALARM"; // Replace with actual alarm command
    sendCommand(command);
}

void ServoActuatorInterface::processIncomingData() {
    if (!servoSerial)
        return;

    buffer.append(servoSerial->readAll());

    // Process responses terminated by carriage return '\r'
    while (buffer.contains('\r')) {
        int endIndex = buffer.indexOf('\r');
        QByteArray responseData = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);

        QString response = QString::fromUtf8(responseData);

        emit responseReceived(response);

        // Parse the response and emit appropriate signals
        if (response.startsWith("OK")) {
            // Command acknowledged
            // Handle as needed
        } else if (response.startsWith("POSITION")) {
            // Parse position information
            QStringList parts = response.split(' ');
            if (parts.size() >= 2) {
                bool ok;
                int position = parts[1].toInt(&ok);
                if (ok) {
                    emit positionReached(position);
                }
            }
        } else if (response.startsWith("STATUS")) {
            // Parse status information
            emit statusUpdated(response);
        } else if (response.startsWith("ALARM")) {
            // Parse alarm information
            emit alarmDetected(response);
        } else {
            // Handle other responses
        }

        // Stop the timeout timer since we received a response
        timeoutTimer->stop();
    }
}

void ServoActuatorInterface::handleTimeout() {
   qDebug() << "Timeout waiting for response from servo actuator";
    // Handle timeout (e.g., retry command, notify user)
}
