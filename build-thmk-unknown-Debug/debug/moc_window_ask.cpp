/****************************************************************************
** Meta object code from reading C++ file 'window_ask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_ask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_ask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_ask_t {
    QByteArrayData data[4];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_ask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_ask_t qt_meta_stringdata_Window_ask = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Window_ask"
QT_MOC_LITERAL(1, 11, 2), // "OK"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 11) // "accept_slot"

    },
    "Window_ask\0OK\0\0accept_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_ask[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Window_ask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_ask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OK(); break;
        case 1: _t->accept_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Window_ask::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_ask::OK)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Window_ask::staticMetaObject = { {
    QMetaObject::SuperData::link<Window_small::staticMetaObject>(),
    qt_meta_stringdata_Window_ask.data,
    qt_meta_data_Window_ask,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_ask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_ask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_ask.stringdata0))
        return static_cast<void*>(this);
    return Window_small::qt_metacast(_clname);
}

int Window_ask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window_small::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Window_ask::OK()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_Window_ask_ex_t {
    QByteArrayData data[12];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_ask_ex_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_ask_ex_t qt_meta_stringdata_Window_ask_ex = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Window_ask_ex"
QT_MOC_LITERAL(1, 14, 2), // "OK"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 20), // "findButtonPressed0_i"
QT_MOC_LITERAL(4, 39, 20), // "findButtonPressed1_i"
QT_MOC_LITERAL(5, 60, 20), // "findButtonPressed2_i"
QT_MOC_LITERAL(6, 81, 20), // "findButtonPressed3_i"
QT_MOC_LITERAL(7, 102, 20), // "findButtonPressed0_f"
QT_MOC_LITERAL(8, 123, 20), // "findButtonPressed1_f"
QT_MOC_LITERAL(9, 144, 20), // "findButtonPressed2_f"
QT_MOC_LITERAL(10, 165, 20), // "findButtonPressed3_f"
QT_MOC_LITERAL(11, 186, 11) // "accept_slot"

    },
    "Window_ask_ex\0OK\0\0findButtonPressed0_i\0"
    "findButtonPressed1_i\0findButtonPressed2_i\0"
    "findButtonPressed3_i\0findButtonPressed0_f\0"
    "findButtonPressed1_f\0findButtonPressed2_f\0"
    "findButtonPressed3_f\0accept_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_ask_ex[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window_ask_ex::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_ask_ex *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OK(); break;
        case 1: _t->findButtonPressed0_i(); break;
        case 2: _t->findButtonPressed1_i(); break;
        case 3: _t->findButtonPressed2_i(); break;
        case 4: _t->findButtonPressed3_i(); break;
        case 5: _t->findButtonPressed0_f(); break;
        case 6: _t->findButtonPressed1_f(); break;
        case 7: _t->findButtonPressed2_f(); break;
        case 8: _t->findButtonPressed3_f(); break;
        case 9: _t->accept_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Window_ask_ex::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_ask_ex::OK)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Window_ask_ex::staticMetaObject = { {
    QMetaObject::SuperData::link<Window_small::staticMetaObject>(),
    qt_meta_stringdata_Window_ask_ex.data,
    qt_meta_data_Window_ask_ex,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_ask_ex::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_ask_ex::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_ask_ex.stringdata0))
        return static_cast<void*>(this);
    return Window_small::qt_metacast(_clname);
}

int Window_ask_ex::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window_small::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Window_ask_ex::OK()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
