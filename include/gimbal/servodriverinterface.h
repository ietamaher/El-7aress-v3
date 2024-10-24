#ifndef SERVODRIVERINTERFACE_H
#define SERVODRIVERINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutex>
#include <modbus/modbus.h>
#include "include/devicemanager.h"

class ServoDriverInterface : public QObject {
    Q_OBJECT
public:
    explicit ServoDriverInterface(const QString &identifier,
                                  const QString &device,
                                  int baudRate,
                                  int slaveId,
                                  QObject *parent = nullptr);
    ~ServoDriverInterface();

    bool connectDevice();
    void disconnectDevice();

signals:
    void dataRead(const QVector<uint16_t> &data);
    void logMessage(const QString &message);

private slots:
    void readData();
    void handleTimeout();

private:
    QString m_identifier;
    QString m_device;
    int m_baudRate;
    int m_slaveId;

    modbus_t *m_modbusContext;
    QMutex m_modbusMutex;

    QTimer *m_readTimer;
    QTimer *m_timeoutTimer;

    void logError(const QString &message);
};

#endif // SERVODRIVERINTERFACE_H
