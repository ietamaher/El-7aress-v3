#ifndef PLCSENSORINTERFACE_H
#define PLCSENSORINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <cstdint>

#include "include/comm/plcmodbusworker.h"
#include <functional>

// Define sensor addresses (adjust these as per your setup)
#define PROXIMITY_SENSOR_ADDRESS    100
#define TEMPERATURE_SENSOR_ADDRESS  101
#define PRESSURE_SENSOR_ADDRESS     102

struct SensorConfig {
    QString name; // Sensor name for identification
    uint16_t address; // Starting register address
    uint16_t registerCount; // Number of registers to read
    std::function<void(const QVector<uint16_t>&, int)> processData; // Function to process data
};

class PLCSensorInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCSensorInterface(PLCModbusWorker *modbusComm, QObject *parent = nullptr);

    void startMonitoring(int intervalMs = 1000); // Default to 1 second interval
    void stopMonitoring();
    void readSensors();

signals:
    void proximitySensorActivated(bool state);
    void temperatureUpdated(double temperature);
    void pressureUpdated(double pressure);
    void logMessage(const QString &message);

private slots:
    void onRegistersRead(int address, const QVector<uint16_t> &values);
    void onErrorOccurred(const QString &message);


private:
    PLCModbusWorker *m_modbusComm;
    QVector<SensorConfig> m_sensorConfigs; // List of sensor configurations
    QTimer *m_readTimer;

    uint16_t m_startAddress;
    uint16_t m_totalRegisters;

    void logError(const QString &message);
    void initializeSensorConfigs();

};

#endif // PLCSENSORINTERFACE_H
