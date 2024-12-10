/****************************************************************************
** Meta object code from reading C++ file 'plcstationsensorsinterface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/sensor/plcstationsensorsinterface.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plcstationsensorsinterface.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS = QtMocHelpers::stringData(
    "PLCStationSensorInterface",
    "logMessage",
    "",
    "message",
    "errorOccurred",
    "stationUpperSensorStateChanged",
    "state",
    "stationLowerSensorStateChanged",
    "stationAmmunitionLevelChanged",
    "stationInput1Changed",
    "stationInput2Changed",
    "stationInput3Changed",
    "eoTemperatureChanged",
    "temperature",
    "eoPressureChanged",
    "pressure",
    "onInputBitsRead",
    "address",
    "QList<uint8_t>",
    "bits",
    "onInputRegistersRead",
    "QList<uint16_t>",
    "values",
    "onErrorOccurred"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS_t {
    uint offsetsAndSizes[48];
    char stringdata0[26];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[31];
    char stringdata6[6];
    char stringdata7[31];
    char stringdata8[30];
    char stringdata9[21];
    char stringdata10[21];
    char stringdata11[21];
    char stringdata12[21];
    char stringdata13[12];
    char stringdata14[18];
    char stringdata15[9];
    char stringdata16[16];
    char stringdata17[8];
    char stringdata18[15];
    char stringdata19[5];
    char stringdata20[21];
    char stringdata21[16];
    char stringdata22[7];
    char stringdata23[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS_t qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 25),  // "PLCStationSensorInterface"
        QT_MOC_LITERAL(26, 10),  // "logMessage"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 7),  // "message"
        QT_MOC_LITERAL(46, 13),  // "errorOccurred"
        QT_MOC_LITERAL(60, 30),  // "stationUpperSensorStateChanged"
        QT_MOC_LITERAL(91, 5),  // "state"
        QT_MOC_LITERAL(97, 30),  // "stationLowerSensorStateChanged"
        QT_MOC_LITERAL(128, 29),  // "stationAmmunitionLevelChanged"
        QT_MOC_LITERAL(158, 20),  // "stationInput1Changed"
        QT_MOC_LITERAL(179, 20),  // "stationInput2Changed"
        QT_MOC_LITERAL(200, 20),  // "stationInput3Changed"
        QT_MOC_LITERAL(221, 20),  // "eoTemperatureChanged"
        QT_MOC_LITERAL(242, 11),  // "temperature"
        QT_MOC_LITERAL(254, 17),  // "eoPressureChanged"
        QT_MOC_LITERAL(272, 8),  // "pressure"
        QT_MOC_LITERAL(281, 15),  // "onInputBitsRead"
        QT_MOC_LITERAL(297, 7),  // "address"
        QT_MOC_LITERAL(305, 14),  // "QList<uint8_t>"
        QT_MOC_LITERAL(320, 4),  // "bits"
        QT_MOC_LITERAL(325, 20),  // "onInputRegistersRead"
        QT_MOC_LITERAL(346, 15),  // "QList<uint16_t>"
        QT_MOC_LITERAL(362, 6),  // "values"
        QT_MOC_LITERAL(369, 15)   // "onErrorOccurred"
    },
    "PLCStationSensorInterface",
    "logMessage",
    "",
    "message",
    "errorOccurred",
    "stationUpperSensorStateChanged",
    "state",
    "stationLowerSensorStateChanged",
    "stationAmmunitionLevelChanged",
    "stationInput1Changed",
    "stationInput2Changed",
    "stationInput3Changed",
    "eoTemperatureChanged",
    "temperature",
    "eoPressureChanged",
    "pressure",
    "onInputBitsRead",
    "address",
    "QList<uint8_t>",
    "bits",
    "onInputRegistersRead",
    "QList<uint16_t>",
    "values",
    "onErrorOccurred"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPLCStationSensorInterfaceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,    1 /* Public */,
       4,    1,   95,    2, 0x06,    3 /* Public */,
       5,    1,   98,    2, 0x06,    5 /* Public */,
       7,    1,  101,    2, 0x06,    7 /* Public */,
       8,    1,  104,    2, 0x06,    9 /* Public */,
       9,    1,  107,    2, 0x06,   11 /* Public */,
      10,    1,  110,    2, 0x06,   13 /* Public */,
      11,    1,  113,    2, 0x06,   15 /* Public */,
      12,    1,  116,    2, 0x06,   17 /* Public */,
      14,    1,  119,    2, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    2,  122,    2, 0x08,   21 /* Private */,
      20,    2,  127,    2, 0x08,   24 /* Private */,
      23,    1,  132,    2, 0x08,   27 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 18,   17,   19,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21,   17,   22,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject PLCStationSensorInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPLCStationSensorInterfaceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PLCStationSensorInterface, std::true_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'stationUpperSensorStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stationLowerSensorStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stationAmmunitionLevelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stationInput1Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stationInput2Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stationInput3Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'eoTemperatureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'eoPressureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onInputBitsRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<uint8_t> &, std::false_type>,
        // method 'onInputRegistersRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<uint16_t> &, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void PLCStationSensorInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PLCStationSensorInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->stationUpperSensorStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->stationLowerSensorStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->stationAmmunitionLevelChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->stationInput1Changed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->stationInput2Changed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->stationInput3Changed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->eoTemperatureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->eoPressureChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onInputBitsRead((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<uint8_t>>>(_a[2]))); break;
        case 11: _t->onInputRegistersRead((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<uint16_t>>>(_a[2]))); break;
        case 12: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PLCStationSensorInterface::*)(const QString & );
            if (_t _q_method = &PLCStationSensorInterface::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(const QString & );
            if (_t _q_method = &PLCStationSensorInterface::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCStationSensorInterface::stationUpperSensorStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCStationSensorInterface::stationLowerSensorStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCStationSensorInterface::stationAmmunitionLevelChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCStationSensorInterface::stationInput1Changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCStationSensorInterface::stationInput2Changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(bool );
            if (_t _q_method = &PLCStationSensorInterface::stationInput3Changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(int );
            if (_t _q_method = &PLCStationSensorInterface::eoTemperatureChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PLCStationSensorInterface::*)(int );
            if (_t _q_method = &PLCStationSensorInterface::eoPressureChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *PLCStationSensorInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLCStationSensorInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPLCStationSensorInterfaceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PLCStationSensorInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void PLCStationSensorInterface::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PLCStationSensorInterface::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PLCStationSensorInterface::stationUpperSensorStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PLCStationSensorInterface::stationLowerSensorStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PLCStationSensorInterface::stationAmmunitionLevelChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PLCStationSensorInterface::stationInput1Changed(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PLCStationSensorInterface::stationInput2Changed(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PLCStationSensorInterface::stationInput3Changed(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PLCStationSensorInterface::eoTemperatureChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PLCStationSensorInterface::eoPressureChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
