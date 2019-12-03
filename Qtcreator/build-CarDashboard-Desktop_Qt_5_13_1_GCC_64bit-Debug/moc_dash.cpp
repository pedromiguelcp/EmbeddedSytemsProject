/****************************************************************************
** Meta object code from reading C++ file 'dash.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../CarDashboard/dash.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dash.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dash_t {
    QByteArrayData data[26];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dash_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dash_t qt_meta_stringdata_Dash = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Dash"
QT_MOC_LITERAL(1, 5, 10), // "askfornews"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 13), // "askforweather"
QT_MOC_LITERAL(4, 31, 16), // "askforbrightness"
QT_MOC_LITERAL(5, 48, 17), // "askfortemperature"
QT_MOC_LITERAL(6, 66, 11), // "timersignal"
QT_MOC_LITERAL(7, 78, 11), // "sendCommand"
QT_MOC_LITERAL(8, 90, 7), // "command"
QT_MOC_LITERAL(9, 98, 8), // "setColor"
QT_MOC_LITERAL(10, 107, 8), // "id_color"
QT_MOC_LITERAL(11, 116, 14), // "getDeviceSongs"
QT_MOC_LITERAL(12, 131, 10), // "selectSong"
QT_MOC_LITERAL(13, 142, 4), // "song"
QT_MOC_LITERAL(14, 147, 11), // "currentSong"
QT_MOC_LITERAL(15, 159, 9), // "pauseSong"
QT_MOC_LITERAL(16, 169, 10), // "resumeSong"
QT_MOC_LITERAL(17, 180, 18), // "controlMusicVolume"
QT_MOC_LITERAL(18, 199, 6), // "volume"
QT_MOC_LITERAL(19, 206, 14), // "getMusicVolume"
QT_MOC_LITERAL(20, 221, 10), // "openCamera"
QT_MOC_LITERAL(21, 232, 11), // "closeCamera"
QT_MOC_LITERAL(22, 244, 16), // "adjustDashBright"
QT_MOC_LITERAL(23, 261, 13), // "getDashBright"
QT_MOC_LITERAL(24, 275, 7), // "getNews"
QT_MOC_LITERAL(25, 283, 5) // "index"

    },
    "Dash\0askfornews\0\0askforweather\0"
    "askforbrightness\0askfortemperature\0"
    "timersignal\0sendCommand\0command\0"
    "setColor\0id_color\0getDeviceSongs\0"
    "selectSong\0song\0currentSong\0pauseSong\0"
    "resumeSong\0controlMusicVolume\0volume\0"
    "getMusicVolume\0openCamera\0closeCamera\0"
    "adjustDashBright\0getDashBright\0getNews\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dash[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    0,  111,    2, 0x06 /* Public */,
       5,    0,  112,    2, 0x06 /* Public */,
       6,    0,  113,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,  114,    2, 0x02 /* Public */,
       9,    1,  117,    2, 0x02 /* Public */,
      11,    0,  120,    2, 0x02 /* Public */,
      12,    1,  121,    2, 0x02 /* Public */,
      14,    0,  124,    2, 0x02 /* Public */,
      15,    0,  125,    2, 0x02 /* Public */,
      16,    0,  126,    2, 0x02 /* Public */,
      17,    1,  127,    2, 0x02 /* Public */,
      19,    0,  130,    2, 0x02 /* Public */,
      20,    0,  131,    2, 0x02 /* Public */,
      21,    0,  132,    2, 0x02 /* Public */,
      22,    1,  133,    2, 0x02 /* Public */,
      23,    0,  136,    2, 0x02 /* Public */,
      24,    1,  137,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,

       0        // eod
};

void Dash::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dash *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->askfornews(); break;
        case 1: _t->askforweather(); break;
        case 2: _t->askforbrightness(); break;
        case 3: _t->askfortemperature(); break;
        case 4: _t->timersignal(); break;
        case 5: _t->sendCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { QString _r = _t->getDeviceSongs();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->selectSong((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->currentSong();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->pauseSong(); break;
        case 11: _t->resumeSong(); break;
        case 12: _t->controlMusicVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: { int _r = _t->getMusicVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->openCamera(); break;
        case 15: _t->closeCamera(); break;
        case 16: _t->adjustDashBright((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: { int _r = _t->getDashBright();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: { QString _r = _t->getNews((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::askfornews)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::askforweather)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Dash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::askforbrightness)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Dash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::askfortemperature)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Dash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::timersignal)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dash::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Dash.data,
    qt_meta_data_Dash,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Dash::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dash::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dash.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Dash::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Dash::askfornews()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Dash::askforweather()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Dash::askforbrightness()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Dash::askfortemperature()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Dash::timersignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
