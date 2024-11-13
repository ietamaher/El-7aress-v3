#ifndef PLCSERVOINTERFACE_H
#define PLCSERVOINTERFACE_H

#include <QObject>
#include "include/comm/plcstationdriver.h"

class PLCServoInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCServoInterface(PLCStationDriver *modbusComm, QObject *parent = nullptr);
    // Setters
    void setOperationMode(uint16_t mode);
    void setElevationSpeed(uint16_t speed);
    void setAzimuthSpeed(uint16_t speed);
    void setElevationDirection(uint16_t direction);
    void setAzimuthDirection(uint16_t direction);
    void setElevationTargetAngle(uint16_t angle);
    void setAzimuthTargetAngle(uint16_t angle);
    void setActualAzimuth(uint16_t angle);
    void setActualElevation(uint16_t angle);
    // Getters (if needed)
    uint16_t getOperationMode();
    uint16_t getElevationSpeed();
    uint16_t getAzimuthSpeed();
    uint16_t getElevationDirection();
    uint16_t getAzimuthDirection();
    uint16_t getElevationTargetAngle();
    uint16_t getAzimuthTargetAngle();

    // Send all parameters to PLC
    void sendParameters();
    //void setServoParameters(int azimuthPulse, bool azimuthDirection, int elevationPulse, bool elevationDirection);
    void sendServoParameters();

signals:
    void logMessage(const QString &message);

private slots:
    void onWriteCompleted(int address);
    void onErrorOccurred(const QString &message);

private:
    PLCStationDriver *m_modbusWorker;

    // Modbus register addresses for servo control
    static constexpr int HR_OPERATION_MODE = 0;


    // Internal storage for servo parameters
    uint16_t m_operationMode;
    uint16_t m_elevationSpeed;
    uint16_t m_azimuthSpeed;
    uint16_t m_elevationDirection;
    uint16_t m_azimuthDirection;
    uint16_t m_elevationTargetAngle;
    uint16_t m_azimuthTargetAngle;
    uint16_t m_actualElevationAngle;
    uint16_t m_actualAzimuthAngle;

    void logError(const QString &message);
};

#endif // PLCSERVOINTERFACE_H
