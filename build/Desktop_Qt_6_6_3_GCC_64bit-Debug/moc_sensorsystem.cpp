/****************************************************************************
** Meta object code from reading C++ file 'sensorsystem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/sensor/sensorsystem.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensorsystem.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSensorSystemENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSensorSystemENDCLASS = QtMocHelpers::stringData(
    "SensorSystem",
    "errorOccurred",
    "",
    "error",
    "frequencySet",
    "frequency",
    "majorVersion",
    "secondaryVersion",
    "maintenanceVersion",
    "settingValueReceived",
    "value",
    "laserCountReceived",
    "count",
    "selfCheckResult",
    "systemStatus",
    "temperatureAlarm",
    "biasVoltageFault",
    "counterMalfunction",
    "rangingDataReceived",
    "status",
    "distance",
    "decimalPlaces",
    "echoStatus",
    "gyroDataUpdated",
    "Roll",
    "Pitch",
    "Yaw",
    "proximitySensorActivated",
    "state",
    "temperatureUpdated",
    "temperature",
    "pressureUpdated",
    "pressure",
    "lrfConnectionStatusChanged",
    "connected",
    "radarConnectionStatusChanged",
    "gyroConnectionStatusChanged",
    "sendSelfCheck",
    "sendSingleRanging",
    "sendContinuousRanging",
    "stopRanging",
    "setFrequency",
    "querySettingValue",
    "queryAccumulatedLaserCount",
    "onGyroDataReceived",
    "handleErrorOccurred",
    "handleFrequencySet",
    "handleSettingValueReceived",
    "handleLaserCountReceived",
    "handleSelfCheckResult",
    "handleRangingDataReceived",
    "onLRFInterfaceDestroyed",
    "obj",
    "handleLRFConnectionStatusChanged",
    "handleRadarConnectionStatusChanged",
    "handleGyroConnectionStatusChanged",
    "onGunStateChanged",
    "onLoadAmmunitionStateChanged",
    "onStationStateChanged",
    "onHomeSwChanged",
    "onStabilizationSwChanged",
    "onAuthorizeSwChanged",
    "onCamSwChanged",
    "onUpSwChanged",
    "onDownSwChanged",
    "onMenuValSwChanged",
    "onSpeedSwChanged",
    "speed",
    "onFireModeStateInputChanged",
    "mode",
    "onPanelTemperatureChanged",
    "onStationUpperSensorStateChanged",
    "onStationLowerSensorStateChanged",
    "onStationAmmunitionLevelChanged",
    "onStationInput1Changed",
    "onStationInput2Changed",
    "onStationInput3Changed",
    "onEOTemperatureChanged",
    "onEOPressureChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSensorSystemENDCLASS_t {
    uint offsetsAndSizes[158];
    char stringdata0[13];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[13];
    char stringdata5[10];
    char stringdata6[13];
    char stringdata7[17];
    char stringdata8[19];
    char stringdata9[21];
    char stringdata10[6];
    char stringdata11[19];
    char stringdata12[6];
    char stringdata13[16];
    char stringdata14[13];
    char stringdata15[17];
    char stringdata16[17];
    char stringdata17[19];
    char stringdata18[20];
    char stringdata19[7];
    char stringdata20[9];
    char stringdata21[14];
    char stringdata22[11];
    char stringdata23[16];
    char stringdata24[5];
    char stringdata25[6];
    char stringdata26[4];
    char stringdata27[25];
    char stringdata28[6];
    char stringdata29[19];
    char stringdata30[12];
    char stringdata31[16];
    char stringdata32[9];
    char stringdata33[27];
    char stringdata34[10];
    char stringdata35[29];
    char stringdata36[28];
    char stringdata37[14];
    char stringdata38[18];
    char stringdata39[22];
    char stringdata40[12];
    char stringdata41[13];
    char stringdata42[18];
    char stringdata43[27];
    char stringdata44[19];
    char stringdata45[20];
    char stringdata46[19];
    char stringdata47[27];
    char stringdata48[25];
    char stringdata49[22];
    char stringdata50[26];
    char stringdata51[24];
    char stringdata52[4];
    char stringdata53[33];
    char stringdata54[35];
    char stringdata55[34];
    char stringdata56[18];
    char stringdata57[29];
    char stringdata58[22];
    char stringdata59[16];
    char stringdata60[25];
    char stringdata61[21];
    char stringdata62[15];
    char stringdata63[14];
    char stringdata64[16];
    char stringdata65[19];
    char stringdata66[17];
    char stringdata67[6];
    char stringdata68[28];
    char stringdata69[5];
    char stringdata70[26];
    char stringdata71[33];
    char stringdata72[33];
    char stringdata73[32];
    char stringdata74[23];
    char stringdata75[23];
    char stringdata76[23];
    char stringdata77[23];
    char stringdata78[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSensorSystemENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSensorSystemENDCLASS_t qt_meta_stringdata_CLASSSensorSystemENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "SensorSystem"
        QT_MOC_LITERAL(13, 13),  // "errorOccurred"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 5),  // "error"
        QT_MOC_LITERAL(34, 12),  // "frequencySet"
        QT_MOC_LITERAL(47, 9),  // "frequency"
        QT_MOC_LITERAL(57, 12),  // "majorVersion"
        QT_MOC_LITERAL(70, 16),  // "secondaryVersion"
        QT_MOC_LITERAL(87, 18),  // "maintenanceVersion"
        QT_MOC_LITERAL(106, 20),  // "settingValueReceived"
        QT_MOC_LITERAL(127, 5),  // "value"
        QT_MOC_LITERAL(133, 18),  // "laserCountReceived"
        QT_MOC_LITERAL(152, 5),  // "count"
        QT_MOC_LITERAL(158, 15),  // "selfCheckResult"
        QT_MOC_LITERAL(174, 12),  // "systemStatus"
        QT_MOC_LITERAL(187, 16),  // "temperatureAlarm"
        QT_MOC_LITERAL(204, 16),  // "biasVoltageFault"
        QT_MOC_LITERAL(221, 18),  // "counterMalfunction"
        QT_MOC_LITERAL(240, 19),  // "rangingDataReceived"
        QT_MOC_LITERAL(260, 6),  // "status"
        QT_MOC_LITERAL(267, 8),  // "distance"
        QT_MOC_LITERAL(276, 13),  // "decimalPlaces"
        QT_MOC_LITERAL(290, 10),  // "echoStatus"
        QT_MOC_LITERAL(301, 15),  // "gyroDataUpdated"
        QT_MOC_LITERAL(317, 4),  // "Roll"
        QT_MOC_LITERAL(322, 5),  // "Pitch"
        QT_MOC_LITERAL(328, 3),  // "Yaw"
        QT_MOC_LITERAL(332, 24),  // "proximitySensorActivated"
        QT_MOC_LITERAL(357, 5),  // "state"
        QT_MOC_LITERAL(363, 18),  // "temperatureUpdated"
        QT_MOC_LITERAL(382, 11),  // "temperature"
        QT_MOC_LITERAL(394, 15),  // "pressureUpdated"
        QT_MOC_LITERAL(410, 8),  // "pressure"
        QT_MOC_LITERAL(419, 26),  // "lrfConnectionStatusChanged"
        QT_MOC_LITERAL(446, 9),  // "connected"
        QT_MOC_LITERAL(456, 28),  // "radarConnectionStatusChanged"
        QT_MOC_LITERAL(485, 27),  // "gyroConnectionStatusChanged"
        QT_MOC_LITERAL(513, 13),  // "sendSelfCheck"
        QT_MOC_LITERAL(527, 17),  // "sendSingleRanging"
        QT_MOC_LITERAL(545, 21),  // "sendContinuousRanging"
        QT_MOC_LITERAL(567, 11),  // "stopRanging"
        QT_MOC_LITERAL(579, 12),  // "setFrequency"
        QT_MOC_LITERAL(592, 17),  // "querySettingValue"
        QT_MOC_LITERAL(610, 26),  // "queryAccumulatedLaserCount"
        QT_MOC_LITERAL(637, 18),  // "onGyroDataReceived"
        QT_MOC_LITERAL(656, 19),  // "handleErrorOccurred"
        QT_MOC_LITERAL(676, 18),  // "handleFrequencySet"
        QT_MOC_LITERAL(695, 26),  // "handleSettingValueReceived"
        QT_MOC_LITERAL(722, 24),  // "handleLaserCountReceived"
        QT_MOC_LITERAL(747, 21),  // "handleSelfCheckResult"
        QT_MOC_LITERAL(769, 25),  // "handleRangingDataReceived"
        QT_MOC_LITERAL(795, 23),  // "onLRFInterfaceDestroyed"
        QT_MOC_LITERAL(819, 3),  // "obj"
        QT_MOC_LITERAL(823, 32),  // "handleLRFConnectionStatusChanged"
        QT_MOC_LITERAL(856, 34),  // "handleRadarConnectionStatusCh..."
        QT_MOC_LITERAL(891, 33),  // "handleGyroConnectionStatusCha..."
        QT_MOC_LITERAL(925, 17),  // "onGunStateChanged"
        QT_MOC_LITERAL(943, 28),  // "onLoadAmmunitionStateChanged"
        QT_MOC_LITERAL(972, 21),  // "onStationStateChanged"
        QT_MOC_LITERAL(994, 15),  // "onHomeSwChanged"
        QT_MOC_LITERAL(1010, 24),  // "onStabilizationSwChanged"
        QT_MOC_LITERAL(1035, 20),  // "onAuthorizeSwChanged"
        QT_MOC_LITERAL(1056, 14),  // "onCamSwChanged"
        QT_MOC_LITERAL(1071, 13),  // "onUpSwChanged"
        QT_MOC_LITERAL(1085, 15),  // "onDownSwChanged"
        QT_MOC_LITERAL(1101, 18),  // "onMenuValSwChanged"
        QT_MOC_LITERAL(1120, 16),  // "onSpeedSwChanged"
        QT_MOC_LITERAL(1137, 5),  // "speed"
        QT_MOC_LITERAL(1143, 27),  // "onFireModeStateInputChanged"
        QT_MOC_LITERAL(1171, 4),  // "mode"
        QT_MOC_LITERAL(1176, 25),  // "onPanelTemperatureChanged"
        QT_MOC_LITERAL(1202, 32),  // "onStationUpperSensorStateChanged"
        QT_MOC_LITERAL(1235, 32),  // "onStationLowerSensorStateChanged"
        QT_MOC_LITERAL(1268, 31),  // "onStationAmmunitionLevelChanged"
        QT_MOC_LITERAL(1300, 22),  // "onStationInput1Changed"
        QT_MOC_LITERAL(1323, 22),  // "onStationInput2Changed"
        QT_MOC_LITERAL(1346, 22),  // "onStationInput3Changed"
        QT_MOC_LITERAL(1369, 22),  // "onEOTemperatureChanged"
        QT_MOC_LITERAL(1392, 19)   // "onEOPressureChanged"
    },
    "SensorSystem",
    "errorOccurred",
    "",
    "error",
    "frequencySet",
    "frequency",
    "majorVersion",
    "secondaryVersion",
    "maintenanceVersion",
    "settingValueReceived",
    "value",
    "laserCountReceived",
    "count",
    "selfCheckResult",
    "systemStatus",
    "temperatureAlarm",
    "biasVoltageFault",
    "counterMalfunction",
    "rangingDataReceived",
    "status",
    "distance",
    "decimalPlaces",
    "echoStatus",
    "gyroDataUpdated",
    "Roll",
    "Pitch",
    "Yaw",
    "proximitySensorActivated",
    "state",
    "temperatureUpdated",
    "temperature",
    "pressureUpdated",
    "pressure",
    "lrfConnectionStatusChanged",
    "connected",
    "radarConnectionStatusChanged",
    "gyroConnectionStatusChanged",
    "sendSelfCheck",
    "sendSingleRanging",
    "sendContinuousRanging",
    "stopRanging",
    "setFrequency",
    "querySettingValue",
    "queryAccumulatedLaserCount",
    "onGyroDataReceived",
    "handleErrorOccurred",
    "handleFrequencySet",
    "handleSettingValueReceived",
    "handleLaserCountReceived",
    "handleSelfCheckResult",
    "handleRangingDataReceived",
    "onLRFInterfaceDestroyed",
    "obj",
    "handleLRFConnectionStatusChanged",
    "handleRadarConnectionStatusChanged",
    "handleGyroConnectionStatusChanged",
    "onGunStateChanged",
    "onLoadAmmunitionStateChanged",
    "onStationStateChanged",
    "onHomeSwChanged",
    "onStabilizationSwChanged",
    "onAuthorizeSwChanged",
    "onCamSwChanged",
    "onUpSwChanged",
    "onDownSwChanged",
    "onMenuValSwChanged",
    "onSpeedSwChanged",
    "speed",
    "onFireModeStateInputChanged",
    "mode",
    "onPanelTemperatureChanged",
    "onStationUpperSensorStateChanged",
    "onStationLowerSensorStateChanged",
    "onStationAmmunitionLevelChanged",
    "onStationInput1Changed",
    "onStationInput2Changed",
    "onStationInput3Changed",
    "onEOTemperatureChanged",
    "onEOPressureChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSensorSystemENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      52,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  326,    2, 0x06,    1 /* Public */,
       4,    4,  329,    2, 0x06,    3 /* Public */,
       9,    1,  338,    2, 0x06,    8 /* Public */,
      11,    1,  341,    2, 0x06,   10 /* Public */,
      13,    4,  344,    2, 0x06,   12 /* Public */,
      18,    4,  353,    2, 0x06,   17 /* Public */,
      23,    3,  362,    2, 0x06,   22 /* Public */,
      27,    1,  369,    2, 0x06,   26 /* Public */,
      29,    1,  372,    2, 0x06,   28 /* Public */,
      31,    1,  375,    2, 0x06,   30 /* Public */,
      33,    1,  378,    2, 0x06,   32 /* Public */,
      35,    1,  381,    2, 0x06,   34 /* Public */,
      36,    1,  384,    2, 0x06,   36 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      37,    0,  387,    2, 0x0a,   38 /* Public */,
      38,    0,  388,    2, 0x0a,   39 /* Public */,
      39,    0,  389,    2, 0x0a,   40 /* Public */,
      40,    0,  390,    2, 0x0a,   41 /* Public */,
      41,    1,  391,    2, 0x0a,   42 /* Public */,
      42,    0,  394,    2, 0x0a,   44 /* Public */,
      43,    0,  395,    2, 0x0a,   45 /* Public */,
      44,    3,  396,    2, 0x0a,   46 /* Public */,
      45,    1,  403,    2, 0x0a,   50 /* Public */,
      46,    4,  406,    2, 0x0a,   52 /* Public */,
      47,    1,  415,    2, 0x0a,   57 /* Public */,
      48,    1,  418,    2, 0x0a,   59 /* Public */,
      49,    4,  421,    2, 0x0a,   61 /* Public */,
      50,    4,  430,    2, 0x0a,   66 /* Public */,
      51,    1,  439,    2, 0x0a,   71 /* Public */,
      53,    1,  442,    2, 0x0a,   73 /* Public */,
      54,    1,  445,    2, 0x0a,   75 /* Public */,
      55,    1,  448,    2, 0x0a,   77 /* Public */,
      56,    1,  451,    2, 0x0a,   79 /* Public */,
      57,    1,  454,    2, 0x0a,   81 /* Public */,
      58,    1,  457,    2, 0x0a,   83 /* Public */,
      59,    1,  460,    2, 0x0a,   85 /* Public */,
      60,    1,  463,    2, 0x0a,   87 /* Public */,
      61,    1,  466,    2, 0x0a,   89 /* Public */,
      62,    1,  469,    2, 0x0a,   91 /* Public */,
      63,    1,  472,    2, 0x0a,   93 /* Public */,
      64,    1,  475,    2, 0x0a,   95 /* Public */,
      65,    1,  478,    2, 0x0a,   97 /* Public */,
      66,    1,  481,    2, 0x0a,   99 /* Public */,
      68,    1,  484,    2, 0x0a,  101 /* Public */,
      70,    1,  487,    2, 0x0a,  103 /* Public */,
      71,    1,  490,    2, 0x0a,  105 /* Public */,
      72,    1,  493,    2, 0x0a,  107 /* Public */,
      73,    1,  496,    2, 0x0a,  109 /* Public */,
      74,    1,  499,    2, 0x0a,  111 /* Public */,
      75,    1,  502,    2, 0x0a,  113 /* Public */,
      76,    1,  505,    2, 0x0a,  115 /* Public */,
      77,    1,  508,    2, 0x0a,  117 /* Public */,
      78,    1,  511,    2, 0x0a,  119 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   14,   15,   16,   17,
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   24,   25,   26,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Double,   30,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,   34,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   24,   25,   26,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   14,   15,   16,   17,
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::QObjectStar,   52,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   69,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   32,

       0        // eod
};

