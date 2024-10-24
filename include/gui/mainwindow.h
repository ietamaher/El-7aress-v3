#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include "include/devicemanager.h"



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

    void on_detBtn_clicked();

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
private:
    Ui::MainWindow *ui;

    StateManager *m_stateManager;
    JoystickHandler *m_joystickHandler;
    CameraSystem *m_cameraSystem;
    SensorSystem *m_sensorSystem;

    VideoGLWidget_gl *m_videoWidget;
    QMap<int, bool> m_buttonStates;
    bool m_manualGimbalControlEnabled;

    QTimer *updateTimer;
    QSet<int> pendingTrackIds;
    bool updatePending = false;


    void initializeComponents();
    void connectSignals();

    // Helper functions
    void emergencyStop();
    void activateAutoTracking();
    void displaySystemStatus();
    void onSelectedTrackLost(int trackId);
    void onTrackedIdsUpdated(const QSet<int>& trackIds);
    void processPendingUpdates();
    int findItemIndexByData(QListWidget* listWidget, int data) const;

};

#endif // MAINWINDOW_H
