#ifndef PLCSOLENOIDINTERFACE_H
#define PLCSOLENOIDINTERFACE_H

#include <QObject>
#include <QTimer>
#include "include/comm/plcmodbuscommunication.h"

class PLCSolenoidInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCSolenoidInterface(PLCModbusCommunication *modbusComm, QObject *parent = nullptr);

    void startFiring(int frequency); // Frequency in Hz
    void stopFiring();

signals:
    void logMessage(const QString &message);

private slots:
    void triggerSolenoid();

private:
    PLCModbusCommunication *m_modbusComm;
    QTimer *m_firingTimer;

    // Modbus register address for solenoid control
    static constexpr int SOLENOID_CONTROL_ADDRESS = 10;

    void logError(const QString &message);
};

#endif // PLCSOLENOIDINTERFACE_H

