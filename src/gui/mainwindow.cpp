#include "include/gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/states/statemanager.h"
#include "include/comm/joystickhandler.h"
#include "include/gimbal/gimbalcontroller.h"
#include "include/weapon/weaponsystem.h"
#include "include/sensor/sensorsystem.h"
#include "include/camera/camerasystem.h"
#include "include/comm/communicationsystem.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_stateManager(new StateManager(this)),
    m_joystickHandler(new JoystickHandler("/dev/input/js0", this)),
    m_manualGimbalControlEnabled(false),
    m_cameraSystem(new CameraSystem(this))
{
    ui->setupUi(this);


    // Create the shared ModbusCommunication instance
    PLCModbusCommunication *plcModbusComm = new PLCModbusCommunication("/dev/pts/12", 115200, this);

    // Connect to the PLC
    if (!plcModbusComm->connectDevice()) {
        qCritical() << "Failed to connect to PLC via Modbus.";
        // Handle the error appropriately
    }

    // Create interfaces using the shared ModbusCommunication instance
    PLCServoInterface *plcServoInterface = new PLCServoInterface(plcModbusComm, this);
    PLCSolenoidInterface *plcSolenoidInterface = new PLCSolenoidInterface(plcModbusComm, this);
    PLCSensorInterface *plcSensorInterface = new PLCSensorInterface(plcModbusComm, this);

    // Create system instances
    GimbalController *gimbalController = new GimbalController(this);
    WeaponSystem *weaponSystem = new WeaponSystem(this);
    m_sensorSystem = new SensorSystem(this);

    // Set interfaces in systems
    gimbalController->setPLCServoInterface(plcServoInterface);
    weaponSystem->setPLCSolenoidInterface(plcSolenoidInterface);
    m_sensorSystem->setPLCSensorInterface(plcSensorInterface);

    // Start monitoring sensors
    m_sensorSystem->startMonitoringSensors();

    // Arm weapon and start firing at 10 Hz
    weaponSystem->startFiring(10);
    initializeComponents();
    connectSignals();
}

MainWindow::~MainWindow() {
    delete ui;
    // Other members will be deleted automatically as they have 'this' as parent
}

void MainWindow::initializeComponents() {
    GimbalController *gimbalController = new GimbalController(this);
    WeaponSystem *weaponSystem = new WeaponSystem(this);

    CommunicationSystem *communicationSystem = new CommunicationSystem(this);
    // Initialize SensorSystem
   // m_sensorSystem = new SensorSystem(this);

    m_stateManager->setSensorSystem(m_sensorSystem);
    // Use the member variable m_cameraSystem
    m_stateManager->setGimbalController(gimbalController);
    m_stateManager->setCameraSystem(m_cameraSystem);
    m_stateManager->setWeaponSystem(weaponSystem);

    m_stateManager->setCommunicationSystem(communicationSystem);

    m_cameraSystem->setDisplayWidget(ui->m_videowidget);


    // Set font and font size
    QFont listFont("Arial", 13);
    ui->trackIdListWidget->setFont(listFont);

    // Set text color and background color with semi-transparency using Stylesheets
    ui->trackIdListWidget->setStyleSheet(
        "QListWidget { background-color: rgba(128, 128, 128, 170); }" // Light gray with 50% opacity
        "QListWidget::item { color: rgba(150, 0, 0, 255); }" // Dark blue text color
        );
    //ui->trackIdListWidget->hide();
    ui->trackIdListWidget->clear();
    // Optionally, set selection behavior and mode
    ui->trackIdListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->trackIdListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->trackIdListWidget, &QListWidget::currentItemChanged, this, &MainWindow::onTrackIdSelected);
    updateTimer = new QTimer(this);
    updateTimer->setInterval(500); // Update every 500ms
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::processPendingUpdates);
    updateTimer->start();
}

