#include "include/comm/modbusinterface.h"
#include <QDebug>

ModbusInterface::ModbusInterface(QObject *parent)
    : QObject(parent),
    m_modbusContext(nullptr),
    m_slaveId(1), // Set the Modbus slave ID of the PLC
    m_connected(false)
{
}

ModbusInterface::~ModbusInterface()
{
    disconnectFromPLC();
}

bool ModbusInterface::connectToPLC(const char* device, int baud, char parity, int data_bit, int stop_bit)
{
    m_modbusContext = modbus_new_rtu(device, baud, parity, data_bit, stop_bit);
    if (m_modbusContext == nullptr) {
        qCritical() << "Unable to create the libmodbus context";
        return false;
    }

    modbus_set_slave(m_modbusContext, m_slaveId);
    modbus_set_response_timeout(m_modbusContext, 0, 200000); // 200 ms

    if (modbus_connect(m_modbusContext) == -1) {
        qCritical() << "Connection failed: " << modbus_strerror(errno);
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        return false;
    }

    m_connected = true;
    qDebug() << "Connected to PLC via Modbus RTU";
    return true;
}

void ModbusInterface::disconnectFromPLC()
{
    if (m_modbusContext) {
        modbus_close(m_modbusContext);
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        m_connected = false;
        qDebug() << "Disconnected from PLC";
    }
}

bool ModbusInterface::writeRegisters(int addr, int nb, const uint16_t *data)
{
    if (!m_connected) {
        qCritical() << "Not connected to PLC";
        return false;
    }

    int rc = modbus_write_registers(m_modbusContext, addr, nb, data);
    if (rc == -1) {
        qCritical() << "Write error: " << modbus_strerror(errno);
        return false;
    }
    return true;
}

bool ModbusInterface::readRegisters(int addr, int nb, uint16_t *dest)
{
    if (!m_connected) {
        qCritical() << "Not connected to PLC";
        return false;
    }

    int rc = modbus_read_registers(m_modbusContext, addr, nb, dest);
    if (rc == -1) {
        qCritical() << "Read error: " << modbus_strerror(errno);
        return false;
    }
    return true;
}

bool ModbusInterface::sendMotionCommand(double azimuthSpeed, double elevationSpeed)
{
    // Convert speeds to register values
    uint16_t registers[2];
    registers[0] = static_cast<uint16_t>(azimuthSpeed * 100);    // Example scaling
    registers[1] = static_cast<uint16_t>(elevationSpeed * 100);  // Example scaling

    // Assume that the PLC expects motion commands at register address 0
    return writeRegisters(0, 2, registers);
}

bool ModbusInterface::sendPositionCommand(double targetAzimuth, double targetElevation)
{
    // Convert positions to register values
    uint16_t registers[2];
    registers[0] = static_cast<uint16_t>(targetAzimuth * 100);    // Example scaling
    registers[1] = static_cast<uint16_t>(targetElevation * 100);  // Example scaling

    // Assume that the PLC expects position commands at register address 10
    return writeRegisters(10, 2, registers);
}

double ModbusInterface::readAzimuth()
{
    uint16_t value;
    if (!readRegisters(100, 1, &value)) {  // Assume azimuth feedback is at register 100
        return 0.0;
    }
    return static_cast<double>(value) / 100.0;  // Convert back to degrees
}

double ModbusInterface::readElevation()
{
    uint16_t value;
    if (!readRegisters(101, 1, &value)) {  // Assume elevation feedback is at register 101
        return 0.0;
    }
    return static_cast<double>(value) / 100.0;  // Convert back to degrees
}
