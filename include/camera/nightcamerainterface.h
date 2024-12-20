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
    void setVideoModeLUT(quint16 mode);
    void setDigitalZoom(quint8 zoomLevel);
    void performFFC();
    void getCameraStatus();
    QByteArray buildCommand(quint8 function, const QByteArray &data);
    quint16 calculateCRC(const QByteArray &data, int length);

signals:
    void responseReceived(const QByteArray &response);
    void errorOccurred(const QString &error);
    void statusChanged(bool isConnected);

private slots:
    void handleSerialError(QSerialPort::SerialPortError error);
    void attemptReconnection();
    void processIncomingData();
    void handleStatusError(quint8 statusByte);
    void handleStatusResponse(const QByteArray &data);
    void handleFFCResponse(const QByteArray &data);
    void handleVideoLUTResponse(const QByteArray &data);
    void handleVideoModeResponse(const QByteArray &data);
    bool verifyCRC(const QByteArray &packet);
    void handleResponse(const QByteArray &response);
private:
    QSerialPort *cameraSerial;
    bool m_isConnected;
    QByteArray incomingBuffer;

    void sendCommand(const QByteArray &command);
};

#endif // NIGHTCAMERAINTERFACE_H

