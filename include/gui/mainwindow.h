#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "include/states/statemanager.h"
#include "include/comm/joystickhandler.h"
#include <QMap>
#include "videoglwidget_gl.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>

#include <QTimer>
#include <QListWidget>

#include "../../include/gui/statuspanel.h"
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GimbalController;
class CameraSystem;
class WeaponSystem;
class SensorSystem;
class CommunicationSystem;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onJoystickAxisMoved(int axis, int value);
    void onJoystickButtonPressed(int button, bool pressed);
    void onModeChanged(OperationalMode newMode);

    void onTrackIdSelected(QListWidgetItem* current, QListWidgetItem* previous);
    //void onSelectedTrackLost(int trackId);

    void on_idleBtn_clicked();

    void on_survBtn_clicked();

    void on_engageBtn_clicked();


    void on_trckBtn_clicked();
    // Slots to handle signals from SensorSystem
    void onErrorOccurred(const QString &error);
    void onFrequencySet(quint8 frequency, quint8 majorVersion, quint8 secondaryVersion, quint8 maintenanceVersion);
    void onSettingValueReceived(quint8 value);
    void onLaserCountReceived(quint32 count);
    void onSelfCheckResult(quint8 systemStatus, quint8 temperatureAlarm, quint8 biasVoltageFault, quint8 counterMalfunction);
    void onRangingDataReceived(quint8 status, quint16 distance, quint8 decimalPlaces, quint8 echoStatus);

    // Slots to send commands to SensorSystem
    void sendSelfCheck();
    void sendSingleRanging();
    void sendContinuousRanging();
    void stopRanging();
    void setFrequency();
    void querySettingValue();
    void queryAccumulatedLaserCount();

    // Slots for System Status

    void onLRFStatusChanged(bool connected);
    void onRadarStatusChanged(bool connected);
    void onGyroStatusChanged(bool connected);
    void onPLC1StatusChanged(bool connected);
    void onAZStepperMotorStatusChanged(bool connected);
    void onELStepperMotorStatusChanged(bool connected);
    void onActuatorStatusChanged(bool connected);

    void on_switchMotionModeButton_clicked();

    void on_trackButton_clicked();

    void on_engageButton_clicked();

    void on_cancelTrackingButton_clicked();

    void on_detectionToggleButton_clicked();

    void on_stabToggleButton_clicked();

private:
    Ui::MainWindow *ui;

    StateManager *m_stateManager;
    JoystickHandler *m_joystickHandler;
    CameraSystem *m_cameraSystem;
    GimbalController *m_gimbalController;
    WeaponSystem *m_weaponSystem;
    SensorSystem *m_sensorSystem;

    PLCModbusWorker *m_modbusWorker;
    QThread *m_modbusThread;

    PLCServoInterface *m_plcServoInterface;
    PLCSolenoidInterface *m_plcSolenoidInterface;
    PLCSensorInterface *m_plcSensorInterface;



    VideoGLWidget_gl *m_videoWidget;
    QMap<int, bool> m_buttonStates;
    bool m_manualGimbalControlEnabled;

    QTimer *updateTimer;
    QTimer *statusTimer;
    QSet<int> pendingTrackIds;
    bool updatePending = false;

    bool detectionEnabled = false;
    bool stabilizationEnabled = false;

    void initializeComponents();
    void connectSignals();
    void startThread();

    // Helper functions
    void emergencyStop();
    void activateAutoTracking();
    void displaySystemStatus();
    void onSelectedTrackLost(int trackId);
    void onTrackedIdsUpdated(const QSet<int>& trackIds);
    void processPendingUpdates();
    int findItemIndexByData(QListWidget* listWidget, int data) const;
    // Map to hold labels for each component
 StatusPanel *m_statusPanel;
    bool isCameraAvailable(const QString &devicePath);
 bool isJoystickConnected();
 void checkCameraStatus();
 void checkSystemStatus();
 void checkJoystickStatus();
};

#endif // MAINWINDOW_H
