#ifndef PLCSOLENOIDINTERFACE_H
#define PLCSOLENOIDINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QSet>
#include "include/comm/plcmodbusworker.h"
#include "include/datamodel.h"

class PLCSolenoidInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCSolenoidInterface(PLCModbusWorker *modbusComm, QObject *parent = nullptr);

    void startFiring(int frequency); // Frequency in Hz
    void stopFiring();

signals:
    void logMessage(const QString &message);

private slots:
    void triggerSolenoid();
    void onWriteCompleted(int address);
    void onErrorOccurred(const QString &message);

private:
    PLCModbusWorker *m_modbusComm;
    QTimer *m_firingTimer;

    // Modbus register address for solenoid control
    static constexpr int SOLENOID_CONTROL_ADDRESS = 10;
    QSet<int> m_pendingWrites;
    void logError(const QString &message);
};

#endif // PLCSOLENOIDINTERFACE_H

