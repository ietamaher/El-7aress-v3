#ifndef RADARINTERFACE_H
#define RADARINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>
#include <QByteArray>
#include <QThread>
#include <QMap>
#include "include/datamodel.h"

struct RadarTarget {
    int id;
    double azimuth; // Degrees
    double range;   // Meters
    // Add other relevant fields if necessary
};

class RadarInterface : public QObject {
    Q_OBJECT
public:
    explicit RadarInterface(QObject *parent = nullptr);
    ~RadarInterface();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    void shutdown();

    // Accessor for target data
    QMap<int, RadarTarget> getTargets();

signals:
    void targetUpdated(const RadarTarget &target);
    void targetRemoved(int targetId);
    void errorOccurred(const QString &error);
    void statusChanged(bool isConnected);

private slots:
    void processIncomingData();
    void handleSerialError(QSerialPort::SerialPortError error);
    void attemptReconnection();

private:
    QSerialPort *radarSerial;
    QByteArray buffer;
    bool m_isConnected;
    QMutex mutex;
    QWaitCondition condition;

    QMap<int, RadarTarget> targets; // Keyed by target ID

    void parseNMEASentence(const QString &sentence);
    int calculateChecksum(const QString &sentence);
};

#endif // RADARINTERFACE_H
