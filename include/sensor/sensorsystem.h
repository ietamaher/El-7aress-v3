#ifndef SENSORSYSTEM_H
#define SENSORSYSTEM_H

#include <QObject>
#include <QPointer>
#include <QThread>
#include <QSerialPort>
#include "lrfinterface.h"
#include "gyrointerface.h"
#include "radarinterface.h"
#include "plcstationsensorsinterface.h"
#include "plcpanelsensorsinterface.h"

#include "include/datamodel.h"


class SensorSystem : public QObject {
    Q_OBJECT
public:
    explicit SensorSystem(DataModel *dataModel, QObject *parent = nullptr);
    ~SensorSystem();


    void shutdown();
    // Setter methods for interfaces
    void setLRFInterface(LRFInterface *lrfInterface);
    void setGyroInterface(GyroInterface *gyroInterface);
    void setRadarInterface(RadarInterface *radarInterface);
    void setPLCStationSensorInterface(PLCStationSensorInterface *sensorInterface);

    // Getter methods for interfaces
    LRFInterface* getLRFInterface() const;
    GyroInterface* getGyroInterface() const;
    RadarInterface* getRadarInterface() const;
    PLCStationSensorInterface* getPLCStationSensorInterface() const;

    // Other methods remain the same
    //void activateSensors(bool activate);
    //void activateLRF();
    //void deactivateLRF();
    //void enableStabilization();
    //void disableStabilization();
    //void activateTrackingSensors(bool activate);
    //void activateEngagementSensors(bool activate);

    void getGyroRates(double& Roll, double& Pitch, double& Yaw);

    void startMonitoringSensors();
    void stopMonitoringSensors();

public slots:
    // Slots for LRF commands
    void sendSelfCheck();
    void sendSingleRanging();
    void sendContinuousRanging();
    void stopRanging();
    void setFrequency(int frequency);
    void querySettingValue();
    void queryAccumulatedLaserCount();

    void onGyroDataReceived(double Roll, double Pitch, double Yaw);

    void handleErrorOccurred(const QString &error);
    void handleFrequencySet(quint8 frequency, quint8 majorVersion, quint8 secondaryVersion, quint8 maintenanceVersion);
    void handleSettingValueReceived(quint8 value);
    void handleLaserCountReceived(quint32 count);
    void handleSelfCheckResult(quint8 systemStatus, quint8 temperatureAlarm, quint8 biasVoltageFault, quint8 counterMalfunction);
    void handleRangingDataReceived(quint8 status, quint16 distance, quint8 decimalPlaces, quint8 echoStatus);

    void onLRFInterfaceDestroyed(QObject *obj);

    void handleLRFConnectionStatusChanged(bool connected);
    void handleRadarConnectionStatusChanged(bool connected);
    void handleGyroConnectionStatusChanged(bool connected);

    // PLC Monitor Digital Input Slots
    void onGunStateChanged(bool state);
    void onLoadAmmunitionStateChanged(bool state);
    void onStationStateChanged(bool state);
    void onHomeSwChanged(bool state);
    void onStabilizationSwChanged(bool state);
    void onAuthorizeSwChanged(bool state);
    void onCamSwChanged(bool state);
    void onUpSwChanged(bool state);
    void onDownSwChanged(bool state);
    void onMenuValSwChanged(bool state);

    // PLC Monitor Analog Input Slot
    void onSpeedSwChanged(int speed);
    void onFireModeStateInputChanged(int mode);
    void onPanelTemperatureChanged(int temperature);

    // PLC Station Digital Input Slots
    void onStationUpperSensorStateChanged(bool state);
    void onStationLowerSensorStateChanged(bool state);
    void onStationAmmunitionLevelChanged(bool state);
    void onStationInput1Changed(bool state);
    void onStationInput2Changed(bool state);
    void onStationInput3Changed(bool state);

    // PLC Station Analog Input Slot
    void onEOTemperatureChanged(int temperature);
    void onEOPressureChanged(int pressure);

signals:
    // Signals to be emitted to MainWindow or other classes
    void errorOccurred(const QString &error);
    void frequencySet(quint8 frequency, quint8 majorVersion, quint8 secondaryVersion, quint8 maintenanceVersion);
    void settingValueReceived(quint8 value);
    void laserCountReceived(quint32 count);
    void selfCheckResult(quint8 systemStatus, quint8 temperatureAlarm, quint8 biasVoltageFault, quint8 counterMalfunction);
    void rangingDataReceived(quint8 status, quint16 distance, quint8 decimalPlaces, quint8 echoStatus);

    void gyroDataUpdated(double Roll, double Pitch, double Yaw);

    void proximitySensorActivated(bool state);
    void temperatureUpdated(double temperature);
    void pressureUpdated(double pressure);

    void lrfConnectionStatusChanged(bool connected);
    void radarConnectionStatusChanged(bool connected);
    void gyroConnectionStatusChanged(bool connected);

private:
    //LRFInterface *m_lrfInterface;
    QPointer<LRFInterface> m_lrfInterface;
    DataModel *m_dataModel;

    GyroInterface *m_gyroInterface;
    RadarInterface *m_radarInterface;
    PLCStationSensorInterface *m_plcStationSensorInterface;
    PLCPanelSensorInterface *m_plcPanelSensorInterface;

    QThread *m_lrfThread;

    QSerialPort  *lrfSerial;
    QSerialPort *radarSerial;
    QSerialPort *gyroSerial;
    QSerialPort *plcSerial;
    QSerialPort *plcMonitorSerial;


    bool m_sensorsActive;
    bool m_lrfActive;
    bool m_stabilizationEnabled;

    bool m_trackingSensorsActive;
    bool m_engagementSensorsActive;




    double m_roll;
    double m_pitch;
    double m_yaw;

    void initializeLRF();

};

#endif // SENSORSYSTEM_H
