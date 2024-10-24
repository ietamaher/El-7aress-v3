#ifndef GYROINTERFACE_H
#define GYROINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QMutex>
#include <QThread>



class GyroInterface : public QObject {
        Q_OBJECT
public:
    explicit GyroInterface(QObject *parent = nullptr);
    ~GyroInterface();

    void start();
    void stop();
    void setSerialPort(QSerialPort *serial);

signals:
    void errorOccurred(const QString &error);
    void gyroDataReceived(double Roll, double Pitch, double Yaw);

private slots:
    //void readGyroData();

private:
    QThread *m_thread;
    bool m_running;
    QSerialPort *gyroSerial;
    bool abort;
    QMutex mutex;
    // Add members for serial port communication or other interfaces
    // e.g., QSerialPort *m_serialPort;

    void processGyroData();
};

#endif // GYROINTERFACE_H

