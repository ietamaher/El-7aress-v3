/****************************************************************************
** Meta object code from reading C++ file 'datamodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/datamodel.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datamodel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSDataModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSDataModelENDCLASS = QtMocHelpers::stringData(
    "DataModel",
    "dataModelUpdated",
    "",
    "operationalStateModeChange",
    "OperationalMode",
    "mode",
    "upSwChanged",
    "state",
    "downSwChanged",
    "menuValSwChanged",
    "reticleStyleChanged",
    "style",
    "fireModeChanged",
    "FireMode",
    "deadManSwitchStateChanged",
    "setOperationalStateMode",
    "setMotionMode",
    "setLRFDistance",
    "distance",
    "setGyroOrientation",
    "roll",
    "pitch",
    "yaw",
    "setCrosshairPosition",
    "position",
    "setWeaponSystemStatus",
    "status",
    "setTargetInformation",
    "info",
    "setSystemTime",
    "time",
    "setGPSCoordinates",
    "coordinates",
    "setSensorReadings",
    "readings",
    "setAlertsWarnings",
    "alerts",
    "setDetectionEnabled",
    "enabled",
    "setStabilizationEnabled",
    "setGunEnabled",
    "setLoadAmmunition",
    "loaded",
    "setStationState",
    "setHomeSw",
    "setStabilizationSw",
    "setAuthorizeSw",
    "setCamActive",
    "setUpSw",
    "setDownSw",
    "setMenuValSw",
    "setFireMode",
    "setSpeedSw",
    "speed",
    "setPanelTemperature",
    "temperature",
    "setStationUpperSensor",
    "setStationLowerSensor",
    "setStationAmmunitionLevel",
    "setStationInput1",
    "setStationInput2",
    "setStationInput3",
    "setEOTemperature",
    "setEOPressure",
    "pressure",
    "setReticleStyle",
    "setDeadManSwitchState",
    "setGimbalAzimuthUpdated",
    "azimuth",
    "setGimbalElevationUpdated",
    "elevation"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSDataModelENDCLASS_t {
    uint offsetsAndSizes[142];
    char stringdata0[10];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[16];
    char stringdata5[5];
    char stringdata6[12];
    char stringdata7[6];
    char stringdata8[14];
    char stringdata9[17];
    char stringdata10[20];
    char stringdata11[6];
    char stringdata12[16];
    char stringdata13[9];
    char stringdata14[26];
    char stringdata15[24];
    char stringdata16[14];
    char stringdata17[15];
    char stringdata18[9];
    char stringdata19[19];
    char stringdata20[5];
    char stringdata21[6];
    char stringdata22[4];
    char stringdata23[21];
    char stringdata24[9];
    char stringdata25[22];
    char stringdata26[7];
    char stringdata27[21];
    char stringdata28[5];
    char stringdata29[14];
    char stringdata30[5];
    char stringdata31[18];
    char stringdata32[12];
    char stringdata33[18];
    char stringdata34[9];
    char stringdata35[18];
    char stringdata36[7];
    char stringdata37[20];
    char stringdata38[8];
    char stringdata39[24];
    char stringdata40[14];
    char stringdata41[18];
    char stringdata42[7];
    char stringdata43[16];
    char stringdata44[10];
    char stringdata45[19];
    char stringdata46[15];
    char stringdata47[13];
    char stringdata48[8];
    char stringdata49[10];
    char stringdata50[13];
    char stringdata51[12];
    char stringdata52[11];
    char stringdata53[6];
    char stringdata54[20];
    char stringdata55[12];
    char stringdata56[22];
    char stringdata57[22];
    char stringdata58[26];
    char stringdata59[17];
    char stringdata60[17];
    char stringdata61[17];
    char stringdata62[17];
    char stringdata63[14];
    char stringdata64[9];
    char stringdata65[16];
    char stringdata66[22];
    char stringdata67[24];
    char stringdata68[8];
    char stringdata69[26];
    char stringdata70[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSDataModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSDataModelENDCLASS_t qt_meta_stringdata_CLASSDataModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "DataModel"
        QT_MOC_LITERAL(10, 16),  // "dataModelUpdated"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 26),  // "operationalStateModeChange"
        QT_MOC_LITERAL(55, 15),  // "OperationalMode"
        QT_MOC_LITERAL(71, 4),  // "mode"
        QT_MOC_LITERAL(76, 11),  // "upSwChanged"
        QT_MOC_LITERAL(88, 5),  // "state"
        QT_MOC_LITERAL(94, 13),  // "downSwChanged"
        QT_MOC_LITERAL(108, 16),  // "menuValSwChanged"
        QT_MOC_LITERAL(125, 19),  // "reticleStyleChanged"
        QT_MOC_LITERAL(145, 5),  // "style"
        QT_MOC_LITERAL(151, 15),  // "fireModeChanged"
        QT_MOC_LITERAL(167, 8),  // "FireMode"
        QT_MOC_LITERAL(176, 25),  // "deadManSwitchStateChanged"
        QT_MOC_LITERAL(202, 23),  // "setOperationalStateMode"
        QT_MOC_LITERAL(226, 13),  // "setMotionMode"
        QT_MOC_LITERAL(240, 14),  // "setLRFDistance"
        QT_MOC_LITERAL(255, 8),  // "distance"
        QT_MOC_LITERAL(264, 18),  // "setGyroOrientation"
        QT_MOC_LITERAL(283, 4),  // "roll"
        QT_MOC_LITERAL(288, 5),  // "pitch"
        QT_MOC_LITERAL(294, 3),  // "yaw"
        QT_MOC_LITERAL(298, 20),  // "setCrosshairPosition"
        QT_MOC_LITERAL(319, 8),  // "position"
        QT_MOC_LITERAL(328, 21),  // "setWeaponSystemStatus"
        QT_MOC_LITERAL(350, 6),  // "status"
        QT_MOC_LITERAL(357, 20),  // "setTargetInformation"
        QT_MOC_LITERAL(378, 4),  // "info"
        QT_MOC_LITERAL(383, 13),  // "setSystemTime"
        QT_MOC_LITERAL(397, 4),  // "time"
        QT_MOC_LITERAL(402, 17),  // "setGPSCoordinates"
        QT_MOC_LITERAL(420, 11),  // "coordinates"
        QT_MOC_LITERAL(432, 17),  // "setSensorReadings"
        QT_MOC_LITERAL(450, 8),  // "readings"
        QT_MOC_LITERAL(459, 17),  // "setAlertsWarnings"
        QT_MOC_LITERAL(477, 6),  // "alerts"
        QT_MOC_LITERAL(484, 19),  // "setDetectionEnabled"
        QT_MOC_LITERAL(504, 7),  // "enabled"
        QT_MOC_LITERAL(512, 23),  // "setStabilizationEnabled"
        QT_MOC_LITERAL(536, 13),  // "setGunEnabled"
        QT_MOC_LITERAL(550, 17),  // "setLoadAmmunition"
        QT_MOC_LITERAL(568, 6),  // "loaded"
        QT_MOC_LITERAL(575, 15),  // "setStationState"
        QT_MOC_LITERAL(591, 9),  // "setHomeSw"
        QT_MOC_LITERAL(601, 18),  // "setStabilizationSw"
        QT_MOC_LITERAL(620, 14),  // "setAuthorizeSw"
        QT_MOC_LITERAL(635, 12),  // "setCamActive"
        QT_MOC_LITERAL(648, 7),  // "setUpSw"
        QT_MOC_LITERAL(656, 9),  // "setDownSw"
        QT_MOC_LITERAL(666, 12),  // "setMenuValSw"
        QT_MOC_LITERAL(679, 11),  // "setFireMode"
        QT_MOC_LITERAL(691, 10),  // "setSpeedSw"
        QT_MOC_LITERAL(702, 5),  // "speed"
        QT_MOC_LITERAL(708, 19),  // "setPanelTemperature"
        QT_MOC_LITERAL(728, 11),  // "temperature"
        QT_MOC_LITERAL(740, 21),  // "setStationUpperSensor"
        QT_MOC_LITERAL(762, 21),  // "setStationLowerSensor"
        QT_MOC_LITERAL(784, 25),  // "setStationAmmunitionLevel"
        QT_MOC_LITERAL(810, 16),  // "setStationInput1"
        QT_MOC_LITERAL(827, 16),  // "setStationInput2"
        QT_MOC_LITERAL(844, 16),  // "setStationInput3"
        QT_MOC_LITERAL(861, 16),  // "setEOTemperature"
        QT_MOC_LITERAL(878, 13),  // "setEOPressure"
        QT_MOC_LITERAL(892, 8),  // "pressure"
        QT_MOC_LITERAL(901, 15),  // "setReticleStyle"
        QT_MOC_LITERAL(917, 21),  // "setDeadManSwitchState"
        QT_MOC_LITERAL(939, 23),  // "setGimbalAzimuthUpdated"
        QT_MOC_LITERAL(963, 7),  // "azimuth"
        QT_MOC_LITERAL(971, 25),  // "setGimbalElevationUpdated"
        QT_MOC_LITERAL(997, 9)   // "elevation"
    },
    "DataModel",
    "dataModelUpdated",
    "",
    "operationalStateModeChange",
    "OperationalMode",
    "mode",
    "upSwChanged",
    "state",
    "downSwChanged",
    "menuValSwChanged",
    "reticleStyleChanged",
    "style",
    "fireModeChanged",
    "FireMode",
    "deadManSwitchStateChanged",
    "setOperationalStateMode",
    "setMotionMode",
    "setLRFDistance",
    "distance",
    "setGyroOrientation",
    "roll",
    "pitch",
    "yaw",
    "setCrosshairPosition",
    "position",
    "setWeaponSystemStatus",
    "status",
    "setTargetInformation",
    "info",
    "setSystemTime",
    "time",
    "setGPSCoordinates",
    "coordinates",
    "setSensorReadings",
    "readings",
    "setAlertsWarnings",
    "alerts",
    "setDetectionEnabled",
    "enabled",
    "setStabilizationEnabled",
    "setGunEnabled",
    "setLoadAmmunition",
    "loaded",
    "setStationState",
    "setHomeSw",
    "setStabilizationSw",
    "setAuthorizeSw",
    "setCamActive",
    "setUpSw",
    "setDownSw",
    "setMenuValSw",
    "setFireMode",
    "setSpeedSw",
    "speed",
    "setPanelTemperature",
    "temperature",
    "setStationUpperSensor",
    "setStationLowerSensor",
    "setStationAmmunitionLevel",
    "setStationInput1",
    "setStationInput2",
    "setStationInput3",
    "setEOTemperature",
    "setEOPressure",
    "pressure",
    "setReticleStyle",
    "setDeadManSwitchState",
    "setGimbalAzimuthUpdated",
    "azimuth",
    "setGimbalElevationUpdated",
    "elevation"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDataModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  290,    2, 0x06,    1 /* Public */,
       3,    1,  291,    2, 0x06,    2 /* Public */,
       6,    1,  294,    2, 0x06,    4 /* Public */,
       8,    1,  297,    2, 0x06,    6 /* Public */,
       9,    1,  300,    2, 0x06,    8 /* Public */,
      10,    1,  303,    2, 0x06,   10 /* Public */,
      12,    1,  306,    2, 0x06,   12 /* Public */,
      14,    1,  309,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    1,  312,    2, 0x0a,   16 /* Public */,
      16,    1,  315,    2, 0x0a,   18 /* Public */,
      17,    1,  318,    2, 0x0a,   20 /* Public */,
      19,    3,  321,    2, 0x0a,   22 /* Public */,
      23,    1,  328,    2, 0x0a,   26 /* Public */,
      25,    1,  331,    2, 0x0a,   28 /* Public */,
      27,    1,  334,    2, 0x0a,   30 /* Public */,
      29,    1,  337,    2, 0x0a,   32 /* Public */,
      31,    1,  340,    2, 0x0a,   34 /* Public */,
      33,    1,  343,    2, 0x0a,   36 /* Public */,
      35,    1,  346,    2, 0x0a,   38 /* Public */,
      37,    1,  349,    2, 0x0a,   40 /* Public */,
      39,    1,  352,    2, 0x0a,   42 /* Public */,
      40,    1,  355,    2, 0x0a,   44 /* Public */,
      41,    1,  358,    2, 0x0a,   46 /* Public */,
      43,    1,  361,    2, 0x0a,   48 /* Public */,
      44,    1,  364,    2, 0x0a,   50 /* Public */,
      45,    1,  367,    2, 0x0a,   52 /* Public */,
      46,    1,  370,    2, 0x0a,   54 /* Public */,
      47,    1,  373,    2, 0x0a,   56 /* Public */,
      48,    1,  376,    2, 0x0a,   58 /* Public */,
      49,    1,  379,    2, 0x0a,   60 /* Public */,
      50,    1,  382,    2, 0x0a,   62 /* Public */,
      51,    1,  385,    2, 0x0a,   64 /* Public */,
      52,    1,  388,    2, 0x0a,   66 /* Public */,
      54,    1,  391,    2, 0x0a,   68 /* Public */,
      56,    1,  394,    2, 0x0a,   70 /* Public */,
      57,    1,  397,    2, 0x0a,   72 /* Public */,
      58,    1,  400,    2, 0x0a,   74 /* Public */,
      59,    1,  403,    2, 0x0a,   76 /* Public */,
      60,    1,  406,    2, 0x0a,   78 /* Public */,
      61,    1,  409,    2, 0x0a,   80 /* Public */,
      62,    1,  412,    2, 0x0a,   82 /* Public */,
      63,    1,  415,    2, 0x0a,   84 /* Public */,
      65,    1,  418,    2, 0x0a,   86 /* Public */,
      66,    1,  421,    2, 0x0a,   88 /* Public */,
      67,    1,  424,    2, 0x0a,   90 /* Public */,
      69,    1,  427,    2, 0x0a,   92 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,    5,
    QMetaType::Void, QMetaType::Bool,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   20,   21,   22,
    QMetaType::Void, QMetaType::QPointF,   24,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QDateTime,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   42,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 13,    5,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Int,   64,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Double,   68,
    QMetaType::Void, QMetaType::Double,   70,

       0        // eod
};

