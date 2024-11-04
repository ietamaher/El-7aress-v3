#ifndef SERVOACTUATORINTERFACE_H
#define SERVOACTUATORINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include "include/datamodel.h"

class ServoActuatorInterface : public QObject {
    Q_OBJECT
public:
    explicit ServoActuatorInterface(QObject *parent = nullptr);
    ~ServoActuatorInterface();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    void shutdown();

    // Command methods
    void moveToPosition(int position);
    void checkStatus();
    void checkAlarms();

signals:
    void responseReceived(const QString &response);
    void commandSent(const QString &command);
    void positionReached(int position);
    void statusUpdated(const QString &status);
    void alarmDetected(const QString &alarmMessage);

    void errorOccurred(const QString &error);
    void statusChanged(bool isConnected);

private slots:
    void processIncomingData();
    void handleTimeout();
    void handleSerialError(QSerialPort::SerialPortError error);
    void attemptReconnection();

private:
    QSerialPort *servoSerial;
    QByteArray buffer;
    bool m_isConnected;
    QTimer *timeoutTimer;

    void sendCommand(const QString &command);
};

#endif // SERVOACTUATORINTERFACE_H
