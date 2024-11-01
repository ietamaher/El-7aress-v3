#ifndef PLCMODBUSWORKER_H
#define PLCMODBUSWORKER_H

#include <QObject>
#include <QModbusRtuSerialClient>
#include <QTimer>
#include <QMutex>

class PLCModbusWorker : public QObject {
    Q_OBJECT
public:
    explicit PLCModbusWorker(const QString &portName, int baudRate, QObject *parent = nullptr);
    ~PLCModbusWorker();

    // Public methods to start and stop communication
    void startCommunication();
    void stopCommunication();

public slots:
    // Read/write methods
    void writeRegister(int serverAddress, int registerAddress, uint16_t value);
    void writeRegisters(int serverAddress, int startAddress, const QVector<uint16_t> &values);
    void readRegisters(int serverAddress, int startAddress, int count);
    void readInputBits(int serverAddress, int startAddress, int count);

signals:
    void logMessage(const QString &message);
    void connectionStatusChanged(bool connected);
    void registersRead(int address, const QVector<uint16_t> &values);
    void inputBitsRead(int address, const QVector<uint8_t> &values);
    void writeCompleted(int address);
    void errorOccurred(const QString &message);

private slots:
    void performPeriodicTasks();
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);

    // Response handlers
    void onReadReady();
    void onWriteFinished();

private:
    QModbusRtuSerialClient *m_modbusDevice;
    QTimer *m_timer;

    QString m_portName;
    int m_baudRate;
    bool m_running;
    QMutex m_mutex;

    void logError(const QString &message);
};

#endif // PLCMODBUSWORKER_H