void MainWindow::connectSignals() {
    connect(m_joystickHandler, &JoystickHandler::axisMoved, this, &MainWindow::onJoystickAxisMoved);
    connect(m_joystickHandler, &JoystickHandler::buttonPressed, this, &MainWindow::onJoystickButtonPressed);

    connect(m_stateManager, &StateManager::modeChanged, this, &MainWindow::onModeChanged);

    connect(m_cameraSystem, &CameraSystem::trackedIdsUpdated, this, &MainWindow::onTrackedIdsUpdated, Qt::QueuedConnection);
    connect(m_cameraSystem, &CameraSystem::selectedTrackLost, this, &MainWindow::onSelectedTrackLost);

    // Connect SensorSystem signals to MainWindow slots
    connect(m_sensorSystem, &SensorSystem::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(m_sensorSystem, &SensorSystem::frequencySet, this, &MainWindow::onFrequencySet);
    connect(m_sensorSystem, &SensorSystem::settingValueReceived, this, &MainWindow::onSettingValueReceived);
    connect(m_sensorSystem, &SensorSystem::laserCountReceived, this, &MainWindow::onLaserCountReceived);
    connect(m_sensorSystem, &SensorSystem::selfCheckResult, this, &MainWindow::onSelfCheckResult);
    connect(m_sensorSystem, &SensorSystem::rangingDataReceived, this, &MainWindow::onRangingDataReceived);

    // Connect UI buttons to MainWindow slots
    connect(ui->btnSelfCheck, &QPushButton::clicked, this, &MainWindow::sendSelfCheck);
    connect(ui->btnSingleRanging, &QPushButton::clicked, this, &MainWindow::sendSingleRanging);
    connect(ui->btnContinuousRanging, &QPushButton::clicked, this, &MainWindow::sendContinuousRanging);
    connect(ui->btnStopRanging, &QPushButton::clicked, this, &MainWindow::stopRanging);
    connect(ui->btnSetFrequency, &QPushButton::clicked, this, &MainWindow::setFrequency);
    connect(ui->btnQuerySettingValue, &QPushButton::clicked, this, &MainWindow::querySettingValue);
    connect(ui->btnQueryLaserCount, &QPushButton::clicked, this, &MainWindow::queryAccumulatedLaserCount);

}

void MainWindow::onJoystickAxisMoved(int axis, int value) {
    float normalizedValue = value / 32767.0f;

    const int DEAD_ZONE = 8000;
    if (abs(value) < DEAD_ZONE) {
        normalizedValue = 0.0f;
    }

    if (m_manualGimbalControlEnabled) {
        GimbalController *gimbalController = m_stateManager->getGimbalController();
        /*if (gimbalController) {
            gimbalController->onAxisMoved(axis, normalizedValue);
        }*/
    } else {
        // Handle axis inputs for other purposes
    }
}

void MainWindow::onJoystickButtonPressed(int button, bool pressed) {
    m_buttonStates[button] = pressed;

    if (pressed) {
        switch (button) {
            // Operational Mode Switching (TMS Hat Switch)
            case 15: m_stateManager->setMode(OperationalMode::Surveillance); break;
            case 16: m_stateManager->setMode(OperationalMode::Engagement); break;
            case 17: m_stateManager->setMode(OperationalMode::Detection); break;
            case 18: m_stateManager->setMode(OperationalMode::Tracking); break;
            case 19: m_stateManager->setMode(OperationalMode::Idle); break;

            // Camera Controls (DMS Hat Switch)
            case 20: m_stateManager->getCameraSystem()->zoomIn(); break;
            case 21: m_stateManager->getCameraSystem()->zoomOut(); break;
            case 22: m_stateManager->getCameraSystem()->toggleDayNightMode(); break;
            case 23: m_stateManager->getCameraSystem()->switchCameraMode(); break;
            case 24: m_stateManager->getCameraSystem()->resetZoom(); break;
            // Camera Processing Mode Switching (assign appropriate buttons)
            /*case 25: // Assuming button 25 is for MODE_NONE
                m_stateManager->getCameraSystem()->setProcessingMode(MODE_NONE);
                break;
            case 26: // Assuming button 26 is for MODE_DETECTION
                m_stateManager->getCameraSystem()->setProcessingMode(MODE_DETECTION);
                break;
            case 27: // Assuming button 27 is for MODE_TRACKING
                m_stateManager->getCameraSystem()->setProcessingMode(MODE_TRACKING);
                break;
            case 28: // Assuming button 28 is for MODE_MANUAL_TRACKING
                m_stateManager->getCameraSystem()->setProcessingMode(MODE_MANUAL_TRACKING);
                break;*/


            // LRF and Stabilization Controls (CMS Hat Switch)
            case 10: m_stateManager->getSensorSystem()->activateLRF(); break;
            case 11: m_stateManager->getSensorSystem()->deactivateLRF(); break;
            case 12: m_stateManager->getSensorSystem()->enableStabilization(); break;
            case 13: m_stateManager->getSensorSystem()->disableStabilization(); break;
            case 14: displaySystemStatus(); break;

            // Gimbal Control Toggle (Button 4)
            case 4:
                m_manualGimbalControlEnabled = !m_manualGimbalControlEnabled;
                m_stateManager->getGimbalController()->enableManualControl(m_manualGimbalControlEnabled);
                break;

            // Fire Weapon (Triggers)
            case 0: m_stateManager->getWeaponSystem()->prepareToFire(); break;
            case 6: m_stateManager->getWeaponSystem()->fire(); break;

            // Emergency Stop (Button 9)
            case 9: emergencyStop(); break;

            // Auto Tracking Activation (Button 8)
            case 8: activateAutoTracking(); break;

            // Communication Functions (Mic Switch)
            case 27: m_stateManager->getCommunicationSystem()->increaseVolume(); break;
            case 28: m_stateManager->getCommunicationSystem()->decreaseVolume(); break;
            case 29: m_stateManager->getCommunicationSystem()->toggleMute(); break;
            case 30: m_stateManager->getCommunicationSystem()->selectChannel(1); break; // Example channel
            case 31: m_stateManager->getCommunicationSystem()->openCommunicationPanel(); break;

            default:
                qDebug() << "Button" << button << "pressed";
                break;
        }
    } else {
        // Handle button release if needed
    }
}

void MainWindow::onModeChanged(OperationalMode newMode) {
    qDebug() << "Operational Mode changed to" << static_cast<int>(newMode);
    // Update UI or perform other actions
}

void MainWindow::emergencyStop() {
    m_manualGimbalControlEnabled = false;
    m_stateManager->getGimbalController()->enable(false);
    m_stateManager->getWeaponSystem()->cancelFire();
    m_stateManager->getSensorSystem()->activateSensors(false);
    m_stateManager->setMode(OperationalMode::Idle);
    qDebug() << "Emergency stop activated. All systems halted.";
}

void MainWindow::activateAutoTracking() {
    // Implement auto tracking activation
}

void MainWindow::displaySystemStatus() {
    // Implement system status display
}

void MainWindow::onSelectedTrackLost(int trackId)
{
    QMessageBox::information(this, "Track Lost", QString("Selected object ID %1 is no longer being tracked.").arg(trackId));

    // Reset the selection in the QListWidget
    ui->trackIdListWidget->clearSelection(); // Or use setCurrentItem(nullptr)

    // Notify the camera pipeline of the deselection
    m_cameraSystem->setSelectedTrackId(-1);
}


void MainWindow::onTrackedIdsUpdated(const QSet<int>& trackIds)
{
    pendingTrackIds = trackIds;
    updatePending = true;
}

void MainWindow::processPendingUpdates()
{
    if (updatePending)
    {
        // Get the currently selected track ID
        QListWidgetItem* currentItem = ui->trackIdListWidget->currentItem();
        int currentTrackId = currentItem ? currentItem->data(Qt::UserRole).toInt() : -1;

        // Build a set of existing track IDs for quick lookup
        QSet<int> existingTrackIds;
        for (int i = 0; i < ui->trackIdListWidget->count(); ++i)
        {
            QListWidgetItem* item = ui->trackIdListWidget->item(i);
            if (item) {
                int id = item->data(Qt::UserRole).toInt();
                existingTrackIds.insert(id);
            }
        }

        // Add new track IDs
        for (int id : pendingTrackIds)
        {
            if (!existingTrackIds.contains(id))
            {
                QListWidgetItem* newItem = new QListWidgetItem(QString::number(id));
                newItem->setData(Qt::UserRole, id); // Store the track ID
                ui->trackIdListWidget->addItem(newItem);
            }
        }

        // Remove track IDs that no longer exist
        for (int i = ui->trackIdListWidget->count() - 1; i >= 0; --i)
        {
            QListWidgetItem* item = ui->trackIdListWidget->item(i);
            if (item)
            {
                int id = item->data(Qt::UserRole).toInt();
                if (!pendingTrackIds.contains(id))
                {
                    delete ui->trackIdListWidget->takeItem(i); // Properly delete the item to avoid memory leaks
                }
            }
        }

        // Restore previous selection if still valid
        int index = findItemIndexByData(ui->trackIdListWidget, currentTrackId);
        if (index != -1)
        {
            ui->trackIdListWidget->setCurrentRow(index);
        }
        else
        {
            // If previous selection is no longer valid, clear the selection
            ui->trackIdListWidget->clearSelection();
            m_cameraSystem->setSelectedTrackId(-1);
        }

        updatePending = false;
    }
}


void MainWindow::onTrackIdSelected(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous); // Avoid compiler warnings if 'previous' is unused

    if (current)
    {
        int trackId = current->data(Qt::UserRole).toInt();
        m_cameraSystem->setSelectedTrackId(trackId);
    }
    else
    {
        // No selection
        m_cameraSystem->setSelectedTrackId(-1);
    }
}