Q_CONSTINIT const QMetaObject SensorSystem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSensorSystemENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSensorSystemENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSensorSystemENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SensorSystem, std::true_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'frequencySet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'settingValueReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'laserCountReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint32, std::false_type>,
        // method 'selfCheckResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'rangingDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'gyroDataUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'proximitySensorActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'temperatureUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'pressureUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'lrfConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'radarConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'gyroConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
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
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'querySettingValue'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'queryAccumulatedLaserCount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGyroDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'handleErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleFrequencySet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'handleSettingValueReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'handleLaserCountReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint32, std::false_type>,
        // method 'handleSelfCheckResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'handleRangingDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        // method 'onLRFInterfaceDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>,
        // method 'handleLRFConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleRadarConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleGyroConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onGunStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onLoadAmmunitionStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStationStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onHomeSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStabilizationSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onAuthorizeSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onCamSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onUpSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onDownSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onMenuValSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onSpeedSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onFireModeStateInputChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onPanelTemperatureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onStationUpperSensorStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStationLowerSensorStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStationAmmunitionLevelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStationInput1Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStationInput2Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onStationInput3Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onEOTemperatureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onEOPressureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void SensorSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SensorSystem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->frequencySet((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 2: _t->settingValueReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 3: _t->laserCountReceived((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 4: _t->selfCheckResult((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 5: _t->rangingDataReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 6: _t->gyroDataUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 7: _t->proximitySensorActivated((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->temperatureUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->pressureUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 10: _t->lrfConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->radarConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->gyroConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->sendSelfCheck(); break;
        case 14: _t->sendSingleRanging(); break;
        case 15: _t->sendContinuousRanging(); break;
        case 16: _t->stopRanging(); break;
        case 17: _t->setFrequency((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->querySettingValue(); break;
        case 19: _t->queryAccumulatedLaserCount(); break;
        case 20: _t->onGyroDataReceived((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 21: _t->handleErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->handleFrequencySet((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 23: _t->handleSettingValueReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 24: _t->handleLaserCountReceived((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 25: _t->handleSelfCheckResult((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 26: _t->handleRangingDataReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 27: _t->onLRFInterfaceDestroyed((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1]))); break;
        case 28: _t->handleLRFConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 29: _t->handleRadarConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 30: _t->handleGyroConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 31: _t->onGunStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 32: _t->onLoadAmmunitionStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 33: _t->onStationStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 34: _t->onHomeSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 35: _t->onStabilizationSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 36: _t->onAuthorizeSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 37: _t->onCamSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 38: _t->onUpSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 39: _t->onDownSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 40: _t->onMenuValSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 41: _t->onSpeedSwChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 42: _t->onFireModeStateInputChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 43: _t->onPanelTemperatureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 44: _t->onStationUpperSensorStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 45: _t->onStationLowerSensorStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 46: _t->onStationAmmunitionLevelChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 47: _t->onStationInput1Changed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 48: _t->onStationInput2Changed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 49: _t->onStationInput3Changed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 50: _t->onEOTemperatureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 51: _t->onEOPressureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SensorSystem::*)(const QString & );
            if (_t _q_method = &SensorSystem::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(quint8 , quint8 , quint8 , quint8 );
            if (_t _q_method = &SensorSystem::frequencySet; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(quint8 );
            if (_t _q_method = &SensorSystem::settingValueReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(quint32 );
            if (_t _q_method = &SensorSystem::laserCountReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(quint8 , quint8 , quint8 , quint8 );
            if (_t _q_method = &SensorSystem::selfCheckResult; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(quint8 , quint16 , quint8 , quint8 );
            if (_t _q_method = &SensorSystem::rangingDataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(double , double , double );
            if (_t _q_method = &SensorSystem::gyroDataUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(bool );
            if (_t _q_method = &SensorSystem::proximitySensorActivated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(double );
            if (_t _q_method = &SensorSystem::temperatureUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(double );
            if (_t _q_method = &SensorSystem::pressureUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(bool );
            if (_t _q_method = &SensorSystem::lrfConnectionStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(bool );
            if (_t _q_method = &SensorSystem::radarConnectionStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SensorSystem::*)(bool );
            if (_t _q_method = &SensorSystem::gyroConnectionStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
    }
}

const QMetaObject *SensorSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SensorSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSensorSystemENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SensorSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 52)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 52;
    }
    return _id;
}

// SIGNAL 0
void SensorSystem::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SensorSystem::frequencySet(quint8 _t1, quint8 _t2, quint8 _t3, quint8 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SensorSystem::settingValueReceived(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SensorSystem::laserCountReceived(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SensorSystem::selfCheckResult(quint8 _t1, quint8 _t2, quint8 _t3, quint8 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SensorSystem::rangingDataReceived(quint8 _t1, quint16 _t2, quint8 _t3, quint8 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SensorSystem::gyroDataUpdated(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SensorSystem::proximitySensorActivated(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SensorSystem::temperatureUpdated(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SensorSystem::pressureUpdated(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SensorSystem::lrfConnectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SensorSystem::radarConnectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SensorSystem::gyroConnectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
