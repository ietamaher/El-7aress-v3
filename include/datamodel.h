#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QPointF>
#include <QDateTime>

class DataModel : public QObject {
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);

    // Setters (slots)
public slots:
    void setOperationalStateMode(const QString &mode);
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
 

    // Getters
public:
    QString getOperationalStateMode();
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

private:
    // Data members
    QString m_operationalStateMode;
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

    
    QMutex m_mutex; // Protects data members
};

#endif // DATAMODEL_H

