#ifndef MODBUSINTERFACE_H
#define MODBUSINTERFACE_H

#include <QObject>
 #include <modbus/modbus.h>

class ModbusInterface : public QObject {
    Q_OBJECT
public:
    explicit ModbusInterface(QObject *parent = nullptr);
    ~ModbusInterface();

    // Motion command methods
    bool sendMotionCommand(double azimuthSpeed, double elevationSpeed);
    bool sendPositionCommand(double targetAzimuth, double targetElevation);

    // Feedback methods
    double readAzimuth();
    double readElevation();

    // Initialization and connection methods
    bool connectToPLC(const char* device, int baud, char parity, int data_bit, int stop_bit);
    void disconnectFromPLC();

private:
    modbus_t *m_modbusContext;
    int m_slaveId;
    bool m_connected;

    // Helper methods
    bool writeRegisters(int addr, int nb, const uint16_t *data);
    bool readRegisters(int addr, int nb, uint16_t *dest);
};

#endif // MODBUSINTERFACE_H

