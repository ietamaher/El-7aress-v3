#ifndef PLCSTATIONDRIVER_H
#define PLCSTATIONDRIVER_H

#include <QObject>
#include <QModbusRtuSerialClient>
#include <QTimer>
#include <QMutex>

class PLCStationDriver : public QObject {
    Q_OBJECT
public:
    explicit PLCStationDriver(const QString &portName, int baudRate, QObject *parent = nullptr);
    ~PLCStationDriver();

    // Public methods to start and stop communication
    void startCommunication();
    void stopCommunication();
    // Start periodic reads
    void startPeriodicReads(int intervalMs);

    // Modbus operations
    void writeRegister(int serverAddress, int registerAddress, uint16_t value);
    void writeRegisters(int serverAddress, int startAddress, const QVector<uint16_t> &values);
    void readRegisters(int serverAddress, int startAddress, int count);
    void readInputBits(int serverAddress, int startAddress, int count);
    void readInputRegisters(int serverAddress, int startAddress, int count);
    void writeCoil(int serverAddress, int address, bool value);


signals:
    void logMessage(const QString &message);
    void errorOccurred(const QString &error);
    void connectionStatusChanged(bool connected);

    void registersRead(int address, const QVector<uint16_t> &values);
    void inputBitsRead(int address, const QVector<uint8_t> &bits);
    void inputRegistersRead(int address, const QVector<uint16_t> &values);
    void writeCompleted(int address);

private slots:
    void performPeriodicTasks();
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);

    // Response handlers
    void onReadReady();
    void onWriteFinished();
    void onWriteReady();

private:
    void logError(const QString &message);

    QModbusRtuSerialClient *m_modbusDevice;
    QTimer *m_timer;
    QString m_portName;
    int m_baudRate;
    bool m_running;
    QMutex m_mutex;
    QVector<bool> m_digitalOutputs = { false, false, false, false, false, false, false, false };

    // Constants for input addresses and counts
    static constexpr int DIGITAL_INPUTS_START_ADDRESS = 0;
    static constexpr int DIGITAL_INPUTS_COUNT = 8;
    static constexpr int ANALOG_INPUTS_START_ADDRESS = 0;
    static constexpr int ANALOG_INPUTS_COUNT = 5;

};

#endif // PLCSTATIONDRIVER_H
