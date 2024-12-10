/****************************************************************************
** Meta object code from reading C++ file 'plcremotestationsensorsinterface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/sensor/plcremotestationsensorsinterface.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plcremotestationsensorsinterface.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS = QtMocHelpers::stringData(
    "PLCRemoteStationSensorInterface",
    "logMessage",
    "",
    "message",
    "errorOccurred",
    "error",
    "dataRead",
    "connectionStatusChanged",
    "connected",
    "gunStateChanged",
    "state",
    "loadAmmunitionStateChanged",
    "stationStateChanged",
    "homeSwChanged",
    "stabilizationSwChanged",
    "authorizeSwChanged",
    "camSwChanged",
    "upSwChanged",
    "downSwChanged",
    "menuValSwChanged",
    "speedSwChanged",
    "speed",
    "fireModeStateInputChanged",
    "mode",
    "panelTemperatureChanged",
    "temperature",
    "digitalInputsChanged",
    "QList<bool>",
    "inputs",
    "analogInputsChanged",
    "QList<uint16_t>",
    "maxReconnectionAttemptsReached",
    "readData",
    "writeData",
    "onWriteReady",
    "onStateChanged",
    "QModbusDevice::State",
    "onErrorOccurred",
    "QModbusDevice::Error",
    "handleTimeout",
    "onDigitalInputsReadReady",
    "onAnalogInputsReadReady"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS_t {
    uint offsetsAndSizes[84];
    char stringdata0[32];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[6];
    char stringdata6[9];
    char stringdata7[24];
    char stringdata8[10];
    char stringdata9[16];
    char stringdata10[6];
    char stringdata11[27];
    char stringdata12[20];
    char stringdata13[14];
    char stringdata14[23];
    char stringdata15[19];
    char stringdata16[13];
    char stringdata17[12];
    char stringdata18[14];
    char stringdata19[17];
    char stringdata20[15];
    char stringdata21[6];
    char stringdata22[26];
    char stringdata23[5];
    char stringdata24[24];
    char stringdata25[12];
    char stringdata26[21];
    char stringdata27[12];
    char stringdata28[7];
    char stringdata29[20];
    char stringdata30[16];
    char stringdata31[31];
    char stringdata32[9];
    char stringdata33[10];
    char stringdata34[13];
    char stringdata35[15];
    char stringdata36[21];
    char stringdata37[16];
    char stringdata38[21];
    char stringdata39[14];
    char stringdata40[25];
    char stringdata41[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS_t qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 31),  // "PLCRemoteStationSensorInterface"
        QT_MOC_LITERAL(32, 10),  // "logMessage"
        QT_MOC_LITERAL(43, 0),  // ""
        QT_MOC_LITERAL(44, 7),  // "message"
        QT_MOC_LITERAL(52, 13),  // "errorOccurred"
        QT_MOC_LITERAL(66, 5),  // "error"
        QT_MOC_LITERAL(72, 8),  // "dataRead"
        QT_MOC_LITERAL(81, 23),  // "connectionStatusChanged"
        QT_MOC_LITERAL(105, 9),  // "connected"
        QT_MOC_LITERAL(115, 15),  // "gunStateChanged"
        QT_MOC_LITERAL(131, 5),  // "state"
        QT_MOC_LITERAL(137, 26),  // "loadAmmunitionStateChanged"
        QT_MOC_LITERAL(164, 19),  // "stationStateChanged"
        QT_MOC_LITERAL(184, 13),  // "homeSwChanged"
        QT_MOC_LITERAL(198, 22),  // "stabilizationSwChanged"
        QT_MOC_LITERAL(221, 18),  // "authorizeSwChanged"
        QT_MOC_LITERAL(240, 12),  // "camSwChanged"
        QT_MOC_LITERAL(253, 11),  // "upSwChanged"
        QT_MOC_LITERAL(265, 13),  // "downSwChanged"
        QT_MOC_LITERAL(279, 16),  // "menuValSwChanged"
        QT_MOC_LITERAL(296, 14),  // "speedSwChanged"
        QT_MOC_LITERAL(311, 5),  // "speed"
        QT_MOC_LITERAL(317, 25),  // "fireModeStateInputChanged"
        QT_MOC_LITERAL(343, 4),  // "mode"
        QT_MOC_LITERAL(348, 23),  // "panelTemperatureChanged"
        QT_MOC_LITERAL(372, 11),  // "temperature"
        QT_MOC_LITERAL(384, 20),  // "digitalInputsChanged"
        QT_MOC_LITERAL(405, 11),  // "QList<bool>"
        QT_MOC_LITERAL(417, 6),  // "inputs"
        QT_MOC_LITERAL(424, 19),  // "analogInputsChanged"
        QT_MOC_LITERAL(444, 15),  // "QList<uint16_t>"
        QT_MOC_LITERAL(460, 30),  // "maxReconnectionAttemptsReached"
        QT_MOC_LITERAL(491, 8),  // "readData"
        QT_MOC_LITERAL(500, 9),  // "writeData"
        QT_MOC_LITERAL(510, 12),  // "onWriteReady"
        QT_MOC_LITERAL(523, 14),  // "onStateChanged"
        QT_MOC_LITERAL(538, 20),  // "QModbusDevice::State"
        QT_MOC_LITERAL(559, 15),  // "onErrorOccurred"
        QT_MOC_LITERAL(575, 20),  // "QModbusDevice::Error"
        QT_MOC_LITERAL(596, 13),  // "handleTimeout"
        QT_MOC_LITERAL(610, 24),  // "onDigitalInputsReadReady"
        QT_MOC_LITERAL(635, 23)   // "onAnalogInputsReadReady"
    },
    "PLCRemoteStationSensorInterface",
    "logMessage",
    "",
    "message",
    "errorOccurred",
    "error",
    "dataRead",
    "connectionStatusChanged",
    "connected",
    "gunStateChanged",
    "state",
    "loadAmmunitionStateChanged",
    "stationStateChanged",
    "homeSwChanged",
    "stabilizationSwChanged",
    "authorizeSwChanged",
    "camSwChanged",
    "upSwChanged",
    "downSwChanged",
    "menuValSwChanged",
    "speedSwChanged",
    "speed",
    "fireModeStateInputChanged",
    "mode",
    "panelTemperatureChanged",
    "temperature",
    "digitalInputsChanged",
    "QList<bool>",
    "inputs",
    "analogInputsChanged",
    "QList<uint16_t>",
    "maxReconnectionAttemptsReached",
    "readData",
    "writeData",
    "onWriteReady",
    "onStateChanged",
    "QModbusDevice::State",
    "onErrorOccurred",
    "QModbusDevice::Error",
    "handleTimeout",
    "onDigitalInputsReadReady",
    "onAnalogInputsReadReady"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPLCRemoteStationSensorInterfaceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  182,    2, 0x06,    1 /* Public */,
       4,    1,  185,    2, 0x06,    3 /* Public */,
       6,    0,  188,    2, 0x06,    5 /* Public */,
       7,    1,  189,    2, 0x06,    6 /* Public */,
       9,    1,  192,    2, 0x06,    8 /* Public */,
      11,    1,  195,    2, 0x06,   10 /* Public */,
      12,    1,  198,    2, 0x06,   12 /* Public */,
      13,    1,  201,    2, 0x06,   14 /* Public */,
      14,    1,  204,    2, 0x06,   16 /* Public */,
      15,    1,  207,    2, 0x06,   18 /* Public */,
      16,    1,  210,    2, 0x06,   20 /* Public */,
      17,    1,  213,    2, 0x06,   22 /* Public */,
      18,    1,  216,    2, 0x06,   24 /* Public */,
      19,    1,  219,    2, 0x06,   26 /* Public */,
      20,    1,  222,    2, 0x06,   28 /* Public */,
      22,    1,  225,    2, 0x06,   30 /* Public */,
      24,    1,  228,    2, 0x06,   32 /* Public */,
      26,    1,  231,    2, 0x06,   34 /* Public */,
      29,    1,  234,    2, 0x06,   36 /* Public */,
      31,    0,  237,    2, 0x06,   38 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      32,    0,  238,    2, 0x0a,   39 /* Public */,
      33,    0,  239,    2, 0x0a,   40 /* Public */,
      34,    0,  240,    2, 0x08,   41 /* Private */,
      35,    1,  241,    2, 0x08,   42 /* Private */,
      37,    1,  244,    2, 0x08,   44 /* Private */,
      39,    0,  247,    2, 0x08,   46 /* Private */,
      40,    0,  248,    2, 0x08,   47 /* Private */,
      41,    0,  249,    2, 0x08,   48 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, 0x80000000 | 30,   28,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 36,   10,
    QMetaType::Void, 0x80000000 | 38,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject PLCRemoteStationSensorInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPLCRemoteStationSensorInterfaceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PLCRemoteStationSensorInterface, std::true_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'dataRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'gunStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'loadAmmunitionStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stationStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'homeSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stabilizationSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'authorizeSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'camSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'upSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'downSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'menuValSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'speedSwChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fireModeStateInputChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'panelTemperatureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'digitalInputsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<bool> &, std::false_type>,
        // method 'analogInputsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<uint16_t> &, std::false_type>,
        // method 'maxReconnectionAttemptsReached'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'writeData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onWriteReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModbusDevice::State, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModbusDevice::Error, std::false_type>,
        // method 'handleTimeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDigitalInputsReadReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAnalogInputsReadReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void PLCRemoteStationSensorInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PLCRemoteStationSensorInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->dataRead(); break;
        case 3: _t->connectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->gunStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->loadAmmunitionStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->stationStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->homeSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->stabilizationSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->authorizeSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->camSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->upSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->downSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->menuValSwChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->speedSwChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->fireModeStateInputChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->panelTemperatureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->digitalInputsChanged((*reinterpret_cast< std::add_pointer_t<QList<bool>>>(_a[1]))); break;
        case 18: _t->analogInputsChanged((*reinterpret_cast< std::add_pointer_t<QList<uint16_t>>>(_a[1]))); break;
        case 19: _t->maxReconnectionAttemptsReached(); break;
        case 20: _t->readData(); break;
        case 21: _t->writeData(); break;
        case 22: _t->onWriteReady(); break;
        case 23: _t->onStateChanged((*reinterpret_cast< std::add_pointer_t<QModbusDevice::State>>(_a[1]))); break;
        case 24: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QModbusDevice::Error>>(_a[1]))); break;
        case 25: _t->handleTimeout(); break;
        case 26: _t->onDigitalInputsReadReady(); break;
        case 27: _t->onAnalogInputsReadReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<bool> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(const QString & );
            if (_t _q_method = &PLCRemoteStationSensorInterface::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(const QString & );
            if (_t _q_method = &PLCRemoteStationSensorInterface::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)();
            if (_t _q_method = &PLCRemoteStationSensorInterface::dataRead; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::connectionStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::gunStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::loadAmmunitionStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::stationStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::homeSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::stabilizationSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::authorizeSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::camSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::upSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::downSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCRemoteStationSensorInterface::menuValSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(int );
            if (_t _q_method = &PLCRemoteStationSensorInterface::speedSwChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(int );
            if (_t _q_method = &PLCRemoteStationSensorInterface::fireModeStateInputChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(int );
            if (_t _q_method = &PLCRemoteStationSensorInterface::panelTemperatureChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(const QVector<bool> & );
            if (_t _q_method = &PLCRemoteStationSensorInterface::digitalInputsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)(const QVector<uint16_t> & );
            if (_t _q_method = &PLCRemoteStationSensorInterface::analogInputsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (PLCRemoteStationSensorInterface::*)();
            if (_t _q_method = &PLCRemoteStationSensorInterface::maxReconnectionAttemptsReached; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 19;
                return;
            }
        }
    }
}

const QMetaObject *PLCRemoteStationSensorInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLCRemoteStationSensorInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPLCRemoteStationSensorInterfaceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PLCRemoteStationSensorInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void PLCRemoteStationSensorInterface::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PLCRemoteStationSensorInterface::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PLCRemoteStationSensorInterface::dataRead()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PLCRemoteStationSensorInterface::connectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PLCRemoteStationSensorInterface::gunStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PLCRemoteStationSensorInterface::loadAmmunitionStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PLCRemoteStationSensorInterface::stationStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PLCRemoteStationSensorInterface::homeSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PLCRemoteStationSensorInterface::stabilizationSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PLCRemoteStationSensorInterface::authorizeSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PLCRemoteStationSensorInterface::camSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PLCRemoteStationSensorInterface::upSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void PLCRemoteStationSensorInterface::downSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void PLCRemoteStationSensorInterface::menuValSwChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PLCRemoteStationSensorInterface::speedSwChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void PLCRemoteStationSensorInterface::fireModeStateInputChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void PLCRemoteStationSensorInterface::panelTemperatureChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void PLCRemoteStationSensorInterface::digitalInputsChanged(const QVector<bool> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void PLCRemoteStationSensorInterface::analogInputsChanged(const QVector<uint16_t> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void PLCRemoteStationSensorInterface::maxReconnectionAttemptsReached()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}
QT_WARNING_POP
