#ifndef PLCSPANELSENSORINTERFACE_H
#define PLCSPANELSENSORINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QModbusRtuSerialClient>
#include <QModbusDataUnit>
#include <QModbusReply>

class PLCPanelSensorInterface : public QObject {
    Q_OBJECT
public:
    explicit PLCPanelSensorInterface(const QString &device,
                                       int baudRate,
                                       int slaveId,
                                       QObject *parent = nullptr);
    ~PLCPanelSensorInterface();

    bool connectDevice();
    void disconnectDevice();
    QVector<bool> digitalInputs() const;
    QVector<uint16_t> analogInputs() const;

    void setDigitalOutputs(const QVector<bool> &outputs);

signals:
    void logMessage(const QString &message);
    void errorOccurred(const QString &error);
    void dataRead();
    void connectionStatusChanged(bool connected);

    // Digital Input Signals
    void gunStateChanged(bool state);
    void loadAmmunitionStateChanged(bool state);
    void stationStateChanged(bool state);
    void homeSwChanged(bool state);
    void stabilizationSwChanged(bool state);
    void authorizeSwChanged(bool state);
    void camSwChanged(bool state);
    void upSwChanged(bool state);
    void downSwChanged(bool state);
    void menuValSwChanged(bool state);

    // Analog Input Signals
    void speedSwChanged(int speed);
    void fireModeStateInputChanged(int mode);
    void panelTemperatureChanged(int temperature);

    void digitalInputsChanged(const QVector<bool> &inputs);
    void analogInputsChanged(const QVector<uint16_t> &inputs);

    void maxReconnectionAttemptsReached();


public slots:
    void readData();
    void writeData();

private slots:
    //void onReadReady();
    void onWriteReady();
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);
    void handleTimeout();
    void onDigitalInputsReadReady();
    void onAnalogInputsReadReady();
    //void onCoilsReadReady();
    //void onHoldingRegisterReadReady();
private:
    QModbusRtuSerialClient *m_modbusDevice;
    QTimer *m_readTimer;
    QTimer *m_timeoutTimer;
    mutable QMutex m_mutex;

    QString m_device;
    int m_baudRate;
    int m_slaveId;

    // Data members for inputs and outputs
    // Inputs
    bool m_gunState;
    bool m_loadAmmunitionState;
    bool m_stationState;
    bool m_homeSw;
    bool m_stabilizationSw;
    bool m_authorizeSw;
    bool m_activeCamera;
    bool m_upSw;
    bool m_downSw;
    bool m_menuValSw;
    bool m_input4;

    // Outputs
    bool m_gunLedState;
    bool m_safetyStationLed;

    // Analog input
    int m_speedSw;
    int m_fireModeStateInput;
    int m_panelTemperature;

    void parseInputs(const QModbusDataUnit &unit);
    void prepareOutputs(QModbusDataUnit &unit);

    // Modbus addresses
    static constexpr int INPUTS_START_ADDRESS = 0;
    static constexpr int OUTPUTS_START_ADDRESS = 0;
    static constexpr int ANALOG_INPUT_START_ADDRESS = 0;

    // Reconnection logic
    int m_reconnectAttempts;
    const int MAX_RECONNECT_ATTEMPTS = 5;

    QVector<bool> m_digitalInputs;
    QVector<uint16_t> m_analogInputs;
    QVector<bool> m_digitalOutputs = { false, false, false, false, false };


    const int BASE_RECONNECT_DELAY_MS = 1000; // 1 second
    void logError(const QString &message);
};

#endif // PLCSPANELSENSORINTERFACE_H
