#ifndef PLCSERVOINTERFACE_H
#define PLCSERVOINTERFACE_H

#include <QObject>
#include "include/comm/plcstationdriver.h"

class PLCServoInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCServoInterface(PLCStationDriver *modbusComm, QObject *parent = nullptr);

    void setServoParameters(int azimuthPulse, bool azimuthDirection, int elevationPulse, bool elevationDirection);
    void sendServoParameters();

signals:
    void logMessage(const QString &message);

private slots:
    void onWriteCompleted(int address);
    void onErrorOccurred(const QString &message);

private:
    PLCStationDriver *m_modbusWorker;

    // Modbus register addresses for servo control
    static constexpr int AZIMUTH_PULSE_ADDRESS = 0;
    static constexpr int AZIMUTH_DIRECTION_ADDRESS = 1;
    static constexpr int ELEVATION_PULSE_ADDRESS = 2;
    static constexpr int ELEVATION_DIRECTION_ADDRESS = 3;

    // Internal storage for servo parameters
    uint16_t m_azimuthPulse = 0;
    uint16_t m_azimuthDirection = 0;
    uint16_t m_elevationPulse = 0;
    uint16_t m_elevationDirection = 0;

    void logError(const QString &message);
};

#endif // PLCSERVOINTERFACE_H
