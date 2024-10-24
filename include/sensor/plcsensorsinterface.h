#ifndef PLCSENSORINTERFACE_H
#define PLCSENSORINTERFACE_H

#include <QObject>
#include <QTimer>
#include "include/comm/plcmodbuscommunication.h"

class PLCSensorInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCSensorInterface(PLCModbusCommunication *modbusComm, QObject *parent = nullptr);

    void startMonitoring(int intervalMs = 1000); // Default to 1 second interval
    void stopMonitoring();

signals:
    void proximitySensorActivated(bool state);
    void temperatureUpdated(double temperature);
    void pressureUpdated(double pressure);
    void logMessage(const QString &message);

private slots:
    void readSensors();

private:
    PLCModbusCommunication *m_modbusComm;
    QTimer *m_readTimer;

    // Modbus register addresses for sensors
    static constexpr int PROXIMITY_SENSOR_ADDRESS = 20;
    static constexpr int TEMPERATURE_SENSOR_ADDRESS = 21;
    static constexpr int PRESSURE_SENSOR_ADDRESS = 22;

    void logError(const QString &message);
};

#endif // PLCSENSORINTERFACE_H
