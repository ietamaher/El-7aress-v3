#include "include/gimbal/mduinocontroller.h"
#include <QDebug>

MduinoController::MduinoController(const QString &portName, int baudRate, int slaveId, QObject *parent)
    : QObject(parent),
      m_modbusContext(nullptr),
      m_portName(portName),
      m_baudRate(baudRate),
      m_slaveId(slaveId)
{
    m_modbusContext = modbus_new_rtu(m_portName.toStdString().c_str(), m_baudRate, 'N', 8, 1);
    if (!m_modbusContext) {
        logError("Failed to create Modbus RTU context");
    } else {
        if (modbus_set_slave(m_modbusContext, m_slaveId) == -1) {
            logError(QString("Failed to set slave ID: %1").arg(modbus_strerror(errno)));
            modbus_free(m_modbusContext);
            m_modbusContext = nullptr;
        }
    }
}

MduinoController::~MduinoController() {
    disconnectDevice();
}

bool MduinoController::connectDevice() {
    if (m_modbusContext && modbus_connect(m_modbusContext) == -1) {
        logError(QString("Failed to connect to Modbus device: %1").arg(modbus_strerror(errno)));
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        return false;
    }
    emit logMessage("Connected to mduino industrial shield successfully.");
    return true;
}

void MduinoController::disconnectDevice() {
    if (m_modbusContext) {
        modbus_close(m_modbusContext);
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        emit logMessage("Disconnected from mduino industrial shield.");
    }
}

void MduinoController::setAzimuthPulse(int pulse) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return;

    uint16_t value = static_cast<uint16_t>(pulse);
    int rc = modbus_write_register(m_modbusContext, /* address */ 0, value); // Replace 0 with actual register address
    if (rc == -1) {
        logError(QString("Failed to write azimuth pulse: %1").arg(modbus_strerror(errno)));
    }
}

void MduinoController::setAzimuthDirection(bool direction) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return;

    uint16_t value = direction ? 1 : 0;
    int rc = modbus_write_register(m_modbusContext, /* address */ 1, value); // Replace 1 with actual register address
    if (rc == -1) {
        logError(QString("Failed to write azimuth direction: %1").arg(modbus_strerror(errno)));
    }
}

void MduinoController::setElevationPulse(int pulse) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return;

    uint16_t value = static_cast<uint16_t>(pulse);
    int rc = modbus_write_register(m_modbusContext, /* address */ 2, value); // Replace 2 with actual register address
    if (rc == -1) {
        logError(QString("Failed to write elevation pulse: %1").arg(modbus_strerror(errno)));
    }
}

void MduinoController::setElevationDirection(bool direction) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return;

    uint16_t value = direction ? 1 : 0;
    int rc = modbus_write_register(m_modbusContext, /* address */ 3, value); // Replace 3 with actual register address
    if (rc == -1) {
        logError(QString("Failed to write elevation direction: %1").arg(modbus_strerror(errno)));
    }
}

void MduinoController::logError(const QString &message) {
    emit logMessage(message);
   qDebug() << "MduinoController:" << message;
}
