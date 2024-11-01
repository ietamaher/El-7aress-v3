#include "include/sensor/lrfinterface.h"
#include <QDebug>
#include <QTimer>

LRFInterface::LRFInterface(QObject *parent)
    : QObject(parent), lrfSerial(new QSerialPort(this)), abort(false), m_isConnected(false)
{}

LRFInterface::~LRFInterface() {
    shutdown();
}

void LRFInterface::setSerialPort(QSerialPort *serial) {
    lrfSerial = serial;
    if (lrfSerial) {
        // Connect readyRead signal to processIncomingData slot
        connect(lrfSerial, &QSerialPort::readyRead, this, &LRFInterface::processIncomingData);

        // Optionally, handle serial port errors
        connect(lrfSerial, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error){
            if (error != QSerialPort::NoError) {
                qDebug() << "Serial Port Error:" << lrfSerial->errorString();
                emit errorOccurred(lrfSerial->errorString());
                updateConnectionStatus(false);
            }
        });
    }
}
bool LRFInterface::openSerialPort(const QString &portName) {
    if (lrfSerial->isOpen()) {
        lrfSerial->close();
    }

    lrfSerial->setPortName(portName);
    lrfSerial->setBaudRate(QSerialPort::Baud9600);
    lrfSerial->setDataBits(QSerialPort::Data8);
    lrfSerial->setParity(QSerialPort::NoParity);
    lrfSerial->setStopBits(QSerialPort::OneStop);
    lrfSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (lrfSerial->open(QIODevice::ReadWrite)) {
        connect(lrfSerial, &QSerialPort::readyRead, this, &LRFInterface::processIncomingData);
        connect(lrfSerial, &QSerialPort::errorOccurred, this, &LRFInterface::handleSerialError);
        qDebug() << "Opened serial port:" << portName;
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        return true;
    } else {
       qDebug() << "Failed to open serial port:" << lrfSerial->errorString();
        emit errorOccurred(lrfSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void LRFInterface::shutdown() {
    // Close the serial port
    closeSerialPort();
}

void LRFInterface::closeSerialPort() {
    if (lrfSerial->isOpen()) {
        lrfSerial->close();
        qDebug() << "Closed serial port:" << lrfSerial->portName();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
    }
}


void LRFInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
       qDebug() << "Serial port error occurred:" << lrfSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &LRFInterface::attemptReconnection);
    }
}

void LRFInterface::attemptReconnection() {
    if (!lrfSerial->isOpen()) {
        if (openSerialPort(lrfSerial->portName())) {
            qDebug() << "Serial port reconnected.";
            // Reinitialize as necessary
        } else {
           qDebug() << "Failed to reopen serial port:" << lrfSerial->errorString();
            // Retry after some time
            QTimer::singleShot(5000, this, &LRFInterface::attemptReconnection);
        }
    }
}
void LRFInterface::updateConnectionStatus(bool isConnected)
{
    if (m_isConnected != isConnected) {
        m_isConnected = isConnected;
        emit statusChanged(m_isConnected);
    }
}

quint8 LRFInterface::calculateChecksum(const QByteArray &command) const {
    quint8 checksum = 0;
    for (char byte : command) {
        checksum += static_cast<quint8>(byte);
    }
    return checksum & 0xFF;
}

bool LRFInterface::verifyChecksum(const QByteArray &response) const {
    if (response.size() < 1) return false;
    quint8 receivedChecksum = static_cast<quint8>(response.at(response.size() - 1));
    quint8 calculatedChecksum = calculateChecksum(response.left(response.size() - 1));
    return receivedChecksum == calculatedChecksum;
}

QByteArray LRFInterface::buildCommand(const QByteArray &commandTemplate) const {
    QByteArray command = commandTemplate;
    quint8 checksum = calculateChecksum(command);
    command.append(static_cast<char>(checksum));
    return command;
}

QByteArray LRFInterface::sendCommand(const QByteArray &command) {
    if (lrfSerial && lrfSerial->isOpen()) {
        lrfSerial->write(command);
        if (!lrfSerial->waitForBytesWritten(20)) { // Reduced timeout
            //TODO Add waitForReadyRead    lrfSerial->waitForReadyRead(1000);!!!
            emit errorOccurred("Failed to write bytes to serial port.");
            return QByteArray();
        }
        // Note: Not waiting for ready read here to allow asynchronous handling
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        return command;
    }
    emit errorOccurred("Serial port is not open.");
    return QByteArray();
}

