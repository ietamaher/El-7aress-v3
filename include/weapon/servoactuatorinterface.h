#ifndef SERVOACTUATORINTERFACE_H
#define SERVOACTUATORINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>

class ServoActuatorInterface : public QObject {
    Q_OBJECT
public:
    explicit ServoActuatorInterface(QObject *parent = nullptr);
    ~ServoActuatorInterface();

    void setSerialPort(QSerialPort *serial);

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

private slots:
    void processIncomingData();
    void handleTimeout();

private:
    QSerialPort *servoSerial;
    QByteArray buffer;
    QTimer *timeoutTimer;

    void sendCommand(const QString &command);
};

#endif // SERVOACTUATORINTERFACE_H
