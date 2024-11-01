#include "include/camera/lensinterface.h"
#include <QDebug>
#include <QTimer>

LensInterface::LensInterface(QObject *parent)
    : QObject(parent), lensSerial(new QSerialPort(this)), m_isConnected(false)
{
}

LensInterface::~LensInterface() {
    shutdown();
}

bool LensInterface::openSerialPort(const QString &portName) {
    if (lensSerial->isOpen()) {
        lensSerial->close();
    }

    lensSerial->setPortName(portName);
    lensSerial->setBaudRate(QSerialPort::Baud9600); // Adjust as necessary
    lensSerial->setDataBits(QSerialPort::Data8);
    lensSerial->setParity(QSerialPort::NoParity);
    lensSerial->setStopBits(QSerialPort::OneStop);
    lensSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (lensSerial->open(QIODevice::ReadWrite)) {
        connect(lensSerial, &QSerialPort::errorOccurred, this, &LensInterface::handleSerialError);
        m_isConnected = true;
        emit statusChanged(m_isConnected);
        qDebug() << "Opened lens serial port:" << portName;
        return true;
    } else {
        qWarning() << "Failed to open lens serial port:" << lensSerial->errorString();
        emit errorOccurred(lensSerial->errorString());
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        return false;
    }
}

void LensInterface::closeSerialPort() {
    if (lensSerial->isOpen()) {
        lensSerial->close();
        m_isConnected = false;
        emit statusChanged(m_isConnected);
        qDebug() << "Closed lens serial port:" << lensSerial->portName();
    }
}

void LensInterface::shutdown() {
    closeSerialPort();
    // Additional cleanup if necessary
}

void LensInterface::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError) {
        qWarning() << "Lens serial port error occurred:" << lensSerial->errorString();
        closeSerialPort();
        QTimer::singleShot(1000, this, &LensInterface::attemptReconnection);
    }
}

void LensInterface::attemptReconnection() {
    if (!lensSerial->isOpen()) {
        if (openSerialPort(lensSerial->portName())) {
            qDebug() << "Lens serial port reconnected.";
            // Reinitialize if necessary
        } else {
            qWarning() << "Failed to reopen lens serial port:" << lensSerial->errorString();
            QTimer::singleShot(5000, this, &LensInterface::attemptReconnection);
        }
    }
}

QString LensInterface::sendCommand(const QString &command) {
    if (lensSerial && lensSerial->isOpen()) {
        // Send the command with a carriage return
        lensSerial->write((command + "\r").toUtf8());
        if (!lensSerial->waitForBytesWritten(100)) {
            emit errorOccurred("Failed to write to lens serial port.");
            return QString();
        }

        // Wait for and read the response
        if (lensSerial->waitForReadyRead(1000)) {
            QByteArray responseData = lensSerial->readAll();
            while (lensSerial->waitForReadyRead(10))
                responseData += lensSerial->readAll();

            QString response = QString::fromUtf8(responseData).trimmed();
            emit responseReceived(response);
            return response;
        } else {
            emit errorOccurred("No response from lens.");
            return QString();
        }
    } else {
        emit errorOccurred("Lens serial port is not open.");
        return QString();
    }
}

// Implement lens control methods similar to before, e.g.:
void LensInterface::moveToWFOV() {
    sendCommand("/MPAv 0, p");
}

void LensInterface::moveToNFOV() {
    QString command = "/MPAv 100, p";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::moveToIntermediateFOV(int percentage) {
    QString command = QString("/MPAv %1, p").arg(percentage);
    sendCommand(command);
    emit commandSent();
}

void LensInterface::moveToFocalLength(int efl) {
    QString command = QString("/MPAv %1, F").arg(efl);
    sendCommand(command);
    emit commandSent();
}

void LensInterface::moveToInfinityFocus() {
    QString command = "/MPAf 100, u";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::moveFocusNear(int amount) {
    QString command = QString("/MPRf %1").arg(-amount);
    sendCommand(command);
    emit commandSent();
}

void LensInterface::moveFocusFar(int amount) {
    QString command = QString("/MPRf %1").arg(amount);
    sendCommand(command);
    emit commandSent();
}

void LensInterface::getFocusPosition() {
    QString command = "/GMSf[2] 1";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::getLensTemperature() {
    QString command = "/GTV";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::resetController() {
    QString command = "/RST0 NEOS";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::homeAxis(int axis) {
    QString command = QString("/HOM%1").arg(axis);
    sendCommand(command);
    emit commandSent();
}

void LensInterface::turnOnTemperatureCompensation() {
    QString command = "/MDF[4] 2";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::turnOffTemperatureCompensation() {
    QString command = "/MDF[4] 0";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::turnOnRangeCompensation() {
    QString command = "/MDF[5] 2";
    sendCommand(command);
    emit commandSent();
}

void LensInterface::turnOffRangeCompensation() {
    QString command = "/MDF[5] 0";
    sendCommand(command);
    emit commandSent();
}
