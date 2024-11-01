#ifndef GIMBALMOTORDRIVER_H
#define GIMBALMOTORDRIVER_H

#include <QObject>
#include "mduinocontroller.h"
#include "servodriverinterface.h"

class GimbalMotorDriver : public QObject {
    Q_OBJECT
public:
    explicit GimbalMotorDriver(QObject *parent = nullptr);
    ~GimbalMotorDriver();

    // Initialization
    bool initialize();

    // Command methods
    void sendPositionCommand(double azimuth, double elevation);
    void sendSpeedCommand(double azimuthSpeed, double elevationSpeed);

    // Accessors for current positions
    double getAzimuthPosition() const;
    double getElevationPosition() const;


public slots:


signals:
    void stepperMotorStatusChanged(const QString &motorName, bool connected);
    void azimuthDataUpdated(double position, double speed, double torque, double motorTemp, double driverTemp);
    void elevationDataUpdated(double position, double speed, double torque, double motorTemp, double driverTemp);
    void logMessage(const QString &message);

    void azimuthConnectionStatusChanged(bool connected);
    void elevationConnectionStatusChanged(bool connected);

private slots:
    void processAzimuthServoData(const QVector<uint16_t> &data);
    void processElevationServoData(const QVector<uint16_t> &data);


    void handleAzimuthConnectionStatusChanged(bool connected);
    void handleElevationConnectionStatusChanged(bool connected);

private:
    MduinoController *m_mduinoController;
    ServoDriverInterface *m_azimuthServoDriver;
    ServoDriverInterface *m_elevationServoDriver;

    double m_azimuthPosition;
    double m_elevationPosition;

};

#endif // GIMBALMOTORDRIVER_H
