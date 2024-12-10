/****************************************************************************
** Meta object code from reading C++ file 'plcstationdriver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/comm/plcstationdriver.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plcstationdriver.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPLCStationDriverENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSPLCStationDriverENDCLASS = QtMocHelpers::stringData(
    "PLCStationDriver",
    "logMessage",
    "",
    "message",
    "errorOccurred",
    "error",
    "connectionStatusChanged",
    "connected",
    "registersRead",
    "address",
    "QList<uint16_t>",
    "values",
    "inputBitsRead",
    "QList<uint8_t>",
    "bits",
    "inputRegistersRead",
    "writeCompleted",
    "performPeriodicTasks",
    "onStateChanged",
    "QModbusDevice::State",
    "state",
    "onErrorOccurred",
    "QModbusDevice::Error",
    "onReadReady",
    "onWriteFinished",
    "onWriteReady"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPLCStationDriverENDCLASS_t {
    uint offsetsAndSizes[52];
    char stringdata0[17];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[6];
    char stringdata6[24];
    char stringdata7[10];
    char stringdata8[14];
    char stringdata9[8];
    char stringdata10[16];
    char stringdata11[7];
    char stringdata12[14];
    char stringdata13[15];
    char stringdata14[5];
    char stringdata15[19];
    char stringdata16[15];
    char stringdata17[21];
    char stringdata18[15];
    char stringdata19[21];
    char stringdata20[6];
    char stringdata21[16];
    char stringdata22[21];
    char stringdata23[12];
    char stringdata24[16];
    char stringdata25[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPLCStationDriverENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPLCStationDriverENDCLASS_t qt_meta_stringdata_CLASSPLCStationDriverENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "PLCStationDriver"
        QT_MOC_LITERAL(17, 10),  // "logMessage"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 7),  // "message"
        QT_MOC_LITERAL(37, 13),  // "errorOccurred"
        QT_MOC_LITERAL(51, 5),  // "error"
        QT_MOC_LITERAL(57, 23),  // "connectionStatusChanged"
        QT_MOC_LITERAL(81, 9),  // "connected"
        QT_MOC_LITERAL(91, 13),  // "registersRead"
        QT_MOC_LITERAL(105, 7),  // "address"
        QT_MOC_LITERAL(113, 15),  // "QList<uint16_t>"
        QT_MOC_LITERAL(129, 6),  // "values"
        QT_MOC_LITERAL(136, 13),  // "inputBitsRead"
        QT_MOC_LITERAL(150, 14),  // "QList<uint8_t>"
        QT_MOC_LITERAL(165, 4),  // "bits"
        QT_MOC_LITERAL(170, 18),  // "inputRegistersRead"
        QT_MOC_LITERAL(189, 14),  // "writeCompleted"
        QT_MOC_LITERAL(204, 20),  // "performPeriodicTasks"
        QT_MOC_LITERAL(225, 14),  // "onStateChanged"
        QT_MOC_LITERAL(240, 20),  // "QModbusDevice::State"
        QT_MOC_LITERAL(261, 5),  // "state"
        QT_MOC_LITERAL(267, 15),  // "onErrorOccurred"
        QT_MOC_LITERAL(283, 20),  // "QModbusDevice::Error"
        QT_MOC_LITERAL(304, 11),  // "onReadReady"
        QT_MOC_LITERAL(316, 15),  // "onWriteFinished"
        QT_MOC_LITERAL(332, 12)   // "onWriteReady"
    },
    "PLCStationDriver",
    "logMessage",
    "",
    "message",
    "errorOccurred",
    "error",
    "connectionStatusChanged",
    "connected",
    "registersRead",
    "address",
    "QList<uint16_t>",
    "values",
    "inputBitsRead",
    "QList<uint8_t>",
    "bits",
    "inputRegistersRead",
    "writeCompleted",
    "performPeriodicTasks",
    "onStateChanged",
    "QModbusDevice::State",
    "state",
    "onErrorOccurred",
    "QModbusDevice::Error",
    "onReadReady",
    "onWriteFinished",
    "onWriteReady"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPLCStationDriverENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,    1 /* Public */,
       4,    1,   95,    2, 0x06,    3 /* Public */,
       6,    1,   98,    2, 0x06,    5 /* Public */,
       8,    2,  101,    2, 0x06,    7 /* Public */,
      12,    2,  106,    2, 0x06,   10 /* Public */,
      15,    2,  111,    2, 0x06,   13 /* Public */,
      16,    1,  116,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    0,  119,    2, 0x08,   18 /* Private */,
      18,    1,  120,    2, 0x08,   19 /* Private */,
      21,    1,  123,    2, 0x08,   21 /* Private */,
      23,    0,  126,    2, 0x08,   23 /* Private */,
      24,    0,  127,    2, 0x08,   24 /* Private */,
      25,    0,  128,    2, 0x08,   25 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,    9,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 22,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject PLCStationDriver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPLCStationDriverENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPLCStationDriverENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPLCStationDriverENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PLCStationDriver, std::true_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'connectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'registersRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<uint16_t> &, std::false_type>,
        // method 'inputBitsRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<uint8_t> &, std::false_type>,
        // method 'inputRegistersRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<uint16_t> &, std::false_type>,
        // method 'writeCompleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'performPeriodicTasks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModbusDevice::State, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModbusDevice::Error, std::false_type>,
        // method 'onReadReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onWriteFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onWriteReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void PLCStationDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PLCStationDriver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->connectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->registersRead((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<uint16_t>>>(_a[2]))); break;
        case 4: _t->inputBitsRead((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<uint8_t>>>(_a[2]))); break;
        case 5: _t->inputRegistersRead((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<uint16_t>>>(_a[2]))); break;
        case 6: _t->writeCompleted((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->performPeriodicTasks(); break;
        case 8: _t->onStateChanged((*reinterpret_cast< std::add_pointer_t<QModbusDevice::State>>(_a[1]))); break;
        case 9: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QModbusDevice::Error>>(_a[1]))); break;
        case 10: _t->onReadReady(); break;
        case 11: _t->onWriteFinished(); break;
        case 12: _t->onWriteReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PLCStationDriver::*)(const QString & );
            if (_t _q_method = &PLCStationDriver::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PLCStationDriver::*)(const QString & );
            if (_t _q_method = &PLCStationDriver::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PLCStationDriver::*)(bool );
            if (_t _q_method = &PLCStationDriver::connectionStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PLCStationDriver::*)(int , const QVector<uint16_t> & );
            if (_t _q_method = &PLCStationDriver::registersRead; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PLCStationDriver::*)(int , const QVector<uint8_t> & );
            if (_t _q_method = &PLCStationDriver::inputBitsRead; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PLCStationDriver::*)(int , const QVector<uint16_t> & );
            if (_t _q_method = &PLCStationDriver::inputRegistersRead; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PLCStationDriver::*)(int );
            if (_t _q_method = &PLCStationDriver::writeCompleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *PLCStationDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLCStationDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPLCStationDriverENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PLCStationDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PLCStationDriver::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PLCStationDriver::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PLCStationDriver::connectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PLCStationDriver::registersRead(int _t1, const QVector<uint16_t> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PLCStationDriver::inputBitsRead(int _t1, const QVector<uint8_t> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PLCStationDriver::inputRegistersRead(int _t1, const QVector<uint16_t> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PLCStationDriver::writeCompleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
