#include "include/gimbal/servodriverinterface.h"
#include <QDebug>

ServoDriverInterface::ServoDriverInterface(const QString &identifier,
                                           const QString &device,
                                           int baudRate,
                                           int slaveId,
                                           QObject *parent)
    : QObject(parent),
      m_identifier(identifier),
      m_device(device),
      m_baudRate(baudRate),
      m_slaveId(slaveId),
      m_modbusContext(nullptr),
      m_readTimer(new QTimer(this)),
      m_timeoutTimer(new QTimer(this))
{
    // Initialize Modbus context
    m_modbusContext = modbus_new_rtu(m_device.toStdString().c_str(), m_baudRate, 'N', 8, 1);
    if (!m_modbusContext) {
        logError("Failed to create Modbus RTU context.");
        return;
    }

    if (modbus_set_slave(m_modbusContext, m_slaveId) == -1) {
        logError(QString("Failed to set slave ID: %1").arg(modbus_strerror(errno)));
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        return;
    }

    // Set up read timer
    connect(m_readTimer, &QTimer::timeout, this, &ServoDriverInterface::readData);
    m_readTimer->setInterval(50); // Adjust interval as needed

    // Set up timeout timer
    connect(m_timeoutTimer, &QTimer::timeout, this, &ServoDriverInterface::handleTimeout);
    m_timeoutTimer->setSingleShot(true);
}

ServoDriverInterface::~ServoDriverInterface() {
    disconnectDevice();
}

bool ServoDriverInterface::connectDevice() {
    if (!m_modbusContext)
        return false;

    if (modbus_connect(m_modbusContext) == -1) {
        logError(QString("Failed to connect to Modbus device: %1").arg(modbus_strerror(errno)));
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        return false;
    }

    emit logMessage(QString("[%1] Modbus connection established successfully.").arg(m_identifier));

    // Start reading data
    m_readTimer->start();
    return true;
}

void ServoDriverInterface::disconnectDevice() {
    if (m_modbusContext) {
        modbus_close(m_modbusContext);
        modbus_free(m_modbusContext);
        m_modbusContext = nullptr;
        emit logMessage(QString("[%1] Modbus connection closed.").arg(m_identifier));
    }

    if (m_readTimer->isActive())
        m_readTimer->stop();
}

void ServoDriverInterface::readData() {
    if (!m_modbusContext)
        return;

    QVector<uint16_t> data(50);

    m_modbusMutex.lock();
    int rc = modbus_read_registers(m_modbusContext, 196, data.size(), data.data());
    m_modbusMutex.unlock();

    if (rc == -1) {
        logError(QString("Read error: %1").arg(modbus_strerror(errno)));
        // Start timeout timer
        if (!m_timeoutTimer->isActive())
            m_timeoutTimer->start(1000); // Adjust timeout as needed
    } else {
        emit dataRead(data);
        // Stop timeout timer if running
        if (m_timeoutTimer->isActive())
            m_timeoutTimer->stop();
    }
}

void ServoDriverInterface::handleTimeout() {
    logError("Timeout waiting for response from servo driver.");
    // Handle timeout (e.g., attempt reconnection)
}

void ServoDriverInterface::logError(const QString &message) {
    emit logMessage(QString("[%1] %2").arg(m_identifier, message));
    qWarning() << QString("[%1] %2").arg(m_identifier, message);
}
