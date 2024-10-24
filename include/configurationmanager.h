   // configurationmanager.h
#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>

class ConfigurationManager : public QObject {
    Q_OBJECT
public:
    // Singleton access method
    static ConfigurationManager& instance() {
        static ConfigurationManager instance;
        return instance;
    }

    // Access the QSettings object
    QSettings* settings() const { return m_settings; }

    // Example getters for specific configurations
    QString modbusPortName() const { return m_settings->value("Modbus/PortName", "COM3").toString(); }
    int modbusBaudRate() const { return m_settings->value("Modbus/BaudRate", 9600).toInt(); }
    QString videoDevice() const { return m_settings->value("Video/Device", "/dev/video0").toString(); }
    // Add more getters as needed

private:
    // Private constructor for Singleton pattern
    explicit ConfigurationManager(QObject *parent = nullptr)
        : QObject(parent),
          m_settings(new QSettings("config.ini", QSettings::IniFormat, this)) {}

    // Delete copy constructor and assignment operator
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    QSettings* m_settings;
};

#endif // CONFIGURATIONMANAGER_H