void LRFInterface::sendSelfCheck() {
    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x02)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::SelfCheck));
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::sendSingleRanging() {
    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x02)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::SingleRanging));
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::sendContinuousRanging() {
    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x02)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::ContinuousRanging));
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::stopRanging() {
    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x02)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::StopRanging));
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::setFrequency(int frequency) {
    if ((frequency < 1) || (frequency > 5)) {
        emit errorOccurred("Invalid frequency value. Must be between 1 and 5 Hz.");
        return;
    }

    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x03)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::SetFrequency));
    commandTemplate.append(static_cast<char>(frequency)); // Frequency (1-5 Hz)
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::querySettingValue() {
    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x02)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::QuerySettingValue));
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::queryAccumulatedLaserCount() {
    QByteArray commandTemplate;
    commandTemplate.append(static_cast<char>(0xEB));
    commandTemplate.append(static_cast<char>(0x90));
    commandTemplate.append(static_cast<char>(0x02)); // Data Length
    commandTemplate.append(static_cast<char>(DeviceCode::LRF));
    commandTemplate.append(static_cast<char>(CommandCode::QueryLaserCount));
    QByteArray command = buildCommand(commandTemplate);
    sendCommand(command);
}

void LRFInterface::handleResponse(const QByteArray &response) {
    if (response.isEmpty()) {
        emit errorOccurred("No response received from LRF.");
        return;
    }

    // Minimum response size based on the smallest possible response
    if (response.size() < 5) {
        emit errorOccurred("Incomplete response received from LRF.");
        return;
    }

    // Check if response starts with the correct header (0xEB 0x90)
    if (static_cast<quint8>(response.at(0)) != 0xEB ||
        static_cast<quint8>(response.at(1)) != 0x90) {
        emit errorOccurred("Invalid response header.");
        return;
    }

    // Extract Data Length
    quint8 dataLength = static_cast<quint8>(response.at(2));
    if (response.size() != (3 + dataLength + 1)) { // Header + Data + Checksum
        emit errorOccurred("Response length mismatch.");
        return;
    }

    // Extract Device Code and Response Code
    quint8 deviceCode = static_cast<quint8>(response.at(3));
    quint8 responseCode = static_cast<quint8>(response.at(4));

    // Verify Device Code
    if (deviceCode != DeviceCode::LRF) {
        emit errorOccurred("Invalid device code in response.");
        return;
    }

    // Handle different response types based on the response code
    switch (responseCode) {
        case ResponseCode::SelfCheckResponse:
            handleSelfCheckResponse(response);
            break;
        case ResponseCode::SingleRangingResponse:
            handleRangingResponse(response);
            break;
        case ResponseCode::ContinuousRangingResponse:
            handleRangingResponse(response); // Handle same as single ranging
            break;
        case ResponseCode::SetFrequencyResponse:
            handleSetFrequencyResponse(response);
            break;
        case ResponseCode::QueryLaserCountResponse:
            handleLaserCountResponse(response);
            break;
        case ResponseCode::QuerySettingValueResponse:
            handleSettingValueResponse(response);
            break;
        default:
            emit errorOccurred(QString("Unknown response code: 0x%1").arg(responseCode, 2, 16, QChar('0')).toUpper());
            break;
    }
}

void LRFInterface::handleSelfCheckResponse(const QByteArray &response) {
    // Expected response length: 12 data bytes + header + checksum = 15 bytes
    if (response.size() < 15) {
        emit errorOccurred("Incomplete self-check response.");
        return;
    }

    // Data content starts from byte 5 to byte 14 (10 bytes)
    // According to documentation, system status and alarms are defined in specific bits
    // Parsing based on assumed byte positions

    // Byte 5: Status Byte
    quint8 statusByte = static_cast<quint8>(response.at(5));

    // Bit definitions:
    // D7: System status (0: Normal, 1: Abnormal)
    // D6: Temperature alarm (0: Normal, 1: Alarm)
    // D5: Bias voltage fault (0: Normal, 1: Fault)
    // D4: Counter malfunction (0: Normal, 1: Fault)
    // D3-D0: Reserved or standby

    quint8 systemStatus = (statusByte & 0x80) >> 7;
    quint8 temperatureAlarm = (statusByte & 0x40) >> 6;
    quint8 biasVoltageFault = (statusByte & 0x20) >> 5;
    quint8 counterMalfunction = (statusByte & 0x10) >> 4;

    emit selfCheckResult(systemStatus, temperatureAlarm, biasVoltageFault, counterMalfunction);
}

