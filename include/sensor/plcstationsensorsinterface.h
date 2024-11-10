#ifndef PLCSTATIONSENSORINTERFACE_H
#define PLCSTATIONSENSORINTERFACE_H

#include <QObject>
#include "include/comm/plcstationdriver.h"

#define ANALOG_INPUTS_START_ADDRESS 1;

class PLCStationSensorInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCStationSensorInterface(PLCStationDriver *modbusComm, QObject *parent = nullptr);

signals:
    void logMessage(const QString &message);
    void errorOccurred(const QString &message);

    // Signals for sensors
    // PLC Station Digital Input Slots
    void stationUpperSensorStateChanged(bool state);
    void stationLowerSensorStateChanged(bool state);
    void stationAmmunitionLevelChanged(bool state);
    void stationInput1Changed(bool state);
    void stationInput2Changed(bool state);
    void stationInput3Changed(bool state);

    // PLC Station Analog Input Slot
    void eoTemperatureChanged(int temperature);
    void eoPressureChanged(int pressure);

private slots:
    void onInputBitsRead(int address, const QVector<uint8_t> &bits);
    void onInputRegistersRead(int address, const QVector<uint16_t> &values);
    void onErrorOccurred(const QString &message);

private:
    PLCStationDriver *m_modbusComm;

    void initializeSensorConfigs();
    void logError(const QString &message);

    // Sensor configurations
    struct SensorConfig {
        QString name;
        int address;
        int registerCount;
        std::function<void(const QVector<uint16_t> &, int)> processData;
    };
    QVector<SensorConfig> m_sensorConfigs;
};

#endif // PLCSTATIONSENSORINTERFACE_H
