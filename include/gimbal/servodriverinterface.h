#ifndef SERVODRIVERINTERFACE_H
#define SERVODRIVERINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QModbusRtuSerialClient>
#include <QModbusDataUnit>
#include <QModbusReply>

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
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &message); // Add this signal

private slots:
    void readData();
    void handleTimeout();
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);
    void onReadReady();

private:
    QString m_identifier;
    QString m_device;
    int m_baudRate;
    int m_slaveId;

    QModbusRtuSerialClient *m_modbusDevice; // Ensure correct class type
    QMutex m_mutex;

    QTimer *m_readTimer;
    QTimer *m_timeoutTimer;

    void logError(const QString &message);
};

#endif // SERVODRIVERINTERFACE_H
