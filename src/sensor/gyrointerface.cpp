#include "include/sensor/gyrointerface.h"
#include <QTimer>
#include <QDebug>

GyroInterface::GyroInterface(QObject *parent)
    : QObject(parent),
    m_thread(new QThread(this)),
    m_running(false)
{
    //moveToThread(m_thread);
    //connect(m_thread, &QThread::started, this, &GyroInterface::readGyroData);
    //connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
}

GyroInterface::~GyroInterface()
{
    stop();
}

void GyroInterface::setSerialPort(QSerialPort *serial) {
    gyroSerial = serial;
    if (gyroSerial) {
        // Move the serial port to this thread
        //lrfSerial->moveToThread(this);

        // Connect readyRead signal to processIncomingData slot
        connect(gyroSerial, &QSerialPort::readyRead, this, &GyroInterface::processGyroData);

        // Optionally, handle serial port errors
        connect(gyroSerial, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error){
            if (error != QSerialPort::NoError) {
                emit errorOccurred(gyroSerial->errorString());
            }
        });
    }
}
void GyroInterface::start()
{
    if (!m_running) {
        m_running = true;
        m_thread->start();
    }
}

void GyroInterface::stop()
{
    if (m_running) {
        m_running = false;
        m_thread->quit();
        m_thread->wait();
    }
}

void GyroInterface::processGyroData()
{
    while (m_running) {
        // Read gyro data from the device
        // For example, read from serial port or SPI

        // Simulate gyro data for demonstration
        double Roll = 0.05; // Replace with actual data
        double Pitch = 0.05; // Replace with actual data
        double Yaw = 0.1; // Replace with actual data

        emit gyroDataReceived(Roll, Pitch, Yaw);

        QThread::msleep(50); // Adjust the sleep duration as needed
    }
}
