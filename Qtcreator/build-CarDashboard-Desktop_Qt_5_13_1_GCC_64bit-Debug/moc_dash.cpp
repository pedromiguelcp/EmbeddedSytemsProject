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
    QByteArrayData data[32];
    char stringdata0[373];
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
QT_MOC_LITERAL(6, 66, 13), // "askforcarinfo"
QT_MOC_LITERAL(7, 80, 11), // "timersignal"
QT_MOC_LITERAL(8, 92, 10), // "valChanged"
QT_MOC_LITERAL(9, 103, 11), // "sendCommand"
QT_MOC_LITERAL(10, 115, 7), // "command"
QT_MOC_LITERAL(11, 123, 8), // "setColor"
QT_MOC_LITERAL(12, 132, 8), // "id_color"
QT_MOC_LITERAL(13, 141, 14), // "getDeviceSongs"
QT_MOC_LITERAL(14, 156, 10), // "selectSong"
QT_MOC_LITERAL(15, 167, 4), // "song"
QT_MOC_LITERAL(16, 172, 11), // "currentSong"
QT_MOC_LITERAL(17, 184, 9), // "pauseSong"
QT_MOC_LITERAL(18, 194, 10), // "resumeSong"
QT_MOC_LITERAL(19, 205, 18), // "controlMusicVolume"
QT_MOC_LITERAL(20, 224, 6), // "volume"
QT_MOC_LITERAL(21, 231, 14), // "getMusicVolume"
QT_MOC_LITERAL(22, 246, 10), // "openCamera"
QT_MOC_LITERAL(23, 257, 11), // "closeCamera"
QT_MOC_LITERAL(24, 269, 16), // "adjustDashBright"
QT_MOC_LITERAL(25, 286, 13), // "getDashBright"
QT_MOC_LITERAL(26, 300, 7), // "getNews"
QT_MOC_LITERAL(27, 308, 5), // "index"
QT_MOC_LITERAL(28, 314, 14), // "getWeatherCity"
QT_MOC_LITERAL(29, 329, 17), // "getWeatherCountry"
QT_MOC_LITERAL(30, 347, 21), // "getWeatherTemperature"
QT_MOC_LITERAL(31, 369, 3) // "val"

    },
    "Dash\0askfornews\0\0askforweather\0"
    "askforbrightness\0askfortemperature\0"
    "askforcarinfo\0timersignal\0valChanged\0"
    "sendCommand\0command\0setColor\0id_color\0"
    "getDeviceSongs\0selectSong\0song\0"
    "currentSong\0pauseSong\0resumeSong\0"
    "controlMusicVolume\0volume\0getMusicVolume\0"
    "openCamera\0closeCamera\0adjustDashBright\0"
    "getDashBright\0getNews\0index\0getWeatherCity\0"
    "getWeatherCountry\0getWeatherTemperature\0"
    "val"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dash[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       1,  172, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  134,    2, 0x06 /* Public */,
       3,    0,  135,    2, 0x06 /* Public */,
       4,    0,  136,    2, 0x06 /* Public */,
       5,    0,  137,    2, 0x06 /* Public */,
       6,    0,  138,    2, 0x06 /* Public */,
       7,    0,  139,    2, 0x06 /* Public */,
       8,    1,  140,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    1,  143,    2, 0x02 /* Public */,
      11,    1,  146,    2, 0x02 /* Public */,
      13,    0,  149,    2, 0x02 /* Public */,
      14,    1,  150,    2, 0x02 /* Public */,
      16,    0,  153,    2, 0x02 /* Public */,
      17,    0,  154,    2, 0x02 /* Public */,
      18,    0,  155,    2, 0x02 /* Public */,
      19,    1,  156,    2, 0x02 /* Public */,
      21,    0,  159,    2, 0x02 /* Public */,
      22,    0,  160,    2, 0x02 /* Public */,
      23,    0,  161,    2, 0x02 /* Public */,
      24,    1,  162,    2, 0x02 /* Public */,
      25,    0,  165,    2, 0x02 /* Public */,
      26,    1,  166,    2, 0x02 /* Public */,
      28,    0,  169,    2, 0x02 /* Public */,
      29,    0,  170,    2, 0x02 /* Public */,
      30,    0,  171,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   27,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,

 // properties: name, type, flags
      31, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       6,

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
        case 4: _t->askforcarinfo(); break;
        case 5: _t->timersignal(); break;
        case 6: _t->valChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->sendCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->getDeviceSongs();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->selectSong((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: { QString _r = _t->currentSong();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->pauseSong(); break;
        case 13: _t->resumeSong(); break;
        case 14: _t->controlMusicVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: { int _r = _t->getMusicVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->openCamera(); break;
        case 17: _t->closeCamera(); break;
        case 18: _t->adjustDashBright((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: { int _r = _t->getDashBright();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->getNews((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 21: { QString _r = _t->getWeatherCity();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 22: { QString _r = _t->getWeatherCountry();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: { int _r = _t->getWeatherTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::askforcarinfo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Dash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::timersignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Dash::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dash::valChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Dash *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->val(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Dash *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVal(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
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
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
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
void Dash::askforcarinfo()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Dash::timersignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Dash::valChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
