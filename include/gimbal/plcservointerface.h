#ifndef PLCSERVOINTERFACE_H
#define PLCSERVOINTERFACE_H

#include <QObject>
#include "include/comm/plcmodbuscommunication.h"

class PLCServoInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCServoInterface(PLCModbusCommunication *modbusComm, QObject *parent = nullptr);

    void setAzimuthPulse(int pulse);
    void setAzimuthDirection(bool direction);
    void setElevationPulse(int pulse);
    void setElevationDirection(bool direction);

signals:
    void logMessage(const QString &message);

private:
    PLCModbusCommunication *m_modbusComm;

    // Modbus register addresses for servo control
    static constexpr int AZIMUTH_PULSE_ADDRESS = 0;
    static constexpr int AZIMUTH_DIRECTION_ADDRESS = 1;
    static constexpr int ELEVATION_PULSE_ADDRESS = 2;
    static constexpr int ELEVATION_DIRECTION_ADDRESS = 3;

    void logError(const QString &message);
};

#endif // PLCSERVOINTERFACE_H

