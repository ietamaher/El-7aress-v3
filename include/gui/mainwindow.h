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
#include <QInputDialog>

#include "../../include/gui/statuspanel.h"
#include <QFile>
#include "include/datamodel.h"
#include "include/comm/plcstationdriver.h"
#include "include/gui/custommenudialog.h"
#include "include/camera/camerapipeline_day.h"


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
    void onOperationalStateModeChanged(const OperationalMode &mode);

    void onJoystickAxisMoved(int axis, int value);
    void onJoystickButtonPressed(int button, bool pressed);
    void onModeChanged(OperationalMode newMode);
    void onFireModeChanged(FireMode mode);
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

    void on_speedPlusButton_clicked();

    void on_speedMinusButton_clicked();

    void onUpSwChanged(bool state);
    void onDownSwChanged(bool state);
    void onMenuValSwChanged(bool state);

    void showIdleMenu();
    void handleMenuClosed() ;
    void showSystemStatus();
    void personalizeReticle();
    void adjustBrightness() ;
    void configureSettings() ;
    void viewLogs() ;
    void softwareUpdates();
    void runDiagnostics() ;
    void showHelpAbout();
    void handleMenuOptionSelected(const QString &option);
    void on_FireButton_pressed();

    void on_FireButton_released();

    void onElevationSliderValueChanged(int value);
    void onAzimuthSliderValueChanged(int value);
private:
    Ui::MainWindow *ui;
    DataModel *m_dataModel;
    StateManager *m_stateManager;
    JoystickHandler *m_joystickHandler;
    CameraSystem *m_cameraSystem;
    GimbalController *m_gimbalController;
    WeaponSystem *m_weaponSystem;
    SensorSystem *m_sensorSystem;

    PLCStationDriver *m_modbusWorker;
    QThread *m_modbusThread;

    PLCServoInterface *m_plcServoInterface;
    PLCSolenoidInterface *m_plcSolenoidInterface;
    PLCStationSensorInterface *m_plcStationSensorInterface;

    CustomMenuWidget *m_menuWidget = nullptr;
    bool m_menuActive = false;

    CustomMenuWidget *m_reticleMenuWidget = nullptr;
    bool m_reticleMenuActive = false;

    CustomMenuWidget *m_systemStatusWidget = nullptr;
    bool m_systemStatusActive = false;

    CustomMenuWidget *m_colorWidget = nullptr;
    bool m_colorMenuActive = false;

    CustomMenuWidget *m_settingsMenuWidget = nullptr;
    bool m_settingsMenuActive = false;

    CustomMenuWidget *m_aboutWidget = nullptr;
    bool m_aboutActive = false;

    VideoGLWidget_gl *m_videoWidget;
    QMap<int, bool> m_buttonStates;
    bool m_manualGimbalControlEnabled;

    QTimer *updateTimer;
    QTimer *statusTimer;
    QSet<int> pendingTrackIds;
    bool updatePending = false;



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
     bool m_detectionEnabled;
    bool m_stabilizationEnabled;
     double m_currentGimbalSpeed;
     QVector<double> m_speedValues;
     int m_speedIndex;
     bool m_previousfirestate = false;
     void updateGimbalSpeed();
};

#endif // MAINWINDOW_H
