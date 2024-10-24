#ifndef GIMBALCONTROLLER_H
#define GIMBALCONTROLLER_H

#include <QObject>
#include "../states/operationalmode.h"
#include "gimbalmotionmode.h"
#include "gimbalmotordriver.h"
#include "mduinocontroller.h"
#include "../sensor/sensorsystem.h"
#include "../camera/camerasystem.h"
#include "plcservointerface.h"

class GimbalController : public QObject {
    Q_OBJECT
public:
    explicit GimbalController(QObject *parent = nullptr);
    ~GimbalController();


    void setMotionMode(GimbalMotionMode* mode);
    void handleJoystickInput(int axis, float value);
    void update(); // Called periodically (e.g., via QTimer)


    // Accessors
    GimbalMotorDriver* getGimbalMotorDriver() const;
    SensorSystem* getSensorSystem() const;
    void setSensorSystem(SensorSystem* sensorSystem);
    CameraSystem* getCameraSystem() const;
    void setCameraSystem(CameraSystem* cameraSystem);
    void setPLCServoInterface(PLCServoInterface *servoInterface);


    void setPanSpeed(float speed);
    void setTiltSpeed(float speed);

    void enable(bool enable);
    void enableManualControl(bool enable);
    void startAutoScan();
    void stopAutoScan();
    void startDetectionScan();
    void stopDetectionScan();
    void enableAutoTracking(bool enable);



public slots:
    //void onAxisMoved(int axis, float normalizedValue);
    void onModeChanged(OperationalMode mode);
    void onAzimuthDataUpdated(double position, double speed, double torque, double motorTemp, double driverTemp);
    void onElevationDataUpdated(double position, double speed, double torque, double motorTemp, double driverTemp);

signals:
    void positionUpdated(double azimuth, double elevation);

private:
    bool m_enabled;
    bool m_manualControlEnabled;
    OperationalMode m_currentOpsMode;

    GimbalMotionMode* m_currentMotionMode;
    GimbalMotorDriver* m_gimbalMotorDriver;
    SensorSystem* m_sensorSystem;
    CameraSystem* m_cameraSystem;
    PLCServoInterface* m_plcServoInterface;

    // Current positions
    double m_azimuth;
    double m_elevation;

    // Feedback update method
    void readFeedback();
};

#endif // GIMBALCONTROLLER_H

