 // devicemanager.h
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <memory>

// Forward declarations for device classes
class PLCModbusCommunication;
class QSerialPort;
class QCamera;
class Joystick;

class DeviceManager : public QObject
{
    Q_OBJECT
public:
    static DeviceManager& instance(); // Singleton access

    // Accessors for devices
    std::shared_ptr<PLCModbusCommunication> getPLCModbusCommunication();
    std::shared_ptr<QSerialPort> getSerialPort(int index); // For multiple serial ports
    std::shared_ptr<QCamera> getCamera(int index); // For multiple cameras
    std::shared_ptr<Joystick> getJoystick();
    bool initializeFromConfig(const QString &configFilePath);


signals:
    void logMessage(const QString &message);

private:
    DeviceManager(QObject *parent = nullptr);
    ~DeviceManager();

    // Delete copy constructor and assignment operator
    DeviceManager(const DeviceManager&) = delete;
    DeviceManager& operator=(const DeviceManager&) = delete;

    // Initialization methods
    bool initializePLCModbusCommunication();
    bool initializeSerialPorts();
    bool initializeCameras();
    bool initializeJoystick();

    // Device instances
    std::shared_ptr<PLCModbusCommunication> m_plcModbusComm;
    std::vector<std::shared_ptr<QSerialPort>> m_serialPorts;
    std::vector<std::shared_ptr<QCamera>> m_cameras;
    std::shared_ptr<Joystick> m_joystick;
};

#endif // DEVICEMANAGER_H

