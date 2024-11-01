#ifndef LENSINTERFACE_H
#define LENSINTERFACE_H

#include <QObject>
#include <QSerialPort>

class LensInterface : public QObject {
    Q_OBJECT
public:
    explicit LensInterface(QObject *parent = nullptr);
    ~LensInterface();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    void shutdown();

    // Lens control methods
    void moveToWFOV();
    void moveToNFOV();
    void moveToIntermediateFOV(int percentage);
    void moveToFocalLength(int efl);
    void moveToInfinityFocus();
    void moveFocusNear(int amount);
    void moveFocusFar(int amount);
    void getFocusPosition();
    void getLensTemperature();
    void resetController();
    void homeAxis(int axis);
    void turnOnTemperatureCompensation();
    void turnOffTemperatureCompensation();
    void turnOnRangeCompensation();
    void turnOffRangeCompensation();

signals:
    void responseReceived(const QString &response);
    void errorOccurred(const QString &error);
    void statusChanged(bool isConnected);
    void commandSent();

private slots:
    void handleSerialError(QSerialPort::SerialPortError error);
    void attemptReconnection();

private:
    QSerialPort *lensSerial;
    bool m_isConnected;

    QString sendCommand(const QString &command);
};

#endif // LENSINTERFACE_H
