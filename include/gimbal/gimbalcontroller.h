#ifndef GIMBALCONTROLLER_H
#define GIMBALCONTROLLER_H

#include <QObject>
#include "../states/operationalmode.h"
#include "gimbalmotionmode.h"
#include "motionmodetype.h"


//#include "gimbalmotordriver.h"
#include "mduinocontroller.h"
#include "../sensor/sensorsystem.h"
#include "../camera/camerasystem.h"
#include "plcservointerface.h"
#include "servodriverinterface.h"
#include "include/datamodel.h"

//#include "include/comm/joystickhandler.h"


#define MODE_SWITCH_BUTTON_ID 333
#define STABILIZATION_TOGGLE_BUTTON_ID 444
//#define PGIE_CLASS_ID_PERSON 0

class GimbalController : public QObject {
    Q_OBJECT
public:
    explicit GimbalController(DataModel *dataModel, QObject *parent = nullptr);
    ~GimbalController();


    void handleJoystickInput(int axis, float value);
    void update(); // Called periodically (e.g., via QTimer)

    void setMotionMode(MotionModeType modeType); // Change parameter type
    MotionModeType getCurrentMotionMode() const; // Add getter
    // Accessors
    //GimbalMotorDriver* getGimbalMotorDriver() const;
    SensorSystem* getSensorSystem() const;
    void setSensorSystem(SensorSystem* sensorSystem);
    CameraSystem* getCameraSystem() const;
    void setCameraSystem(CameraSystem* cameraSystem);
    void setPLCServoInterface(PLCServoInterface *servoInterface);

    void shutdown();

    void setPanSpeed(float speed);
    void setTiltSpeed(float speed);

    void enable(bool enable);
    void enableManualControl(bool enable);
    void startAutoScan();
    void stopAutoScan();
    void startDetectionScan();
    void stopDetectionScan();
    void enableAutoTracking(bool enable);
    void handleJoystickButtonPressed(int buttonId);

    void setStabilizationEnabled(bool enabled);
    bool isStabilizationEnabled() const;
    // Initialization
    bool initialize();

    // Command methods
    void sendPositionCommand(double azimuth, double elevation);
    void sendSpeedCommand(double azimuthSpeed, double elevationSpeed);

    // Accessors for current positions
    double getAzimuthPosition() const;
    double getElevationPosition() const;

    DataModel* getDataModel() const { return m_dataModel; }

public slots:
    //void onAxisMoved(int axis, float normalizedValue);
    void onModeChanged(OperationalMode mode);
    void onAzimuthDataUpdated(const QVector<uint16_t> &data);
    void onElevationDataUpdated(const QVector<uint16_t> &data);

    void handleAzimuthConnectionStatusChanged(bool connected);
    void handleElevationConnectionStatusChanged(bool connected);

signals:
    void positionUpdated(double azimuth, double elevation);

    void azimuthConnectionStatusChanged(bool connected);
    void elevationConnectionStatusChanged(bool connected);
    void motionModeChangeRequested(MotionModeType modeType);

    void stepperMotorStatusChanged(const QString &motorName, bool connected);
    void azimuthDataUpdated(const QVector<uint16_t> &data);
    void elevationDataUpdated(const QVector<uint16_t> &data);
    void logMessage(const QString &message);


private:
    bool m_enabled;
    bool m_manualControlEnabled;
    OperationalMode m_currentOpsMode;
    std::unique_ptr<GimbalMotionMode> m_currentMotionMode; // Use smart pointer

   // GimbalMotionMode* m_currentMotionMode;
    //GimbalMotorDriver* m_gimbalMotorDriver;
    SensorSystem* m_sensorSystem;
    CameraSystem* m_cameraSystem;
    PLCServoInterface* m_plcServoInterface;
    //JoystickHandler *m_joystickHandler;
    MotionModeType m_currentMotionModeType;
    bool m_stabilizationEnabled;
    ServoDriverInterface *m_azimuthServoDriver;
    ServoDriverInterface *m_elevationServoDriver;

    double m_azimuthPosition;
    double m_elevationPosition;
     // Current positions
    double m_azimuth;
    double m_elevation;
    DataModel *m_dataModel;

    float m_panSpeed;
    float m_tiltSpeed;

    // Feedback update method
    void readFeedback();
};

#endif // GIMBALCONTROLLER_H

