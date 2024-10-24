#include "include/comm/plcmodbuscommunication.h"
#include <QDebug>

PLCModbusCommunication::PLCModbusCommunication(const QString &portName, int baudRate, QObject *parent)
    : QObject(parent),
    m_modbusContext(nullptr),
    m_portName(portName),
    m_baudRate(baudRate)
{
    m_modbusContext = modbus_new_rtu(m_portName.toStdString().c_str(), m_baudRate, 'N', 8, 1);
    if (!m_modbusContext) {
        logError("Failed to create Modbus RTU context");
    }
    int m_slaveId = 2 ;
    modbus_set_slave(m_modbusContext, m_slaveId);
}

PLCModbusCommunication::~PLCModbusCommunication() {
    disconnectDevice();
}

bool PLCModbusCommunication::connectDevice() {
    if (m_modbusContext && modbus_connect(m_modbusContext) == -1) {
        logError(QString("Failed to connect to Modbus device: %1").arg(modbus_strerror(errno)));
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        return false;
    }
    emit logMessage("Connected to PLC via Modbus successfully.");
    return true;
}

void PLCModbusCommunication::disconnectDevice() {
    if (m_modbusContext) {
        modbus_close(m_modbusContext);
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        emit logMessage("Disconnected from PLC.");
    }
}

bool PLCModbusCommunication::writeRegister(int address, uint16_t value) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return false;

    int rc = modbus_write_register(m_modbusContext, address, value);
    if (rc == -1) {
        logError(QString("Failed to write register at address %1: %2").arg(address).arg(modbus_strerror(errno)));
        return false;
    }
    return true;
}

bool PLCModbusCommunication::writeRegisters(int address, const QVector<uint16_t> &values) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return false;

    int rc = modbus_write_registers(m_modbusContext, address, values.size(), values.data());
    if (rc == -1) {
        logError(QString("Failed to write registers starting at address %1: %2").arg(address).arg(modbus_strerror(errno)));
        return false;
    }
    return true;
}

bool PLCModbusCommunication::readRegisters(int address, int count, QVector<uint16_t> &values) {
    QMutexLocker locker(&m_modbusMutex);
    if (!m_modbusContext) return false;

    values.resize(count);
    int rc = modbus_read_registers(m_modbusContext, address, count, values.data());
    if (rc == -1) {
        logError(QString("Failed to read registers starting at address %1: %2").arg(address).arg(modbus_strerror(errno)));
        return false;
    }
    return true;
}

void PLCModbusCommunication::logError(const QString &message) {
    emit logMessage(message);
    qWarning() << "PLCModbusCommunication:" << message;
}

