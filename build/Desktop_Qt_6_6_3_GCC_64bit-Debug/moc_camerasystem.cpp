/****************************************************************************
** Meta object code from reading C++ file 'camerasystem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/camera/camerasystem.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerasystem.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSCameraSystemENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCameraSystemENDCLASS = QtMocHelpers::stringData(
    "CameraSystem",
    "errorOccurred",
    "",
    "error",
    "newFrameAvailable",
    "frameData",
    "width",
    "height",
    "selectedTrackLost",
    "trackId",
    "trackedIdsUpdated",
    "QSet<int>",
    "ids",
    "targetPositionUpdated",
    "azimuth",
    "elevation",
    "dayCameraInterfaceStatusChanged",
    "isConnected",
    "nightCameraInterfaceStatusChanged",
    "lensInterfaceStatusChanged",
    "lensResponseReceived",
    "response",
    "dayResponseReceived",
    "nightResponseReceived",
    "onNewFrameAvailable",
    "onSelectedTrackLost",
    "onTrackedIdsUpdated",
    "trackIds",
    "onDayCameraInterfaceStatusChanged",
    "onNightCameraInterfaceStatusChanged",
    "onLensInterfaceStatusChanged",
    "onDayInterfaceResponseReceived",
    "onNightInterfaceResponseReceived",
    "onLensResponseReceived",
    "onErrorOccurred",
    "onTargetPositionUpdated"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCameraSystemENDCLASS_t {
    uint offsetsAndSizes[72];
    char stringdata0[13];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[18];
    char stringdata5[10];
    char stringdata6[6];
    char stringdata7[7];
    char stringdata8[18];
    char stringdata9[8];
    char stringdata10[18];
    char stringdata11[10];
    char stringdata12[4];
    char stringdata13[22];
    char stringdata14[8];
    char stringdata15[10];
    char stringdata16[32];
    char stringdata17[12];
    char stringdata18[34];
    char stringdata19[27];
    char stringdata20[21];
    char stringdata21[9];
    char stringdata22[20];
    char stringdata23[22];
    char stringdata24[20];
    char stringdata25[20];
    char stringdata26[20];
    char stringdata27[9];
    char stringdata28[34];
    char stringdata29[36];
    char stringdata30[29];
    char stringdata31[31];
    char stringdata32[33];
    char stringdata33[23];
    char stringdata34[16];
    char stringdata35[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCameraSystemENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCameraSystemENDCLASS_t qt_meta_stringdata_CLASSCameraSystemENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "CameraSystem"
        QT_MOC_LITERAL(13, 13),  // "errorOccurred"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 5),  // "error"
        QT_MOC_LITERAL(34, 17),  // "newFrameAvailable"
        QT_MOC_LITERAL(52, 9),  // "frameData"
        QT_MOC_LITERAL(62, 5),  // "width"
        QT_MOC_LITERAL(68, 6),  // "height"
        QT_MOC_LITERAL(75, 17),  // "selectedTrackLost"
        QT_MOC_LITERAL(93, 7),  // "trackId"
        QT_MOC_LITERAL(101, 17),  // "trackedIdsUpdated"
        QT_MOC_LITERAL(119, 9),  // "QSet<int>"
        QT_MOC_LITERAL(129, 3),  // "ids"
        QT_MOC_LITERAL(133, 21),  // "targetPositionUpdated"
        QT_MOC_LITERAL(155, 7),  // "azimuth"
        QT_MOC_LITERAL(163, 9),  // "elevation"
        QT_MOC_LITERAL(173, 31),  // "dayCameraInterfaceStatusChanged"
        QT_MOC_LITERAL(205, 11),  // "isConnected"
        QT_MOC_LITERAL(217, 33),  // "nightCameraInterfaceStatusCha..."
        QT_MOC_LITERAL(251, 26),  // "lensInterfaceStatusChanged"
        QT_MOC_LITERAL(278, 20),  // "lensResponseReceived"
        QT_MOC_LITERAL(299, 8),  // "response"
        QT_MOC_LITERAL(308, 19),  // "dayResponseReceived"
        QT_MOC_LITERAL(328, 21),  // "nightResponseReceived"
        QT_MOC_LITERAL(350, 19),  // "onNewFrameAvailable"
        QT_MOC_LITERAL(370, 19),  // "onSelectedTrackLost"
        QT_MOC_LITERAL(390, 19),  // "onTrackedIdsUpdated"
        QT_MOC_LITERAL(410, 8),  // "trackIds"
        QT_MOC_LITERAL(419, 33),  // "onDayCameraInterfaceStatusCha..."
        QT_MOC_LITERAL(453, 35),  // "onNightCameraInterfaceStatusC..."
        QT_MOC_LITERAL(489, 28),  // "onLensInterfaceStatusChanged"
        QT_MOC_LITERAL(518, 30),  // "onDayInterfaceResponseReceived"
        QT_MOC_LITERAL(549, 32),  // "onNightInterfaceResponseReceived"
        QT_MOC_LITERAL(582, 22),  // "onLensResponseReceived"
        QT_MOC_LITERAL(605, 15),  // "onErrorOccurred"
        QT_MOC_LITERAL(621, 23)   // "onTargetPositionUpdated"
    },
    "CameraSystem",
    "errorOccurred",
    "",
    "error",
    "newFrameAvailable",
    "frameData",
    "width",
    "height",
    "selectedTrackLost",
    "trackId",
    "trackedIdsUpdated",
    "QSet<int>",
    "ids",
    "targetPositionUpdated",
    "azimuth",
    "elevation",
    "dayCameraInterfaceStatusChanged",
    "isConnected",
    "nightCameraInterfaceStatusChanged",
    "lensInterfaceStatusChanged",
    "lensResponseReceived",
    "response",
    "dayResponseReceived",
    "nightResponseReceived",
    "onNewFrameAvailable",
    "onSelectedTrackLost",
    "onTrackedIdsUpdated",
    "trackIds",
    "onDayCameraInterfaceStatusChanged",
    "onNightCameraInterfaceStatusChanged",
    "onLensInterfaceStatusChanged",
    "onDayInterfaceResponseReceived",
    "onNightInterfaceResponseReceived",
    "onLensResponseReceived",
    "onErrorOccurred",
    "onTargetPositionUpdated"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCameraSystemENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  146,    2, 0x06,    1 /* Public */,
       4,    3,  149,    2, 0x06,    3 /* Public */,
       8,    1,  156,    2, 0x06,    7 /* Public */,
      10,    1,  159,    2, 0x06,    9 /* Public */,
      13,    2,  162,    2, 0x06,   11 /* Public */,
      16,    1,  167,    2, 0x06,   14 /* Public */,
      18,    1,  170,    2, 0x06,   16 /* Public */,
      19,    1,  173,    2, 0x06,   18 /* Public */,
      20,    1,  176,    2, 0x06,   20 /* Public */,
      22,    1,  179,    2, 0x06,   22 /* Public */,
      23,    1,  182,    2, 0x06,   24 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      24,    3,  185,    2, 0x08,   26 /* Private */,
      25,    1,  192,    2, 0x08,   30 /* Private */,
      26,    1,  195,    2, 0x08,   32 /* Private */,
      28,    1,  198,    2, 0x08,   34 /* Private */,
      29,    1,  201,    2, 0x08,   36 /* Private */,
      30,    1,  204,    2, 0x08,   38 /* Private */,
      31,    1,  207,    2, 0x08,   40 /* Private */,
      32,    1,  210,    2, 0x08,   42 /* Private */,
      33,    1,  213,    2, 0x08,   44 /* Private */,
      34,    1,  216,    2, 0x08,   46 /* Private */,
      35,    2,  219,    2, 0x08,   48 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   14,   15,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QByteArray,   21,
    QMetaType::Void, QMetaType::QByteArray,   21,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   27,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::QByteArray,   21,
    QMetaType::Void, QMetaType::QByteArray,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   14,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject CameraSystem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSCameraSystemENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCameraSystemENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCameraSystemENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CameraSystem, std::true_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'newFrameAvailable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'selectedTrackLost'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'trackedIdsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSet<int> &, std::false_type>,
        // method 'targetPositionUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'dayCameraInterfaceStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'nightCameraInterfaceStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'lensInterfaceStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'lensResponseReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'dayResponseReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'nightResponseReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'onNewFrameAvailable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onSelectedTrackLost'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onTrackedIdsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSet<int> &, std::false_type>,
        // method 'onDayCameraInterfaceStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onNightCameraInterfaceStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onLensInterfaceStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onDayInterfaceResponseReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'onNightInterfaceResponseReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'onLensResponseReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onTargetPositionUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void CameraSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraSystem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->newFrameAvailable((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->selectedTrackLost((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->trackedIdsUpdated((*reinterpret_cast< std::add_pointer_t<QSet<int>>>(_a[1]))); break;
        case 4: _t->targetPositionUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 5: _t->dayCameraInterfaceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->nightCameraInterfaceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->lensInterfaceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->lensResponseReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->dayResponseReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 10: _t->nightResponseReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 11: _t->onNewFrameAvailable((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 12: _t->onSelectedTrackLost((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->onTrackedIdsUpdated((*reinterpret_cast< std::add_pointer_t<QSet<int>>>(_a[1]))); break;
        case 14: _t->onDayCameraInterfaceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->onNightCameraInterfaceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->onLensInterfaceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->onDayInterfaceResponseReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 18: _t->onNightInterfaceResponseReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 19: _t->onLensResponseReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->onTargetPositionUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QSet<int> >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QSet<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraSystem::*)(const QString & );
            if (_t _q_method = &CameraSystem::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(const QByteArray & , int , int );
            if (_t _q_method = &CameraSystem::newFrameAvailable; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(int );
            if (_t _q_method = &CameraSystem::selectedTrackLost; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(const QSet<int> & );
            if (_t _q_method = &CameraSystem::trackedIdsUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(double , double );
            if (_t _q_method = &CameraSystem::targetPositionUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(bool );
            if (_t _q_method = &CameraSystem::dayCameraInterfaceStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(bool );
            if (_t _q_method = &CameraSystem::nightCameraInterfaceStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(bool );
            if (_t _q_method = &CameraSystem::lensInterfaceStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(const QString & );
            if (_t _q_method = &CameraSystem::lensResponseReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(const QByteArray & );
            if (_t _q_method = &CameraSystem::dayResponseReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (CameraSystem::*)(const QByteArray & );
            if (_t _q_method = &CameraSystem::nightResponseReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject *CameraSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCameraSystemENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CameraSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void CameraSystem::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraSystem::newFrameAvailable(const QByteArray & _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraSystem::selectedTrackLost(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraSystem::trackedIdsUpdated(const QSet<int> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CameraSystem::targetPositionUpdated(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CameraSystem::dayCameraInterfaceStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CameraSystem::nightCameraInterfaceStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CameraSystem::lensInterfaceStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CameraSystem::lensResponseReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CameraSystem::dayResponseReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void CameraSystem::nightResponseReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
