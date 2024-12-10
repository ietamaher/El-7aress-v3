/****************************************************************************
** Meta object code from reading C++ file 'lrfinterface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/sensor/lrfinterface.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lrfinterface.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSLRFInterfaceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSLRFInterfaceENDCLASS = QtMocHelpers::stringData(
    "LRFInterface",
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
    "statusChanged",
    "connected",
    "sendSelfCheck",
    "sendSingleRanging",
    "sendContinuousRanging",
    "stopRanging",
    "setFrequency",
    "querySettingValue",
    "queryAccumulatedLaserCount",
    "processIncomingData",
    "handleSerialError",
    "QSerialPort::SerialPortError",
    "attemptReconnection"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSLRFInterfaceENDCLASS_t {
    uint offsetsAndSizes[72];
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
    char stringdata23[14];
    char stringdata24[10];
    char stringdata25[14];
    char stringdata26[18];
    char stringdata27[22];
    char stringdata28[12];
    char stringdata29[13];
    char stringdata30[18];
    char stringdata31[27];
    char stringdata32[20];
    char stringdata33[18];
    char stringdata34[29];
    char stringdata35[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSLRFInterfaceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSLRFInterfaceENDCLASS_t qt_meta_stringdata_CLASSLRFInterfaceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "LRFInterface"
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
        QT_MOC_LITERAL(301, 13),  // "statusChanged"
        QT_MOC_LITERAL(315, 9),  // "connected"
        QT_MOC_LITERAL(325, 13),  // "sendSelfCheck"
        QT_MOC_LITERAL(339, 17),  // "sendSingleRanging"
        QT_MOC_LITERAL(357, 21),  // "sendContinuousRanging"
        QT_MOC_LITERAL(379, 11),  // "stopRanging"
        QT_MOC_LITERAL(391, 12),  // "setFrequency"
        QT_MOC_LITERAL(404, 17),  // "querySettingValue"
        QT_MOC_LITERAL(422, 26),  // "queryAccumulatedLaserCount"
        QT_MOC_LITERAL(449, 19),  // "processIncomingData"
        QT_MOC_LITERAL(469, 17),  // "handleSerialError"
        QT_MOC_LITERAL(487, 28),  // "QSerialPort::SerialPortError"
        QT_MOC_LITERAL(516, 19)   // "attemptReconnection"
    },
    "LRFInterface",
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
    "statusChanged",
    "connected",
    "sendSelfCheck",
    "sendSingleRanging",
    "sendContinuousRanging",
    "stopRanging",
    "setFrequency",
    "querySettingValue",
    "queryAccumulatedLaserCount",
    "processIncomingData",
    "handleSerialError",
    "QSerialPort::SerialPortError",
    "attemptReconnection"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLRFInterfaceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  116,    2, 0x06,    1 /* Public */,
       4,    4,  119,    2, 0x06,    3 /* Public */,
       9,    1,  128,    2, 0x06,    8 /* Public */,
      11,    1,  131,    2, 0x06,   10 /* Public */,
      13,    4,  134,    2, 0x06,   12 /* Public */,
      18,    4,  143,    2, 0x06,   17 /* Public */,
      23,    1,  152,    2, 0x06,   22 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      25,    0,  155,    2, 0x0a,   24 /* Public */,
      26,    0,  156,    2, 0x0a,   25 /* Public */,
      27,    0,  157,    2, 0x0a,   26 /* Public */,
      28,    0,  158,    2, 0x0a,   27 /* Public */,
      29,    1,  159,    2, 0x0a,   28 /* Public */,
      30,    0,  162,    2, 0x0a,   30 /* Public */,
      31,    0,  163,    2, 0x0a,   31 /* Public */,
      32,    0,  164,    2, 0x08,   32 /* Private */,
      33,    1,  165,    2, 0x08,   33 /* Private */,
      35,    0,  168,    2, 0x08,   35 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   14,   15,   16,   17,
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::Bool,   24,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 34,    3,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject LRFInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSLRFInterfaceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLRFInterfaceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLRFInterfaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LRFInterface, std::true_type>,
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
        // method 'statusChanged'
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
        // method 'processIncomingData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSerialError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>,
        // method 'attemptReconnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LRFInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LRFInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->frequencySet((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 2: _t->settingValueReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 3: _t->laserCountReceived((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 4: _t->selfCheckResult((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 5: _t->rangingDataReceived((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<quint8>>(_a[4]))); break;
        case 6: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->sendSelfCheck(); break;
        case 8: _t->sendSingleRanging(); break;
        case 9: _t->sendContinuousRanging(); break;
        case 10: _t->stopRanging(); break;
        case 11: _t->setFrequency((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->querySettingValue(); break;
        case 13: _t->queryAccumulatedLaserCount(); break;
        case 14: _t->processIncomingData(); break;
        case 15: _t->handleSerialError((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        case 16: _t->attemptReconnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LRFInterface::*)(const QString & );
            if (_t _q_method = &LRFInterface::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LRFInterface::*)(quint8 , quint8 , quint8 , quint8 );
            if (_t _q_method = &LRFInterface::frequencySet; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LRFInterface::*)(quint8 );
            if (_t _q_method = &LRFInterface::settingValueReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LRFInterface::*)(quint32 );
            if (_t _q_method = &LRFInterface::laserCountReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LRFInterface::*)(quint8 , quint8 , quint8 , quint8 );
            if (_t _q_method = &LRFInterface::selfCheckResult; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LRFInterface::*)(quint8 , quint16 , quint8 , quint8 );
            if (_t _q_method = &LRFInterface::rangingDataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LRFInterface::*)(bool );
            if (_t _q_method = &LRFInterface::statusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *LRFInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LRFInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLRFInterfaceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LRFInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void LRFInterface::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LRFInterface::frequencySet(quint8 _t1, quint8 _t2, quint8 _t3, quint8 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LRFInterface::settingValueReceived(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LRFInterface::laserCountReceived(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LRFInterface::selfCheckResult(quint8 _t1, quint8 _t2, quint8 _t3, quint8 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LRFInterface::rangingDataReceived(quint8 _t1, quint16 _t2, quint8 _t3, quint8 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LRFInterface::statusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
