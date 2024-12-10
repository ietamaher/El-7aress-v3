/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <include/gui/statuspanel.h>
#include <include/gui/videoglwidget_gl.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *survBtn;
    QPushButton *trckBtn;
    QPushButton *engageBtn;
    VideoGLWidget_gl *m_videowidget;
    QListWidget *trackIdListWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *lblTemperatureAlarm;
    QPushButton *btnSelfCheck;
    QLabel *lblBiasVoltageFault;
    QLabel *lblSystemStatus;
    QLabel *lblVersion;
    QLabel *lblDistance;
    QLabel *lblCounterMalfunction;
    QPushButton *btnSetFrequency;
    QLabel *lblCurrentFrequency;
    QPushButton *btnQuerySettingValue;
    QLabel *lblEchoStatus;
    QPushButton *btnContinuousRanging;
    QLabel *lblFrequency;
    QPushButton *btnSingleRanging;
    QPushButton *btnQueryLaserCount;
    QPushButton *btnStopRanging;
    QSpinBox *spinFrequency;
    QLabel *lblLaserCount;
    StatusPanel *systemStatusWidget;
    QPushButton *idleBtn;
    QPushButton *switchMotionModeButton;
    QLabel *currentMotionModeLabel;
    QPushButton *trackButton;
    QPushButton *engageButton;
    QPushButton *cancelTrackingButton;
    QPushButton *detectionToggleButton;
    QPushButton *stabToggleButton;
    QLabel *lblGimbalSpeed;
    QPushButton *FireButton;
    QSlider *elevationSlider;
    QSlider *azimuthSlider;
    QLabel *elevationValueLabel;
    QLabel *azimuthValueLabel;
    QWidget *_widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1492, 795);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        survBtn = new QPushButton(centralwidget);
        survBtn->setObjectName("survBtn");
        survBtn->setGeometry(QRect(190, 0, 80, 23));
        trckBtn = new QPushButton(centralwidget);
        trckBtn->setObjectName("trckBtn");
        trckBtn->setGeometry(QRect(280, 0, 80, 23));
        engageBtn = new QPushButton(centralwidget);
        engageBtn->setObjectName("engageBtn");
        engageBtn->setGeometry(QRect(370, 0, 80, 23));
        m_videowidget = new VideoGLWidget_gl(centralwidget);
        m_videowidget->setObjectName("m_videowidget");
        m_videowidget->setGeometry(QRect(1030, 740, 231, 21));
        trackIdListWidget = new QListWidget(centralwidget);
        trackIdListWidget->setObjectName("trackIdListWidget");
        trackIdListWidget->setGeometry(QRect(20, 40, 131, 231));
        trackIdListWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 97, 203);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(180, 120, 89, 25));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(180, 90, 89, 25));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(170, 60, 89, 25));
        lblTemperatureAlarm = new QLabel(centralwidget);
        lblTemperatureAlarm->setObjectName("lblTemperatureAlarm");
        lblTemperatureAlarm->setGeometry(QRect(130, 500, 163, 16));
        btnSelfCheck = new QPushButton(centralwidget);
        btnSelfCheck->setObjectName("btnSelfCheck");
        btnSelfCheck->setGeometry(QRect(10, 470, 101, 30));
        btnSelfCheck->setAutoDefault(false);
        btnSelfCheck->setFlat(false);
        lblBiasVoltageFault = new QLabel(centralwidget);
        lblBiasVoltageFault->setObjectName("lblBiasVoltageFault");
        lblBiasVoltageFault->setGeometry(QRect(130, 520, 116, 16));
        lblSystemStatus = new QLabel(centralwidget);
        lblSystemStatus->setObjectName("lblSystemStatus");
        lblSystemStatus->setGeometry(QRect(130, 480, 163, 16));
        lblVersion = new QLabel(centralwidget);
        lblVersion->setObjectName("lblVersion");
        lblVersion->setGeometry(QRect(200, 410, 60, 16));
        lblDistance = new QLabel(centralwidget);
        lblDistance->setObjectName("lblDistance");
        lblDistance->setGeometry(QRect(200, 320, 67, 16));
        lblCounterMalfunction = new QLabel(centralwidget);
        lblCounterMalfunction->setObjectName("lblCounterMalfunction");
        lblCounterMalfunction->setGeometry(QRect(130, 540, 163, 16));
        btnSetFrequency = new QPushButton(centralwidget);
        btnSetFrequency->setObjectName("btnSetFrequency");
        btnSetFrequency->setGeometry(QRect(10, 370, 131, 30));
        btnSetFrequency->setAutoDefault(false);
        btnSetFrequency->setFlat(false);
        lblCurrentFrequency = new QLabel(centralwidget);
        lblCurrentFrequency->setObjectName("lblCurrentFrequency");
        lblCurrentFrequency->setGeometry(QRect(200, 390, 163, 16));
        btnQuerySettingValue = new QPushButton(centralwidget);
        btnQuerySettingValue->setObjectName("btnQuerySettingValue");
        btnQuerySettingValue->setGeometry(QRect(10, 400, 163, 30));
        btnQuerySettingValue->setAutoDefault(false);
        btnQuerySettingValue->setFlat(false);
        lblEchoStatus = new QLabel(centralwidget);
        lblEchoStatus->setObjectName("lblEchoStatus");
        lblEchoStatus->setGeometry(QRect(130, 560, 163, 16));
        btnContinuousRanging = new QPushButton(centralwidget);
        btnContinuousRanging->setObjectName("btnContinuousRanging");
        btnContinuousRanging->setGeometry(QRect(10, 310, 161, 30));
        btnContinuousRanging->setAutoDefault(false);
        btnContinuousRanging->setFlat(false);
        lblFrequency = new QLabel(centralwidget);
        lblFrequency->setObjectName("lblFrequency");
        lblFrequency->setGeometry(QRect(200, 370, 78, 16));
        btnSingleRanging = new QPushButton(centralwidget);
        btnSingleRanging->setObjectName("btnSingleRanging");
        btnSingleRanging->setGeometry(QRect(10, 280, 131, 30));
        btnSingleRanging->setAutoDefault(false);
        btnSingleRanging->setFlat(false);
        btnQueryLaserCount = new QPushButton(centralwidget);
        btnQueryLaserCount->setObjectName("btnQueryLaserCount");
        btnQueryLaserCount->setGeometry(QRect(10, 430, 163, 30));
        btnQueryLaserCount->setAutoDefault(false);
        btnQueryLaserCount->setFlat(false);
        btnStopRanging = new QPushButton(centralwidget);
        btnStopRanging->setObjectName("btnStopRanging");
        btnStopRanging->setGeometry(QRect(12, 340, 121, 30));
        btnStopRanging->setAutoDefault(false);
        btnStopRanging->setFlat(false);
        spinFrequency = new QSpinBox(centralwidget);
        spinFrequency->setObjectName("spinFrequency");
        spinFrequency->setEnabled(true);
        spinFrequency->setGeometry(QRect(140, 370, 51, 31));
        spinFrequency->setMinimum(1);
        spinFrequency->setMaximum(5);
        lblLaserCount = new QLabel(centralwidget);
        lblLaserCount->setObjectName("lblLaserCount");
        lblLaserCount->setGeometry(QRect(200, 440, 83, 16));
        systemStatusWidget = new StatusPanel(centralwidget);
        systemStatusWidget->setObjectName("systemStatusWidget");
        systemStatusWidget->setGeometry(QRect(280, 40, 241, 411));
        idleBtn = new QPushButton(centralwidget);
        idleBtn->setObjectName("idleBtn");
        idleBtn->setGeometry(QRect(100, 0, 89, 25));
        switchMotionModeButton = new QPushButton(centralwidget);
        switchMotionModeButton->setObjectName("switchMotionModeButton");
        switchMotionModeButton->setGeometry(QRect(180, 160, 101, 25));
        currentMotionModeLabel = new QLabel(centralwidget);
        currentMotionModeLabel->setObjectName("currentMotionModeLabel");
        currentMotionModeLabel->setGeometry(QRect(20, 720, 411, 17));
        trackButton = new QPushButton(centralwidget);
        trackButton->setObjectName("trackButton");
        trackButton->setGeometry(QRect(180, 210, 89, 25));
        engageButton = new QPushButton(centralwidget);
        engageButton->setObjectName("engageButton");
        engageButton->setGeometry(QRect(180, 250, 89, 25));
        cancelTrackingButton = new QPushButton(centralwidget);
        cancelTrackingButton->setObjectName("cancelTrackingButton");
        cancelTrackingButton->setGeometry(QRect(190, 280, 89, 25));
        detectionToggleButton = new QPushButton(centralwidget);
        detectionToggleButton->setObjectName("detectionToggleButton");
        detectionToggleButton->setGeometry(QRect(20, 630, 121, 25));
        stabToggleButton = new QPushButton(centralwidget);
        stabToggleButton->setObjectName("stabToggleButton");
        stabToggleButton->setGeometry(QRect(20, 660, 121, 25));
        lblGimbalSpeed = new QLabel(centralwidget);
        lblGimbalSpeed->setObjectName("lblGimbalSpeed");
        lblGimbalSpeed->setGeometry(QRect(160, 690, 111, 17));
        FireButton = new QPushButton(centralwidget);
        FireButton->setObjectName("FireButton");
        FireButton->setGeometry(QRect(160, 660, 89, 25));
        elevationSlider = new QSlider(centralwidget);
        elevationSlider->setObjectName("elevationSlider");
        elevationSlider->setGeometry(QRect(470, 650, 20, 101));
        elevationSlider->setMinimum(-1000);
        elevationSlider->setMaximum(1000);
        elevationSlider->setOrientation(Qt::Vertical);
        azimuthSlider = new QSlider(centralwidget);
        azimuthSlider->setObjectName("azimuthSlider");
        azimuthSlider->setGeometry(QRect(270, 730, 160, 16));
        azimuthSlider->setMinimum(-1000);
        azimuthSlider->setMaximum(1000);
        azimuthSlider->setOrientation(Qt::Horizontal);
        elevationValueLabel = new QLabel(centralwidget);
        elevationValueLabel->setObjectName("elevationValueLabel");
        elevationValueLabel->setGeometry(QRect(400, 690, 67, 17));
        azimuthValueLabel = new QLabel(centralwidget);
        azimuthValueLabel->setObjectName("azimuthValueLabel");
        azimuthValueLabel->setGeometry(QRect(290, 690, 67, 17));
        _widget = new QWidget(centralwidget);
        _widget->setObjectName("_widget");
        _widget->setGeometry(QRect(530, 10, 960, 720));
        MainWindow->setCentralWidget(centralwidget);
        _widget->raise();
        survBtn->raise();
        trckBtn->raise();
        engageBtn->raise();
        m_videowidget->raise();
        trackIdListWidget->raise();
        pushButton->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        lblTemperatureAlarm->raise();
        btnSelfCheck->raise();
        lblBiasVoltageFault->raise();
        lblSystemStatus->raise();
        lblVersion->raise();
        lblDistance->raise();
        lblCounterMalfunction->raise();
        btnSetFrequency->raise();
        lblCurrentFrequency->raise();
        btnQuerySettingValue->raise();
        lblEchoStatus->raise();
        btnContinuousRanging->raise();
        lblFrequency->raise();
        btnSingleRanging->raise();
        btnQueryLaserCount->raise();
        btnStopRanging->raise();
        spinFrequency->raise();
        lblLaserCount->raise();
        systemStatusWidget->raise();
        idleBtn->raise();
        switchMotionModeButton->raise();
        currentMotionModeLabel->raise();
        trackButton->raise();
        engageButton->raise();
        cancelTrackingButton->raise();
        detectionToggleButton->raise();
        stabToggleButton->raise();
        lblGimbalSpeed->raise();
        FireButton->raise();
        elevationSlider->raise();
        azimuthSlider->raise();
        elevationValueLabel->raise();
        azimuthValueLabel->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1492, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        btnSelfCheck->setDefault(false);
        btnSetFrequency->setDefault(false);
        btnQuerySettingValue->setDefault(false);
        btnContinuousRanging->setDefault(false);
        btnSingleRanging->setDefault(false);
        btnQueryLaserCount->setDefault(false);
        btnStopRanging->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        survBtn->setText(QCoreApplication::translate("MainWindow", "Surveillance", nullptr));
        trckBtn->setText(QCoreApplication::translate("MainWindow", "Tracking", nullptr));
        engageBtn->setText(QCoreApplication::translate("MainWindow", "Engagment", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        lblTemperatureAlarm->setText(QCoreApplication::translate("MainWindow", "lblTemperatureAlarm", nullptr));
        btnSelfCheck->setText(QCoreApplication::translate("MainWindow", "btnSelfCheck", nullptr));
        lblBiasVoltageFault->setText(QCoreApplication::translate("MainWindow", "lblBiasVoltageFault", nullptr));
        lblSystemStatus->setText(QCoreApplication::translate("MainWindow", "lblSystemStatus", nullptr));
        lblVersion->setText(QCoreApplication::translate("MainWindow", "lblVersion", nullptr));
        lblDistance->setText(QCoreApplication::translate("MainWindow", "lblDistance", nullptr));
        lblCounterMalfunction->setText(QCoreApplication::translate("MainWindow", "lblCounterMalfunction", nullptr));
        btnSetFrequency->setText(QCoreApplication::translate("MainWindow", "btnSetFrequency", nullptr));
        lblCurrentFrequency->setText(QCoreApplication::translate("MainWindow", "lblCurrentFrequency", nullptr));
        btnQuerySettingValue->setText(QCoreApplication::translate("MainWindow", "btnQuerySettingValue", nullptr));
        lblEchoStatus->setText(QCoreApplication::translate("MainWindow", "lblEchoStatus", nullptr));
        btnContinuousRanging->setText(QCoreApplication::translate("MainWindow", "btnContinuousRanging", nullptr));
        lblFrequency->setText(QCoreApplication::translate("MainWindow", "lblFrequency", nullptr));
        btnSingleRanging->setText(QCoreApplication::translate("MainWindow", "btnSingleRanging", nullptr));
        btnQueryLaserCount->setText(QCoreApplication::translate("MainWindow", "btnQueryLaserCount", nullptr));
        btnStopRanging->setText(QCoreApplication::translate("MainWindow", "btnStopRanging", nullptr));
        lblLaserCount->setText(QCoreApplication::translate("MainWindow", "lblLaserCount", nullptr));
        idleBtn->setText(QCoreApplication::translate("MainWindow", "Idle", nullptr));
        switchMotionModeButton->setText(QCoreApplication::translate("MainWindow", " Motion mode ", nullptr));
        currentMotionModeLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        trackButton->setText(QCoreApplication::translate("MainWindow", "Track", nullptr));
        engageButton->setText(QCoreApplication::translate("MainWindow", "Engage ", nullptr));
        cancelTrackingButton->setText(QCoreApplication::translate("MainWindow", "cancel Track", nullptr));
        detectionToggleButton->setText(QCoreApplication::translate("MainWindow", "detectionToggle", nullptr));
        stabToggleButton->setText(QCoreApplication::translate("MainWindow", "stabToggle", nullptr));
        lblGimbalSpeed->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        FireButton->setText(QCoreApplication::translate("MainWindow", "Fire", nullptr));
        elevationValueLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        azimuthValueLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
