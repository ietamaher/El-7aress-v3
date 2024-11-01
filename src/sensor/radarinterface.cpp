#include "include/sensor/radarinterface.h"
#include <QDebug>
#include <QStringList>
#include <QTimer>

RadarInterface::RadarInterface(QObject *parent)
    : QObject(parent), radarSerial(new QSerialPort(this)), m_isConnected(false)
{
}

RadarInterface::~RadarInterface()
{
    shutdown();
}

bool RadarInterface::openSerialPort(const QString &portName) {
    if (radarSerial->isOpen()) {
        radarSerial->close();
    }

    radarSerial->setPortName(portName);
    radarSerial->setBaudRate(QSerialPort::Baud4800);
    radarSerial->setDataBits(QSerialPort::Data8);
    radarSerial->setParity(QSerialPort::NoParity);
    radarSerial->setStopBits(QSerialPort::OneStop);
    radarSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (radarSerial->open(QIODevice::ReadOnly)) {
        connect(radarSerial, &QSerialPort::readyRead, this, &RadarInterface::processIncomingData);
        connect(radarSerial, &QSerialPort::errorOccurred, this, &RadarInterface::handleSerialError);
        qDebug() << "Opened radar serial port:" << portName;
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        return true;
    } else {
       qDebug() << "Failed to open radar serial port:" << radarSerial->errorString();
        emit errorOccurred(radarSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void RadarInterface::closeSerialPort() {
    if (radarSerial->isOpen()) {
        radarSerial->close();
        qDebug() << "Closed radar serial port:" << radarSerial->portName();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
    }
}

void RadarInterface::shutdown() {
    closeSerialPort();
    // Additional cleanup if necessary
}



void RadarInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
       qDebug() << "Radar serial port error occurred:" << radarSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &RadarInterface::attemptReconnection);
    }
}

void RadarInterface::attemptReconnection() {
    if (!radarSerial->isOpen()) {
        if (openSerialPort(radarSerial->portName())) {
            qDebug() << "Radar serial port reconnected.";
            // Reinitialize if necessary
        } else {
           qDebug() << "Failed to reopen radar serial port:" << radarSerial->errorString();
            // Retry after some time
            QTimer::singleShot(5000, this, &RadarInterface::attemptReconnection);
        }
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
       qDebug() << "Invalid NMEA sentence: No checksum";
        return;
    }

    QString dataWithoutChecksum = sentence.mid(1, asteriskIndex - 1);
    QString checksumStr = sentence.mid(asteriskIndex + 1);
    bool ok;
    int receivedChecksum = checksumStr.toInt(&ok, 16);
    if (!ok) {
       qDebug() << "Invalid NMEA checksum format";
        return;
    }

    int calculatedChecksum = 0;
    for (QChar ch : dataWithoutChecksum) {
        calculatedChecksum ^= ch.unicode();
    }

    if (calculatedChecksum != receivedChecksum) {
       qDebug() << "Checksum mismatch";
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
           qDebug() << "Incomplete RATTM message";
            return;
        }

        RadarTarget target;
        bool ok;

        // Extract target ID
        target.id = fields[1].toInt(&ok);
        if (!ok) {
           qDebug() << "Invalid target ID";
            return;
        }

        // Extract range (nautical miles to meters)
        double rangeNm = fields[2].toDouble(&ok);
        if (!ok) {
           qDebug() << "Invalid range";
            return;
        }
        target.range = rangeNm * 1852.0; // Convert nautical miles to meters

        // Extract azimuth (degrees)
        target.azimuth = fields[3].toDouble(&ok);
        if (!ok) {
           qDebug() << "Invalid azimuth";
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
