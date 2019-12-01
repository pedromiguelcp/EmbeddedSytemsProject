/****************************************************************************
** Meta object code from reading C++ file 'dash.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CarDashboard/dash.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dash.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dash_t {
    QByteArrayData data[15];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dash_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dash_t qt_meta_stringdata_Dash = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Dash"
QT_MOC_LITERAL(1, 5, 11), // "sendCommand"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "command"
QT_MOC_LITERAL(4, 26, 8), // "setColor"
QT_MOC_LITERAL(5, 35, 8), // "id_color"
QT_MOC_LITERAL(6, 44, 14), // "getDeviceSongs"
QT_MOC_LITERAL(7, 59, 10), // "selectSong"
QT_MOC_LITERAL(8, 70, 4), // "song"
QT_MOC_LITERAL(9, 75, 11), // "currentSong"
QT_MOC_LITERAL(10, 87, 9), // "pauseSong"
QT_MOC_LITERAL(11, 97, 10), // "resumeSong"
QT_MOC_LITERAL(12, 108, 10), // "openCamera"
QT_MOC_LITERAL(13, 119, 11), // "closeCamera"
QT_MOC_LITERAL(14, 131, 16) // "adjustDashBright"

    },
    "Dash\0sendCommand\0\0command\0setColor\0"
    "id_color\0getDeviceSongs\0selectSong\0"
    "song\0currentSong\0pauseSong\0resumeSong\0"
    "openCamera\0closeCamera\0adjustDashBright"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dash[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x02 /* Public */,
       4,    1,   67,    2, 0x02 /* Public */,
       6,    0,   70,    2, 0x02 /* Public */,
       7,    1,   71,    2, 0x02 /* Public */,
       9,    0,   74,    2, 0x02 /* Public */,
      10,    0,   75,    2, 0x02 /* Public */,
      11,    0,   76,    2, 0x02 /* Public */,
      12,    0,   77,    2, 0x02 /* Public */,
      13,    0,   78,    2, 0x02 /* Public */,
      14,    1,   79,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Dash::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dash *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { QString _r = _t->getDeviceSongs();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->selectSong((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { QString _r = _t->currentSong();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->pauseSong(); break;
        case 6: _t->resumeSong(); break;
        case 7: _t->openCamera(); break;
        case 8: _t->closeCamera(); break;
        case 9: _t->adjustDashBright((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
