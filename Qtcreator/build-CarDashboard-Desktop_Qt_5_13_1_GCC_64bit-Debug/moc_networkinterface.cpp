/****************************************************************************
** Meta object code from reading C++ file 'networkinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../CarDashboard/networkinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkInterface_t {
    QByteArrayData data[12];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkInterface_t qt_meta_stringdata_NetworkInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "NetworkInterface"
QT_MOC_LITERAL(1, 17, 12), // "readyweather"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "weather_t"
QT_MOC_LITERAL(4, 41, 13), // "weatherValues"
QT_MOC_LITERAL(5, 55, 9), // "readynews"
QT_MOC_LITERAL(6, 65, 8), // "news_t[]"
QT_MOC_LITERAL(7, 74, 10), // "newsValues"
QT_MOC_LITERAL(8, 85, 14), // "refreshWeather"
QT_MOC_LITERAL(9, 100, 11), // "refreshNews"
QT_MOC_LITERAL(10, 112, 12), // "printweather"
QT_MOC_LITERAL(11, 125, 9) // "printnews"

    },
    "NetworkInterface\0readyweather\0\0weather_t\0"
    "weatherValues\0readynews\0news_t[]\0"
    "newsValues\0refreshWeather\0refreshNews\0"
    "printweather\0printnews"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   50,    2, 0x0a /* Public */,
       9,    0,   51,    2, 0x0a /* Public */,
      10,    0,   52,    2, 0x0a /* Public */,
      11,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NetworkInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyweather((*reinterpret_cast< weather_t(*)>(_a[1]))); break;
        case 1: _t->readynews((*reinterpret_cast< news_t(*)[]>(_a[1]))); break;
        case 2: _t->refreshWeather(); break;
        case 3: _t->refreshNews(); break;
        case 4: _t->printweather(); break;
        case 5: _t->printnews(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkInterface::*)(weather_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkInterface::readyweather)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkInterface::*)(news_t []);
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkInterface::readynews)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetworkInterface::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NetworkInterface.data,
    qt_meta_data_NetworkInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NetworkInterface::readyweather(weather_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkInterface::readynews(news_t _t1[])
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE