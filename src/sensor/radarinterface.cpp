#include "include/sensor/radarinterface.h"
#include <QDebug>
#include <QStringList>

RadarInterface::RadarInterface(QObject *parent)
    : QObject(parent),
    radarSerial(nullptr)
{
}

RadarInterface::~RadarInterface()
{
    if (radarSerial) {
        radarSerial->close();
        radarSerial->deleteLater();
    }
}

void RadarInterface::setSerialPort(QSerialPort *serial)
{
    radarSerial = serial;
    if (radarSerial) {
        // Connect readyRead signal to processIncomingData slot
        connect(radarSerial, &QSerialPort::readyRead, this, &RadarInterface::processIncomingData);
    }
}

void RadarInterface::processIncomingData()
{
    if (!radarSerial)
        return;

    buffer.append(radarSerial->readAll());

    // Split the buffer into lines
    while (buffer.contains('\n')) {
        int endIndex = buffer.indexOf('\n');
        QByteArray lineData = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);

        QString line = QString::fromUtf8(lineData);

        // Process the NMEA sentence
        if (line.startsWith("$")) {
            parseNMEASentence(line);
        }
    }
}

void RadarInterface::parseNMEASentence(const QString &sentence)
{
    // Validate checksum
    int asteriskIndex = sentence.indexOf('*');
    if (asteriskIndex == -1) {
        qWarning() << "Invalid NMEA sentence: No checksum";
        return;
    }

    QString dataWithoutChecksum = sentence.mid(1, asteriskIndex - 1);
    QString checksumStr = sentence.mid(asteriskIndex + 1);
    bool ok;
    int receivedChecksum = checksumStr.toInt(&ok, 16);
    if (!ok) {
        qWarning() << "Invalid NMEA checksum format";
        return;
    }

    int calculatedChecksum = 0;
    for (QChar ch : dataWithoutChecksum) {
        calculatedChecksum ^= ch.unicode();
    }

    if (calculatedChecksum != receivedChecksum) {
        qWarning() << "Checksum mismatch";
        return;
    }

    // Split the data into fields
    QStringList fields = dataWithoutChecksum.split(',');

    if (fields.isEmpty())
        return;

    QString messageType = fields[0];

    if (messageType == "RATTM") {
        // Parse RATTM message
        if (fields.size() < 13) {
            qWarning() << "Incomplete RATTM message";
            return;
        }

        RadarTarget target;
        bool ok;

        // Extract target ID
        target.id = fields[1].toInt(&ok);
        if (!ok) {
            qWarning() << "Invalid target ID";
            return;
        }

        // Extract range (nautical miles to meters)
        double rangeNm = fields[2].toDouble(&ok);
        if (!ok) {
            qWarning() << "Invalid range";
            return;
        }
        target.range = rangeNm * 1852.0; // Convert nautical miles to meters

        // Extract azimuth (degrees)
        target.azimuth = fields[3].toDouble(&ok);
        if (!ok) {
            qWarning() << "Invalid azimuth";
            return;
        }

        // You can extract additional fields as needed

        // Update the target list
        QMutexLocker locker(&mutex);
        targets[target.id] = target;

        emit targetUpdated(target);
    } else {
        // Handle other NMEA message types if necessary
    }
}

QMap<int, RadarTarget> RadarInterface::getTargets()
{
    QMutexLocker locker(&mutex);
    return targets;
}
