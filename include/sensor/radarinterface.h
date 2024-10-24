#ifndef RADARINTERFACE_H
#define RADARINTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include <QMap>

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

    void setSerialPort(QSerialPort *serial);

    // Accessor for target data
    QMap<int, RadarTarget> getTargets();

signals:
    void targetUpdated(const RadarTarget &target);
    void targetRemoved(int targetId);

private slots:
    void processIncomingData();

private:
    QSerialPort *radarSerial;
    QByteArray buffer;
    QMutex mutex;

    QMap<int, RadarTarget> targets; // Keyed by target ID

    void parseNMEASentence(const QString &sentence);
    int calculateChecksum(const QString &sentence);
};

#endif // RADARINTERFACE_H