void LRFInterface::handleRangingResponse(const QByteArray &response) {
    // Expected response length: 12 data bytes + header + checksum = 15 bytes
    if (response.size() < 15) {
        emit errorOccurred("Incomplete ranging response.");
        return;
    }

    // Data content:
    // Byte 5: Status
    // Bytes 6-7: Ranging Value 1 (high, low)
    // Byte 8: Decimal Places for Value 1
    // Bytes 9-10: Ranging Value 2 (high, low)
    // Byte 11: Decimal Places for Value 2
    // Bytes 12-13: Ranging Value 3 (high, low)
    // Byte 14: Decimal Places for Value 3

    quint8 status = static_cast<quint8>(response.at(5));

    // Parsing status bits
    quint8 systemStatus = (status & 0x80) >> 7;
    quint8 frontDischargePowerSwitch = (status & 0x40) >> 6;
    quint8 ldPowerSwitch = (status & 0x20) >> 5;
    quint8 biasSwitch = (status & 0x10) >> 4;
    quint8 workingStatus = (status & 0x08) >> 3;
    quint8 echoStatus = (status & 0x04) >> 2;
    quint8 temperatureAlarm = (status & 0x02) >> 1;
    quint8 reserved = (status & 0x01);

    // Ranging Value 1
    quint16 rangingValue1 = (static_cast<quint8>(response.at(6)) << 8) |
                              static_cast<quint8>(response.at(7));
    quint8 decimalPlaces1 = static_cast<quint8>(response.at(8));

    // Ranging Value 2
    quint16 rangingValue2 = (static_cast<quint8>(response.at(9)) << 8) |
                              static_cast<quint8>(response.at(10));
    quint8 decimalPlaces2 = static_cast<quint8>(response.at(11));

    // Ranging Value 3
    quint16 rangingValue3 = (static_cast<quint8>(response.at(12)) << 8) |
                              static_cast<quint8>(response.at(13));
    quint8 decimalPlaces3 = static_cast<quint8>(response.at(14));

    // Combine integer and decimal parts
    double distance1 = rangingValue1 + (decimalPlaces1 / 100.0);
    double distance2 = rangingValue2 + (decimalPlaces2 / 100.0);
    double distance3 = rangingValue3 + (decimalPlaces3 / 100.0);

    // For continuous ranging, we might receive multiple rangingDataReceived signals
    // Here, we'll emit the first distance value as an example
    emit rangingDataReceived(status, rangingValue1, decimalPlaces1, echoStatus);
}

void LRFInterface::handleSetFrequencyResponse(const QByteArray &response) {
    // Expected response length: 12 data bytes + header + checksum = 15 bytes
    if (response.size() < 15) {
        emit errorOccurred("Incomplete set frequency response.");
        return;
    }

    // Data content:
    // Byte 10: Ranging Frequency (1-5 Hz)
    // Byte 11: Major Version
    // Byte 12: Secondary Version
    // Byte 13: Maintenance Version

    quint8 rangingFrequency = static_cast<quint8>(response.at(10));
    quint8 majorVersion = static_cast<quint8>(response.at(11));
    quint8 secondaryVersion = static_cast<quint8>(response.at(12));
    quint8 maintenanceVersion = static_cast<quint8>(response.at(13));

    emit frequencySet(rangingFrequency, majorVersion, secondaryVersion, maintenanceVersion);
}

void LRFInterface::handleSettingValueResponse(const QByteArray &response) {
    // Expected response length: 12 data bytes + header + checksum = 15 bytes
    if (response.size() < 15) {
        emit errorOccurred("Incomplete setting value response.");
        return;
    }

    // Data content:
    // Byte 10: Setting Value (Ranging Frequency)

    quint8 settingValue = static_cast<quint8>(response.at(10));

    emit settingValueReceived(settingValue);
}

void LRFInterface::handleLaserCountResponse(const QByteArray &response) {
    // Expected response length: 12 data bytes + header + checksum = 15 bytes
    if (response.size() < 15) {
        emit errorOccurred("Incomplete laser count response.");
        return;
    }

    // Data content:
    // Bytes 6-9: Cumulative Laser Shot Count (4 bytes: D31-D0)

    quint32 laserCount = (static_cast<quint8>(response.at(6)) << 24) |
                         (static_cast<quint8>(response.at(7)) << 16) |
                         (static_cast<quint8>(response.at(8)) << 8) |
                         static_cast<quint8>(response.at(9));

    emit laserCountReceived(laserCount);
}

void LRFInterface::processIncomingData() {
    if (!lrfSerial) return;

    readBuffer += lrfSerial->readAll();

    while (readBuffer.size() >= 3) { // Minimum bytes to determine packet length
        // Look for start bytes
        if (static_cast<quint8>(readBuffer.at(0)) != 0xEB ||
            static_cast<quint8>(readBuffer.at(1)) != 0x90) {
            // Remove the first byte and continue searching
            readBuffer.remove(0, 1);
            continue;
        }

        // Extract Data Length
        quint8 dataLength = static_cast<quint8>(readBuffer.at(2));
        int totalPacketSize = 3 + dataLength + 1; // Header (3) + Data + Checksum (1)

        if (readBuffer.size() < totalPacketSize) {
            // Wait for the full packet to arrive
            break;
        }

        // Extract the full packet
        QByteArray packet = readBuffer.left(totalPacketSize);
        readBuffer.remove(0, totalPacketSize);

        // Verify checksum
        if (!verifyChecksum(packet)) {
            emit errorOccurred("Checksum mismatch in incoming packet.");
            continue;
        }

        // Handle the response
        handleResponse(packet);
    }
}