Q_CONSTINIT const QMetaObject DataModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSDataModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDataModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSDataModelENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DataModel, std::true_type>,
        // method 'dataModelUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'operationalStateModeChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const OperationalMode &, std::false_type>,
        // method 'upSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'downSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'menuValSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'reticleStyleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'fireModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<FireMode, std::false_type>,
        // method 'deadManSwitchStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setOperationalStateMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const OperationalMode &, std::false_type>,
        // method 'setMotionMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setLRFDistance'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'setGyroOrientation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'setCrosshairPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'setWeaponSystemStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setTargetInformation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setSystemTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        // method 'setGPSCoordinates'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setSensorReadings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setAlertsWarnings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setDetectionEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStabilizationEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setGunEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setLoadAmmunition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStationState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setHomeSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStabilizationSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setAuthorizeSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setCamActive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setUpSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setDownSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setMenuValSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setFireMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<FireMode, std::false_type>,
        // method 'setSpeedSw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setPanelTemperature'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setStationUpperSensor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStationLowerSensor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStationAmmunitionLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStationInput1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStationInput2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setStationInput3'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setEOTemperature'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setEOPressure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setReticleStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setDeadManSwitchState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setGimbalAzimuthUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'setGimbalElevationUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void DataModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataModelUpdated(); break;
        case 1: _t->operationalStateModeChange((*reinterpret_cast< std::add_pointer_t<OperationalMode>>(_a[1]))); break;
        case 2: _t->upSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->downSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->menuValSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->reticleStyleChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->fireModeChanged((*reinterpret_cast< std::add_pointer_t<FireMode>>(_a[1]))); break;
        case 7: _t->deadManSwitchStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->setOperationalStateMode((*reinterpret_cast< std::add_pointer_t<OperationalMode>>(_a[1]))); break;
        case 9: _t->setMotionMode((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->setLRFDistance((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 11: _t->setGyroOrientation((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 12: _t->setCrosshairPosition((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 13: _t->setWeaponSystemStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->setTargetInformation((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->setSystemTime((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1]))); break;
        case 16: _t->setGPSCoordinates((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->setSensorReadings((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->setAlertsWarnings((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->setDetectionEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 20: _t->setStabilizationEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->setGunEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->setLoadAmmunition((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 23: _t->setStationState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 24: _t->setHomeSw((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 25: _t->setStabilizationSw((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 26: _t->setAuthorizeSw((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 27: _t->setCamActive((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 28: _t->setUpSw((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 29: _t->setDownSw((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 30: _t->setMenuValSw((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 31: _t->setFireMode((*reinterpret_cast< std::add_pointer_t<FireMode>>(_a[1]))); break;
        case 32: _t->setSpeedSw((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 33: _t->setPanelTemperature((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 34: _t->setStationUpperSensor((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 35: _t->setStationLowerSensor((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 36: _t->setStationAmmunitionLevel((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 37: _t->setStationInput1((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 38: _t->setStationInput2((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 39: _t->setStationInput3((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 40: _t->setEOTemperature((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 41: _t->setEOPressure((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 42: _t->setReticleStyle((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 43: _t->setDeadManSwitchState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 44: _t->setGimbalAzimuthUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 45: _t->setGimbalElevationUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataModel::*)();
            if (_t _q_method = &DataModel::dataModelUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(const OperationalMode & );
            if (_t _q_method = &DataModel::operationalStateModeChange; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(bool );
            if (_t _q_method = &DataModel::upSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(bool );
            if (_t _q_method = &DataModel::downSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(bool );
            if (_t _q_method = &DataModel::menuValSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(const QString & );
            if (_t _q_method = &DataModel::reticleStyleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(FireMode );
            if (_t _q_method = &DataModel::fireModeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DataModel::*)(bool );
            if (_t _q_method = &DataModel::deadManSwitchStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *DataModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDataModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 46;
    }
    return _id;
}

// SIGNAL 0
void DataModel::dataModelUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DataModel::operationalStateModeChange(const OperationalMode & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataModel::upSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataModel::downSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataModel::menuValSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DataModel::reticleStyleChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DataModel::fireModeChanged(FireMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DataModel::deadManSwitchStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
