#ifndef LRFInterface_H
#define LRFInterface_H

#include <QObject>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>
#include <QByteArray>

class LRFInterface : public QObject {
    Q_OBJECT
public:
    explicit LRFInterface(QObject *parent = nullptr);
    ~LRFInterface();

    void setSerialPort(QSerialPort *serial);

signals:
    void errorOccurred(const QString &error);
    void frequencySet(quint8 frequency, quint8 majorVersion, quint8 secondaryVersion, quint8 maintenanceVersion);
    void settingValueReceived(quint8 value);
    void laserCountReceived(quint32 count);
    void selfCheckResult(quint8 systemStatus, quint8 temperatureAlarm, quint8 biasVoltageFault, quint8 counterMalfunction);
    void rangingDataReceived(quint8 status, quint16 distance, quint8 decimalPlaces, quint8 echoStatus);

public slots:
    void sendSelfCheck();
    void sendSingleRanging();
    void sendContinuousRanging();
    void stopRanging();
    void setFrequency(int frequency);
    void querySettingValue();
    void queryAccumulatedLaserCount();

//protected:
    //void run() override;

private:
    enum DeviceCode : quint8 {
        LRF = 0x03
    };

    enum CommandCode : quint8 {
        SelfCheck = 0x01,
        SingleRanging = 0x02,
        ContinuousRanging = 0x03,
        StopRanging = 0x04,
        SetFrequency = 0x05,
        QueryLaserCount = 0x07,
        QuerySettingValue = 0x08
    };

    enum ResponseCode : quint8 {
        SelfCheckResponse = 0x01,
        SingleRangingResponse = 0x02,
        ContinuousRangingResponse = 0x03,
        StopRangingResponse = 0x04,
        SetFrequencyResponse = 0x05,
        QueryLaserCountResponse = 0x07,
        QuerySettingValueResponse = 0x08
    };

    quint8 calculateChecksum(const QByteArray &command) const;
    bool verifyChecksum(const QByteArray &response) const;
    QByteArray buildCommand(const QByteArray &commandTemplate) const;
    QByteArray sendCommand(const QByteArray &command);
    void handleResponse(const QByteArray &response);

    void handleSelfCheckResponse(const QByteArray &response);
    void handleRangingResponse(const QByteArray &response);
    void handleSetFrequencyResponse(const QByteArray &response);
    void handleSettingValueResponse(const QByteArray &response);
    void handleLaserCountResponse(const QByteArray &response);

    void processIncomingData();

    QSerialPort *lrfSerial;
    bool abort;
    QMutex mutex;
    QWaitCondition condition;
    QByteArray readBuffer; // Buffer to accumulate incoming data
};

#endif // LRFInterface_H
