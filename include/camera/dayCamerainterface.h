#ifndef DAYCAMERAINTERFACE_H
#define DAYCAMERAINTERFACE_H

#include <QObject>
#include <QSerialPort>

class DayCameraInterface : public QObject {
    Q_OBJECT
public:
    explicit DayCameraInterface(QObject *parent = nullptr);
    ~DayCameraInterface();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    void shutdown();

    // Visca command methods
    void zoomIn();
    void zoomOut();
    void zoomStop();
    void setZoomPosition(quint16 position); // Position range depends on camera
    void focusNear();
    void focusFar();
    void focusStop();
    void setFocusAuto(bool enabled);
    void setFocusPosition(quint16 position);

    // Inquiry commands
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

#endif // DAYCAMERAINTERFACE_H
