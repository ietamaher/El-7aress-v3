#ifndef PLCSOLENOIDINTERFACE_H
#define PLCSOLENOIDINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QSet>
#include "include/comm/plcstationdriver.h"
#include "include/datamodel.h"

class PLCSolenoidInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCSolenoidInterface(PLCStationDriver *modbusComm, QObject *parent = nullptr);

    void WriteRegisterData(int slaveId, int address, int mode) ;
    void startFiring(); // Frequency in Hz
    void stopFiring();

signals:
    void logMessage(const QString &message);

private slots:
    void triggerSolenoid();
    void onWriteCompleted(int address);
    void onErrorOccurred(const QString &message);

private:
    PLCStationDriver *m_modbusComm;
    QTimer *m_firingTimer;

    // Modbus register address for solenoid control
    static constexpr int SOLENOID_CONTROL_ADDRESS = 10;
    QSet<int> m_pendingWrites;
    void logError(const QString &message);
};

#endif // PLCSOLENOIDINTERFACE_H

