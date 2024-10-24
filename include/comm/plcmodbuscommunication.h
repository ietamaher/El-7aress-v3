#ifndef PLCMODBUSCOMMUNICATION_H
#define PLCMODBUSCOMMUNICATION_H

#include <QObject>
#include <QMutex>
#include <modbus/modbus.h>

class PLCModbusCommunication : public QObject {
    Q_OBJECT
public:
    explicit PLCModbusCommunication(const QString &portName, int baudRate, QObject *parent = nullptr);
    ~PLCModbusCommunication();

    bool connectDevice();
    void disconnectDevice();

    // Thread-safe read/write methods
    bool writeRegister(int address, uint16_t value);
    bool writeRegisters(int address, const QVector<uint16_t> &values);
    bool readRegisters(int address, int count, QVector<uint16_t> &values);

signals:
    void logMessage(const QString &message);

private:
    modbus_t *m_modbusContext;
    QMutex m_modbusMutex;

    QString m_portName;
    int m_baudRate;

    void logError(const QString &message);
};

#endif // PLCMODBUSCOMMUNICATION_H
