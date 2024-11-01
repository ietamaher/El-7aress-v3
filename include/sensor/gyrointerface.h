#ifndef GYROINTERFACE_H
#define GYROINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>
#include <QByteArray>
#include <QThread>



class GyroInterface : public QObject {
        Q_OBJECT
public:
    explicit GyroInterface(QObject *parent = nullptr);
    ~GyroInterface();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    void shutdown();

signals:
    void gyroDataReceived(double Roll, double Pitch, double Yaw);
    void errorOccurred(const QString &error);
    void statusChanged(bool isConnected);

private slots:
    void processGyroData();
    void handleSerialError(QSerialPort::SerialPortError error);
    void attemptReconnection();

private:

    QSerialPort *gyroSerial;
    bool m_isConnected;

};

#endif // GYROINTERFACE_H

