/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/gui/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onOperationalStateModeChanged",
    "",
    "OperationalMode",
    "mode",
    "onJoystickAxisMoved",
    "axis",
    "value",
    "onJoystickButtonPressed",
    "button",
    "pressed",
    "onModeChanged",
    "newMode",
    "onFireModeChanged",
    "FireMode",
    "onTrackIdSelected",
    "QListWidgetItem*",
    "current",
    "previous",
    "on_idleBtn_clicked",
    "on_survBtn_clicked",
    "on_engageBtn_clicked",
    "on_trckBtn_clicked",
    "onErrorOccurred",
    "error",
    "onFrequencySet",
    "frequency",
    "majorVersion",
    "secondaryVersion",
    "maintenanceVersion",
    "onSettingValueReceived",
    "onLaserCountReceived",
    "count",
    "onSelfCheckResult",
    "systemStatus",
    "temperatureAlarm",
    "biasVoltageFault",
    "counterMalfunction",
    "onRangingDataReceived",
    "status",
    "distance",
    "decimalPlaces",
    "echoStatus",
    "sendSelfCheck",
    "sendSingleRanging",
    "sendContinuousRanging",
    "stopRanging",
    "setFrequency",
    "querySettingValue",
    "queryAccumulatedLaserCount",
    "onLRFStatusChanged",
    "connected",
    "onRadarStatusChanged",
    "onGyroStatusChanged",
    "onPLC1StatusChanged",
    "onAZStepperMotorStatusChanged",
    "onELStepperMotorStatusChanged",
    "onActuatorStatusChanged",
    "on_switchMotionModeButton_clicked",
    "on_trackButton_clicked",
    "on_engageButton_clicked",
    "on_cancelTrackingButton_clicked",
    "on_detectionToggleButton_clicked",
    "onUpSwChanged",
    "state",
    "onDownSwChanged",
    "onMenuValSwChanged",
    "showIdleMenu",
    "handleMenuClosed",
    "showSystemStatus",
    "personalizeReticle",
    "adjustBrightness",
    "configureSettings",
    "viewLogs",
    "softwareUpdates",
    "runDiagnostics",
    "showHelpAbout",
    "handleMenuOptionSelected",
    "option",
    "on_FireButton_pressed",
    "on_FireButton_released",
    "onElevationSliderValueChanged",
    "onAzimuthSliderValueChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[166];
    char stringdata0[11];
    char stringdata1[30];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[5];
    char stringdata5[20];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[24];
    char stringdata9[7];
    char stringdata10[8];
    char stringdata11[14];
    char stringdata12[8];
    char stringdata13[18];
    char stringdata14[9];
    char stringdata15[18];
    char stringdata16[17];
    char stringdata17[8];
    char stringdata18[9];
    char stringdata19[19];
    char stringdata20[19];
    char stringdata21[21];
    char stringdata22[19];
    char stringdata23[16];
    char stringdata24[6];
    char stringdata25[15];
    char stringdata26[10];
    char stringdata27[13];
    char stringdata28[17];
    char stringdata29[19];
    char stringdata30[23];
    char stringdata31[21];
    char stringdata32[6];
    char stringdata33[18];
    char stringdata34[13];
    char stringdata35[17];
    char stringdata36[17];
    char stringdata37[19];
    char stringdata38[22];
    char stringdata39[7];
    char stringdata40[9];
    char stringdata41[14];
    char stringdata42[11];
    char stringdata43[14];
    char stringdata44[18];
    char stringdata45[22];
    char stringdata46[12];
    char stringdata47[13];
    char stringdata48[18];
    char stringdata49[27];
    char stringdata50[19];
    char stringdata51[10];
    char stringdata52[21];
    char stringdata53[20];
    char stringdata54[20];
    char stringdata55[30];
    char stringdata56[30];
    char stringdata57[24];
    char stringdata58[34];
    char stringdata59[23];
    char stringdata60[24];
    char stringdata61[32];
    char stringdata62[33];
    char stringdata63[14];
    char stringdata64[6];
    char stringdata65[16];
    char stringdata66[19];
    char stringdata67[13];
    char stringdata68[17];
    char stringdata69[17];
    char stringdata70[19];
    char stringdata71[17];
    char stringdata72[18];
    char stringdata73[9];
    char stringdata74[16];
    char stringdata75[15];
    char stringdata76[14];
    char stringdata77[25];
    char stringdata78[7];
    char stringdata79[22];
    char stringdata80[23];
    char stringdata81[30];
    char stringdata82[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 29),  // "onOperationalStateModeChanged"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 15),  // "OperationalMode"
        QT_MOC_LITERAL(58, 4),  // "mode"
        QT_MOC_LITERAL(63, 19),  // "onJoystickAxisMoved"
        QT_MOC_LITERAL(83, 4),  // "axis"
        QT_MOC_LITERAL(88, 5),  // "value"
        QT_MOC_LITERAL(94, 23),  // "onJoystickButtonPressed"
        QT_MOC_LITERAL(118, 6),  // "button"
        QT_MOC_LITERAL(125, 7),  // "pressed"
        QT_MOC_LITERAL(133, 13),  // "onModeChanged"
        QT_MOC_LITERAL(147, 7),  // "newMode"
        QT_MOC_LITERAL(155, 17),  // "onFireModeChanged"
        QT_MOC_LITERAL(173, 8),  // "FireMode"
        QT_MOC_LITERAL(182, 17),  // "onTrackIdSelected"
        QT_MOC_LITERAL(200, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(217, 7),  // "current"
        QT_MOC_LITERAL(225, 8),  // "previous"
        QT_MOC_LITERAL(234, 18),  // "on_idleBtn_clicked"
        QT_MOC_LITERAL(253, 18),  // "on_survBtn_clicked"
        QT_MOC_LITERAL(272, 20),  // "on_engageBtn_clicked"
        QT_MOC_LITERAL(293, 18),  // "on_trckBtn_clicked"
        QT_MOC_LITERAL(312, 15),  // "onErrorOccurred"
        QT_MOC_LITERAL(328, 5),  // "error"
        QT_MOC_LITERAL(334, 14),  // "onFrequencySet"
        QT_MOC_LITERAL(349, 9),  // "frequency"
        QT_MOC_LITERAL(359, 12),  // "majorVersion"
        QT_MOC_LITERAL(372, 16),  // "secondaryVersion"
        QT_MOC_LITERAL(389, 18),  // "maintenanceVersion"
        QT_MOC_LITERAL(408, 22),  // "onSettingValueReceived"
        QT_MOC_LITERAL(431, 20),  // "onLaserCountReceived"
        QT_MOC_LITERAL(452, 5),  // "count"
        QT_MOC_LITERAL(458, 17),  // "onSelfCheckResult"
        QT_MOC_LITERAL(476, 12),  // "systemStatus"
        QT_MOC_LITERAL(489, 16),  // "temperatureAlarm"
        QT_MOC_LITERAL(506, 16),  // "biasVoltageFault"
        QT_MOC_LITERAL(523, 18),  // "counterMalfunction"
        QT_MOC_LITERAL(542, 21),  // "onRangingDataReceived"
        QT_MOC_LITERAL(564, 6),  // "status"
        QT_MOC_LITERAL(571, 8),  // "distance"
        QT_MOC_LITERAL(580, 13),  // "decimalPlaces"
        QT_MOC_LITERAL(594, 10),  // "echoStatus"
        QT_MOC_LITERAL(605, 13),  // "sendSelfCheck"
        QT_MOC_LITERAL(619, 17),  // "sendSingleRanging"
        QT_MOC_LITERAL(637, 21),  // "sendContinuousRanging"
        QT_MOC_LITERAL(659, 11),  // "stopRanging"
        QT_MOC_LITERAL(671, 12),  // "setFrequency"
        QT_MOC_LITERAL(684, 17),  // "querySettingValue"
        QT_MOC_LITERAL(702, 26),  // "queryAccumulatedLaserCount"
        QT_MOC_LITERAL(729, 18),  // "onLRFStatusChanged"
        QT_MOC_LITERAL(748, 9),  // "connected"
        QT_MOC_LITERAL(758, 20),  // "onRadarStatusChanged"
        QT_MOC_LITERAL(779, 19),  // "onGyroStatusChanged"
        QT_MOC_LITERAL(799, 19),  // "onPLC1StatusChanged"
        QT_MOC_LITERAL(819, 29),  // "onAZStepperMotorStatusChanged"
        QT_MOC_LITERAL(849, 29),  // "onELStepperMotorStatusChanged"
        QT_MOC_LITERAL(879, 23),  // "onActuatorStatusChanged"
        QT_MOC_LITERAL(903, 33),  // "on_switchMotionModeButton_cli..."
        QT_MOC_LITERAL(937, 22),  // "on_trackButton_clicked"
        QT_MOC_LITERAL(960, 23),  // "on_engageButton_clicked"
        QT_MOC_LITERAL(984, 31),  // "on_cancelTrackingButton_clicked"
        QT_MOC_LITERAL(1016, 32),  // "on_detectionToggleButton_clicked"
        QT_MOC_LITERAL(1049, 13),  // "onUpSwChanged"
        QT_MOC_LITERAL(1063, 5),  // "state"
        QT_MOC_LITERAL(1069, 15),  // "onDownSwChanged"
        QT_MOC_LITERAL(1085, 18),  // "onMenuValSwChanged"
        QT_MOC_LITERAL(1104, 12),  // "showIdleMenu"
        QT_MOC_LITERAL(1117, 16),  // "handleMenuClosed"
        QT_MOC_LITERAL(1134, 16),  // "showSystemStatus"
        QT_MOC_LITERAL(1151, 18),  // "personalizeReticle"
        QT_MOC_LITERAL(1170, 16),  // "adjustBrightness"
        QT_MOC_LITERAL(1187, 17),  // "configureSettings"
        QT_MOC_LITERAL(1205, 8),  // "viewLogs"
        QT_MOC_LITERAL(1214, 15),  // "softwareUpdates"
        QT_MOC_LITERAL(1230, 14),  // "runDiagnostics"
        QT_MOC_LITERAL(1245, 13),  // "showHelpAbout"
        QT_MOC_LITERAL(1259, 24),  // "handleMenuOptionSelected"
        QT_MOC_LITERAL(1284, 6),  // "option"
        QT_MOC_LITERAL(1291, 21),  // "on_FireButton_pressed"
        QT_MOC_LITERAL(1313, 22),  // "on_FireButton_released"
        QT_MOC_LITERAL(1336, 29),  // "onElevationSliderValueChanged"
        QT_MOC_LITERAL(1366, 27)   // "onAzimuthSliderValueChanged"
    },
    "MainWindow",
    "onOperationalStateModeChanged",
    "",
    "OperationalMode",
    "mode",
    "onJoystickAxisMoved",
    "axis",
    "value",
    "onJoystickButtonPressed",
    "button",
    "pressed",
    "onModeChanged",
    "newMode",
    "onFireModeChanged",
    "FireMode",
    "onTrackIdSelected",
    "QListWidgetItem*",
    "current",
    "previous",
    "on_idleBtn_clicked",
    "on_survBtn_clicked",
    "on_engageBtn_clicked",
    "on_trckBtn_clicked",
    "onErrorOccurred",
    "error",
    "onFrequencySet",
    "frequency",
    "majorVersion",
    "secondaryVersion",
    "maintenanceVersion",
    "onSettingValueReceived",
    "onLaserCountReceived",
    "count",
    "onSelfCheckResult",
    "systemStatus",
    "temperatureAlarm",
    "biasVoltageFault",
    "counterMalfunction",
    "onRangingDataReceived",
    "status",
    "distance",
    "decimalPlaces",
    "echoStatus",
    "sendSelfCheck",
    "sendSingleRanging",
    "sendContinuousRanging",
    "stopRanging",
    "setFrequency",
    "querySettingValue",
    "queryAccumulatedLaserCount",
    "onLRFStatusChanged",
    "connected",
    "onRadarStatusChanged",
    "onGyroStatusChanged",
    "onPLC1StatusChanged",
    "onAZStepperMotorStatusChanged",
    "onELStepperMotorStatusChanged",
    "onActuatorStatusChanged",
    "on_switchMotionModeButton_clicked",
    "on_trackButton_clicked",
    "on_engageButton_clicked",
    "on_cancelTrackingButton_clicked",
    "on_detectionToggleButton_clicked",
    "onUpSwChanged",
    "state",
    "onDownSwChanged",
    "onMenuValSwChanged",
    "showIdleMenu",
    "handleMenuClosed",
    "showSystemStatus",
    "personalizeReticle",
    "adjustBrightness",
    "configureSettings",
    "viewLogs",
    "softwareUpdates",
    "runDiagnostics",
    "showHelpAbout",
    "handleMenuOptionSelected",
    "option",
    "on_FireButton_pressed",
    "on_FireButton_released",
    "onElevationSliderValueChanged",
    "onAzimuthSliderValueChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  332,    2, 0x08,    1 /* Private */,
       5,    2,  335,    2, 0x08,    3 /* Private */,
       8,    2,  340,    2, 0x08,    6 /* Private */,
      11,    1,  345,    2, 0x08,    9 /* Private */,
      13,    1,  348,    2, 0x08,   11 /* Private */,
      15,    2,  351,    2, 0x08,   13 /* Private */,
      19,    0,  356,    2, 0x08,   16 /* Private */,
      20,    0,  357,    2, 0x08,   17 /* Private */,
      21,    0,  358,    2, 0x08,   18 /* Private */,
      22,    0,  359,    2, 0x08,   19 /* Private */,
      23,    1,  360,    2, 0x08,   20 /* Private */,
      25,    4,  363,    2, 0x08,   22 /* Private */,
      30,    1,  372,    2, 0x08,   27 /* Private */,
      31,    1,  375,    2, 0x08,   29 /* Private */,
      33,    4,  378,    2, 0x08,   31 /* Private */,
      38,    4,  387,    2, 0x08,   36 /* Private */,
      43,    0,  396,    2, 0x08,   41 /* Private */,
      44,    0,  397,    2, 0x08,   42 /* Private */,
      45,    0,  398,    2, 0x08,   43 /* Private */,
      46,    0,  399,    2, 0x08,   44 /* Private */,
      47,    0,  400,    2, 0x08,   45 /* Private */,
      48,    0,  401,    2, 0x08,   46 /* Private */,
      49,    0,  402,    2, 0x08,   47 /* Private */,
      50,    1,  403,    2, 0x08,   48 /* Private */,
      52,    1,  406,    2, 0x08,   50 /* Private */,
      53,    1,  409,    2, 0x08,   52 /* Private */,
      54,    1,  412,    2, 0x08,   54 /* Private */,
      55,    1,  415,    2, 0x08,   56 /* Private */,
      56,    1,  418,    2, 0x08,   58 /* Private */,
      57,    1,  421,    2, 0x08,   60 /* Private */,
      58,    0,  424,    2, 0x08,   62 /* Private */,
      59,    0,  425,    2, 0x08,   63 /* Private */,
      60,    0,  426,    2, 0x08,   64 /* Private */,
      61,    0,  427,    2, 0x08,   65 /* Private */,
      62,    0,  428,    2, 0x08,   66 /* Private */,
      63,    1,  429,    2, 0x08,   67 /* Private */,
      65,    1,  432,    2, 0x08,   69 /* Private */,
      66,    1,  435,    2, 0x08,   71 /* Private */,
      67,    0,  438,    2, 0x08,   73 /* Private */,
      68,    0,  439,    2, 0x08,   74 /* Private */,
      69,    0,  440,    2, 0x08,   75 /* Private */,
      70,    0,  441,    2, 0x08,   76 /* Private */,
      71,    0,  442,    2, 0x08,   77 /* Private */,
      72,    0,  443,    2, 0x08,   78 /* Private */,
      73,    0,  444,    2, 0x08,   79 /* Private */,
      74,    0,  445,    2, 0x08,   80 /* Private */,
      75,    0,  446,    2, 0x08,   81 /* Private */,
      76,    0,  447,    2, 0x08,   82 /* Private */,
      77,    1,  448,    2, 0x08,   83 /* Private */,
      79,    0,  451,    2, 0x08,   85 /* Private */,
      80,    0,  452,    2, 0x08,   86 /* Private */,
      81,    1,  453,    2, 0x08,   87 /* Private */,
      82,    1,  456,    2, 0x08,   89 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    9,   10,
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 14,    4,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 16,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   26,   27,   28,   29,
    QMetaType::Void, QMetaType::UChar,    7,
    QMetaType::Void, QMetaType::UInt,   32,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   34,   35,   36,   37,
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar,   39,   40,   41,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   64,
    QMetaType::Void, QMetaType::Bool,   64,
    QMetaType::Void, QMetaType::Bool,   64,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onOperationalStateModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const OperationalMode &, std::false_type>,
        // method 'onJoystickAxisMoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onJoystickButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<OperationalMode, std::false_type>,
        // method 'onFireModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<FireMode, std::false_type>,
        // method 'onTrackIdSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_idleBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_survBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_engageBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_trckBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onFrequencySet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'onSettingValueReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'onLaserCountReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint32, std::false_type>,
        // method 'onSelfCheckResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'onRangingDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'sendSelfCheck'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendSingleRanging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendContinuousRanging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopRanging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setFrequency'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'querySettingValue'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'queryAccumulatedLaserCount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLRFStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onRadarStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onGyroStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onPLC1StatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onAZStepperMotorStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onELStepperMotorStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onActuatorStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_switchMotionModeButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_trackButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_engageButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancelTrackingButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_detectionToggleButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUpSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onDownSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onMenuValSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showIdleMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMenuClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showSystemStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'personalizeReticle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'adjustBrightness'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'configureSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'viewLogs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'softwareUpdates'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'runDiagnostics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showHelpAbout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMenuOptionSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_FireButton_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_FireButton_released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onElevationSliderValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onAzimuthSliderValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onOperationalStateModeChanged((*reinterpret_cast< std::add_pointer_t<OperationalMode>>(_a[1]))); break;
        case 1: _t->onJoystickAxisMoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->onJoystickButtonPressed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 3: _t->onModeChanged((*reinterpret_cast< std::add_pointer_t<OperationalMode>>(_a[1]))); break;
        case 4: _t->onFireModeChanged((*reinterpret_cast< std::add_pointer_t<FireMode>>(_a[1]))); break;
        case 5: _t->onTrackIdSelected((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[2]))); break;
        case 6: _t->on_idleBtn_clicked(); break;
        case 7: _t->on_survBtn_clicked(); break;
        case 8: _t->on_engageBtn_clicked(); break;
        case 9: _t->on_trckBtn_clicked(); break;
        case 10: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->onFrequencySet((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 12: _t->onSettingValueReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 13: _t->onLaserCountReceived((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 14: _t->onSelfCheckResult((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 15: _t->onRangingDataReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 16: _t->sendSelfCheck(); break;
        case 17: _t->sendSingleRanging(); break;
        case 18: _t->sendContinuousRanging(); break;
        case 19: _t->stopRanging(); break;
        case 20: _t->setFrequency(); break;
        case 21: _t->querySettingValue(); break;
        case 22: _t->queryAccumulatedLaserCount(); break;
        case 23: _t->onLRFStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 24: _t->onRadarStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 25: _t->onGyroStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 26: _t->onPLC1StatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 27: _t->onAZStepperMotorStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 28: _t->onELStepperMotorStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 29: _t->onActuatorStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 30: _t->on_switchMotionModeButton_clicked(); break;
        case 31: _t->on_trackButton_clicked(); break;
        case 32: _t->on_engageButton_clicked(); break;
        case 33: _t->on_cancelTrackingButton_clicked(); break;
        case 34: _t->on_detectionToggleButton_clicked(); break;
        case 35: _t->onUpSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 36: _t->onDownSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 37: _t->onMenuValSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 38: _t->showIdleMenu(); break;
        case 39: _t->handleMenuClosed(); break;
        case 40: _t->showSystemStatus(); break;
        case 41: _t->personalizeReticle(); break;
        case 42: _t->adjustBrightness(); break;
        case 43: _t->configureSettings(); break;
        case 44: _t->viewLogs(); break;
        case 45: _t->softwareUpdates(); break;
        case 46: _t->runDiagnostics(); break;
        case 47: _t->showHelpAbout(); break;
        case 48: _t->handleMenuOptionSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 49: _t->on_FireButton_pressed(); break;
        case 50: _t->on_FireButton_released(); break;
        case 51: _t->onElevationSliderValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 52: _t->onAzimuthSliderValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 53;
    }
    return _id;
}
QT_WARNING_POP
