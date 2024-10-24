#ifndef MDUINOCONTROLLER_H
#define MDUINOCONTROLLER_H

#include <QObject>
#include <QMutex>
#include <modbus/modbus.h>

class MduinoController : public QObject {
    Q_OBJECT
public:
    explicit MduinoController(const QString &portName, int baudRate, int slaveId, QObject *parent = nullptr);
    ~MduinoController();

    bool connectDevice();
    void disconnectDevice();

    // Methods to control stepper motors
    void setAzimuthPulse(int pulse);
    void setAzimuthDirection(bool direction);
    void setElevationPulse(int pulse);
    void setElevationDirection(bool direction);

    // Optionally, methods to set speed or other parameters

signals:
    void logMessage(const QString &message);

private:
    modbus_t *m_modbusContext;
    QMutex m_modbusMutex;

    QString m_portName;
    int m_baudRate;
    int m_slaveId;

    void logError(const QString &message);
};

#endif // MDUINOCONTROLLER_H
