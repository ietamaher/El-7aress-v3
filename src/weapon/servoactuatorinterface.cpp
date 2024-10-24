#include "include/weapon/servoactuatorinterface.h"
#include <QDebug>

ServoActuatorInterface::ServoActuatorInterface(QObject *parent)
    : QObject(parent),
      servoSerial(nullptr),
      timeoutTimer(new QTimer(this))
{
    connect(timeoutTimer, &QTimer::timeout, this, &ServoActuatorInterface::handleTimeout);
}

ServoActuatorInterface::~ServoActuatorInterface() {
    if (servoSerial) {
        servoSerial->close();
        servoSerial->deleteLater();
    }
}

void ServoActuatorInterface::setSerialPort(QSerialPort *serial) {
    if (servoSerial) {
        disconnect(servoSerial, &QSerialPort::readyRead, this, &ServoActuatorInterface::processIncomingData);
        servoSerial->close();
        servoSerial->deleteLater();
    }

    servoSerial = serial;
    if (servoSerial) {
        // Configure the serial port if necessary
        // servoSerial->setBaudRate(QSerialPort::Baud9600);
        // servoSerial->setDataBits(QSerialPort::Data8);
        // servoSerial->setParity(QSerialPort::NoParity);
        // servoSerial->setStopBits(QSerialPort::OneStop);
        // servoSerial->setFlowControl(QSerialPort::NoFlowControl);

        if (!servoSerial->isOpen()) {
            if (!servoSerial->open(QIODevice::ReadWrite)) {
                qWarning() << "Failed to open servo actuator serial port";
                return;
            }
        }

        connect(servoSerial, &QSerialPort::readyRead, this, &ServoActuatorInterface::processIncomingData);
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
            qWarning() << "Failed to write command to servo actuator";
        }
    } else {
        qWarning() << "Servo serial port is not open";
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
    qWarning() << "Timeout waiting for response from servo actuator";
    // Handle timeout (e.g., retry command, notify user)
}
