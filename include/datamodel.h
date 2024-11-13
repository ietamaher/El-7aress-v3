#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QPointF>
#include <QDateTime>

#include "include/states/operationalstate.h"

enum class FireMode {
    SingleShot = 0,
    ShortBurst = 1,
    LongBurst = 2
};


class DataModel : public QObject {
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);


public slots:
    void setOperationalStateMode(const OperationalMode &mode);
    void setMotionMode(const QString &mode);
    void setLRFDistance(double distance);
    void setGyroOrientation(double roll, double pitch, double yaw);
    void setGimbalOrientation(double azimuth, double elevation);
    void setGimbalSpeed(double speed);
    void setCrosshairPosition(const QPointF &position);
    void setWeaponSystemStatus(const QString &status);
    void setTargetInformation(const QString &info);
    void setSystemTime(const QDateTime &time);
    void setGPSCoordinates(const QString &coordinates);
    void setSensorReadings(const QString &readings);
    void setAlertsWarnings(const QString &alerts);
    void setDetectionEnabled(bool enabled);
    void setStabilizationEnabled(bool enabled);

    // Setters For PLC Monitor
    void setGunEnabled(bool enabled);
    void setLoadAmmunition(bool loaded);
    void setStationState(bool state);
    void setHomeSw(bool state);
    void setStabilizationSw(bool state);
    void setAuthorizeSw(bool state);
    void setCamActive(bool state);
    void setUpSw(bool state);
    void setDownSw(bool state);
    void setMenuValSw(bool state);
    void setFireMode(FireMode mode);
    void setSpeedSw(int speed);
    void setPanelTemperature(int temperature);


    void setStationUpperSensor(bool state);
    void setStationLowerSensor(bool state);
    void setStationAmmunitionLevel(bool state);
    void setStationInput1(bool state);
    void setStationInput2(bool state);
    void setStationInput3(bool state);

    void setEOTemperature(int temperature);
    void setEOPressure(int pressure);

    void setReticleStyle(const QString &style);


    // Getters
public:
    OperationalMode getOperationalStateMode();
    QString getMotionMode();
    double getLRFDistance();
    void getGyroOrientation(double &roll, double &pitch, double &yaw);

    void getGimbalOrientation(double &azimuth, double &elevation);
    double getGimbalSpeed();
    QPointF getCrosshairPosition();
    QString getWeaponSystemStatus();
    QString getTargetInformation();
    QDateTime getSystemTime();
    QString getGPSCoordinates();
    QString getSensorReadings();
    QString getAlertsWarnings();
    bool isDetectionEnabled();
    bool isStabilizationEnabled();

    // Getters For PLC Monitor
    bool isGunEnabled();

    bool isLoadAmmunition();
    bool getStationState();

    bool getHomeSw();
    bool getStabilizationSw();
    bool getAuthorizeSw();
    bool getCamera();
    bool getUpSw();
    bool getDownSw();
    bool getMenuValSw();
    int getSpeedSw();
    FireMode getFireMode();
    int getPanelTemperature();

    bool getStationUpperSensor();
    bool getStationLowerSensor();
    bool getStationAmmunitionLevel();
    bool getStationInput1();
    bool getStationInput2();
    bool getStationInput3();

    int getEOTemperature();
    int getEOPressure();

    QString getReticleStyle();
signals:
    // Optional: Signals to notify changes
    void dataModelUpdated();
    void operationalStateModeChange(const OperationalMode &mode);
    void upSwChanged(bool state);
    void downSwChanged(bool state);
    void menuValSwChanged(bool state);

    void reticleStyleChanged(const QString &style);
    void fireModeChanged(FireMode mode);

private:
    // Data members
    OperationalMode m_operationalStateMode;
    QString m_motionMode;
    double m_lrfDistance;
    double m_roll, m_pitch, m_yaw;

    double m_azimuthAngle;
    double m_elevationAngle;
    double m_gimbalSpeed;
    QPointF m_crosshairPosition;
    QString m_weaponSystemStatus;
    QString m_targetInformation;
    QDateTime m_systemTime;
    QString m_gpsCoordinates;
    QString m_sensorReadings;
    QString m_alertsWarnings;
    bool m_detectionEnabled;
    bool m_stabilizationEnabled;

    bool m_gunEnabled;
    FireMode m_fireMode;
    bool m_loadAmmunition;
    bool m_stationState;
    int m_speedSw;
    bool m_homeSw;
    bool m_stabilizationSw;
    bool m_authorizeSw;
    bool m_activeCamera;
    bool m_upSw;
    bool m_downSw;
    bool m_menuValSw;
    int m_panelTemperature;

    bool m_stationUpperSensor;
    bool m_stationLowerSensor;
    bool m_stationAmmunitionLevel;

    bool m_stationInput1;
    bool m_stationInput2;
    bool m_stationInput3;
    int m_stationTemperature;
    int m_stationPressure;

    QString m_reticleStyle;

    QMutex m_mutex; // Protects data members


};

#endif // DATAMODEL_H

