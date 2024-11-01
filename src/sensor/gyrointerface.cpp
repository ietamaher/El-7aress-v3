#include "include/sensor/gyrointerface.h"
#include <QTimer>
#include <QDebug>

GyroInterface::GyroInterface(QObject *parent)
    : QObject(parent), gyroSerial(new QSerialPort(this)), m_isConnected(false)
{
}

GyroInterface::~GyroInterface()
{
    shutdown();
}

bool GyroInterface::openSerialPort(const QString &portName) {
    if (gyroSerial->isOpen()) {
        gyroSerial->close();
    }

    gyroSerial->setPortName(portName);
    gyroSerial->setBaudRate(QSerialPort::Baud9600);
    gyroSerial->setDataBits(QSerialPort::Data8);
    gyroSerial->setParity(QSerialPort::NoParity);
    gyroSerial->setStopBits(QSerialPort::OneStop);
    gyroSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (gyroSerial->open(QIODevice::ReadWrite)) {
        connect(gyroSerial, &QSerialPort::readyRead, this, &GyroInterface::processGyroData);
        connect(gyroSerial, &QSerialPort::errorOccurred, this, &GyroInterface::handleSerialError);
        qDebug() << "Opened gyro serial port:" << portName;
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        return true;
    } else {
       qDebug() << "Failed to open gyro serial port:" << gyroSerial->errorString();
        emit errorOccurred(gyroSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void GyroInterface::closeSerialPort() {
    if (gyroSerial->isOpen()) {
        gyroSerial->close();
        qDebug() << "Closed gyro serial port:" << gyroSerial->portName();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
    }
}

void GyroInterface::shutdown() {
    closeSerialPort();
    // Additional cleanup if necessary
}

void GyroInterface::processGyroData() {
    // Read data from the serial port
    QByteArray data = gyroSerial->readAll();
    // Process the data to extract Roll, Pitch, Yaw
    // For demonstration, let's assume the data is in a specific format
    // Example: "R:1.0,P:2.0,Y:3.0\n"

    // Accumulate data until we have a full line
    static QByteArray buffer;
    buffer.append(data);

    while (buffer.contains('\n')) {
        int endIndex = buffer.indexOf('\n');
        QByteArray lineData = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);

        QString line = QString::fromUtf8(lineData);
        // Parse the line to extract gyro data
        // You need to adjust this based on your actual data format
        QStringList parts = line.split(',');
        if (parts.size() >= 3) {
            bool ok1, ok2, ok3;
            double roll = parts[0].section(':', 1).toDouble(&ok1);
            double pitch = parts[1].section(':', 1).toDouble(&ok2);
            double yaw = parts[2].section(':', 1).toDouble(&ok3);

            if (ok1 && ok2 && ok3) {
                emit gyroDataReceived(roll, pitch, yaw);
            }
        }
    }
}

void GyroInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
       qDebug() << "Gyro serial port error occurred:" << gyroSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &GyroInterface::attemptReconnection);
    }
}

void GyroInterface::attemptReconnection() {
    if (!gyroSerial->isOpen()) {
        if (openSerialPort(gyroSerial->portName())) {
            qDebug() << "Gyro serial port reconnected.";
            // Reinitialize if necessary
        } else {
           qDebug() << "Failed to reopen gyro serial port:" << gyroSerial->errorString();
            // Retry after some time
            QTimer::singleShot(5000, this, &GyroInterface::attemptReconnection);
        }
    }
}
