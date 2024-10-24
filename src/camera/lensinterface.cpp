#include "include/camera/lensinterface.h"
#include <QDebug>


LensInterface::LensInterface(QObject *parent)
    : QObject(parent), lensSerial(nullptr), abort(false)
{}

LensInterface::~LensInterface() {
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    //wait();
}

void LensInterface::setSerialPort(QSerialPort *serial) {
    lensSerial = serial;
}


QString LensInterface::sendCommand(const QString &command) {
    if (lensSerial && lensSerial->isOpen()) {
        // Send the command with a carriage return
        lensSerial->write((command + "\r").toUtf8());
        lensSerial->waitForBytesWritten(100);

        // Wait for and read the response
        if (lensSerial->waitForReadyRead(1000)) {
            QByteArray response = lensSerial->readAll();
            emit responseReceived(QString(response).trimmed());
            return QString(response).trimmed();
        }
    }
    return QString();
}

void LensInterface::moveToWFOV() {
    QString command = "/MPAv 0, p";
    sendCommand(command);
    emit commandSent();
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