int MainWindow::findItemIndexByData(QListWidget* listWidget, int data) const
{
    for (int i = 0; i < listWidget->count(); ++i)
    {
        QListWidgetItem* item = listWidget->item(i);
        if (item && item->data(Qt::UserRole).toInt() == data)
        {
            return i;
        }
    }
    return -1; // Not found
}



void MainWindow::onErrorOccurred(const QString &error)
{
    // Display the error in the status bar and optionally as a message box
    qDebug() << "Error:" << error;
    //ui->statusBar->showMessage(error, 5000); // Show for 5 seconds
    QMessageBox::warning(this, "LRF Error", error);
}

void MainWindow::onFrequencySet(quint8 frequency, quint8 majorVersion, quint8 secondaryVersion, quint8 maintenanceVersion)
{
    // Update UI labels with frequency and version information
    qDebug() << "Frequency set to:" << frequency << "Hz";
    qDebug() << "Version:" << majorVersion << "." << secondaryVersion << "." << maintenanceVersion;

    ui->lblFrequency->setText(QString::number(frequency) + " Hz");
    ui->lblVersion->setText(QString::number(majorVersion) + "." +
                            QString::number(secondaryVersion) + "." +
                            QString::number(maintenanceVersion));
}

void MainWindow::onSettingValueReceived(quint8 value)
{
    // Update UI with current frequency setting
    qDebug() << "Current Frequency Setting:" << value << "Hz";
    ui->lblCurrentFrequency->setText(QString::number(value) + " Hz");
}

