#ifndef NIGHTCAMERAINTERFACE_H
#define NIGHTCAMERAINTERFACE_H

#include <QObject>
#include <QSerialPort>

class NightCameraInterface : public QObject {
    Q_OBJECT
public:
    explicit NightCameraInterface(QObject *parent = nullptr);
    ~NightCameraInterface();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    void shutdown();

    // Implement camera control methods
    void performFFC(); // Flat Field Correction
    void setDigitalZoom(quint8 zoomLevel);
    void getCameraStatus();

signals:
    void responseReceived(const QByteArray &response);
    void errorOccurred(const QString &error);
    void statusChanged(bool isConnected);

private slots:
    void handleSerialError(QSerialPort::SerialPortError error);
    void attemptReconnection();
    void processIncomingData();

private:
    QSerialPort *cameraSerial;
    bool m_isConnected;
    QByteArray incomingBuffer;

    void sendCommand(const QByteArray &command);
};

#endif // NIGHTCAMERAINTERFACE_H

