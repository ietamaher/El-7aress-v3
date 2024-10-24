#ifndef LENSINTERFACE_H
#define LENSINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>


class LensInterface : public QObject
{
    Q_OBJECT

public:
    explicit LensInterface(QObject *parent = nullptr);
    ~LensInterface();

    void setSerialPort(QSerialPort *serial);

    // Lens Command Methods
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


private:
    QSerialPort *lensSerial;
    QMutex mutex;
    QWaitCondition condition;
    bool abort;

    QString sendCommand(const QString &command);

signals:
    void commandSent();
    void responseReceived(const QString &response);

};

#endif // LENSINTERFACE_H