void MainWindow::onLaserCountReceived(quint32 count)
{
    // Update UI with cumulative laser shot count
    qDebug() << "Cumulative Laser Shot Count:" << count;
    ui->lblLaserCount->setText(QString::number(count));
}

void MainWindow::onSelfCheckResult(quint8 systemStatus, quint8 temperatureAlarm, quint8 biasVoltageFault, quint8 counterMalfunction)
{
    // Update UI with self-check results
    qDebug() << "Self-Check Results:";
    QString statusText = (systemStatus ? "Abnormal" : "Normal");
    QString tempAlarmText = (temperatureAlarm ? "Alarm" : "Normal");
    QString biasFaultText = (biasVoltageFault ? "Fault" : "Normal");
    QString counterFaultText = (counterMalfunction ? "Fault" : "Normal");

    ui->lblSystemStatus->setText(statusText);
    ui->lblTemperatureAlarm->setText(tempAlarmText);
    ui->lblBiasVoltageFault->setText(biasFaultText);
    ui->lblCounterMalfunction->setText(counterFaultText);
}

void MainWindow::onRangingDataReceived(quint8 status, quint16 distance, quint8 decimalPlaces, quint8 echoStatus)
{
    // Update UI with ranging data
    qDebug() << "Ranging Data Received:";
    qDebug() << "Status:" << status;
    qDebug() << "Distance:" << distance << "." << decimalPlaces << "cm";
    qDebug() << "Echo Status:" << echoStatus;

    // Convert distance to meters with decimal places
    double distanceMeters = distance / 100.0 + decimalPlaces / 10000.0;
    ui->lblDistance->setText(QString::number(distanceMeters, 'f', 2) + " m");

    // Update echo status
    ui->lblEchoStatus->setText(echoStatus ? "With Echo" : "No Echo");

    // Interpret status bits if necessary
}

//////////////////////////
/// Command Sending Slots
//////////////////////////

void MainWindow::sendSelfCheck()
{
    qDebug() << "Sending Self-Check Command.";
    m_sensorSystem->sendSelfCheck();
}

void MainWindow::sendSingleRanging()
{
    qDebug() << "Sending Single Ranging Command.";
    m_sensorSystem->sendSingleRanging();
}

void MainWindow::sendContinuousRanging()
{
    qDebug() << "Sending Continuous Ranging Command.";
    m_sensorSystem->sendContinuousRanging();
}

void MainWindow::stopRanging()
{
    qDebug() << "Sending Stop Ranging Command.";
    m_sensorSystem->stopRanging();
}

void MainWindow::setFrequency()
{
    // Retrieve frequency value from the spin box
    int frequency = ui->spinFrequency->value(); // Ensure the spin box has objectName "spinFrequency"

    // Validate frequency (1-5 Hz)
    if (frequency < 1 || frequency > 5) {
        QMessageBox::warning(this, "Invalid Frequency", "Frequency must be between 1 and 5 Hz.");
        return;
    }

    qDebug() << "Setting Frequency to:" << frequency << "Hz.";
    m_sensorSystem->setFrequency(frequency);
}

void MainWindow::querySettingValue()
{
    qDebug() << "Sending Query Setting Value Command.";
    m_sensorSystem->querySettingValue();
}

void MainWindow::queryAccumulatedLaserCount()
{
    qDebug() << "Sending Query Accumulated Laser Count Command.";
    m_sensorSystem->queryAccumulatedLaserCount();
}


void MainWindow::on_idleBtn_clicked()
{
    m_stateManager->setMode(OperationalMode::Idle);
}

void MainWindow::on_survBtn_clicked()
{
    m_stateManager->setMode(OperationalMode::Surveillance);
}

void MainWindow::on_engageBtn_clicked()
{
    m_stateManager->setMode(OperationalMode::Engagement);
}

void MainWindow::on_detBtn_clicked()
{
    m_stateManager->setMode(OperationalMode::Detection);
}

void MainWindow::on_trckBtn_clicked()
{
    m_stateManager->setMode(OperationalMode::Tracking);
}
