/****************************************************************************
** Meta object code from reading C++ file 'window_editor_main.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_editor_main.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_editor_main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_editor_main_t {
    QByteArrayData data[15];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_editor_main_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_editor_main_t qt_meta_stringdata_Window_editor_main = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Window_editor_main"
QT_MOC_LITERAL(1, 19, 13), // "stageKeyArrow"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "stageKeyMove"
QT_MOC_LITERAL(4, 47, 11), // "stageKeyCut"
QT_MOC_LITERAL(5, 59, 14), // "stageKeySelect"
QT_MOC_LITERAL(6, 74, 13), // "stageKeyBrush"
QT_MOC_LITERAL(7, 88, 15), // "stageUpdateList"
QT_MOC_LITERAL(8, 104, 10), // "backToHome"
QT_MOC_LITERAL(9, 115, 4), // "undo"
QT_MOC_LITERAL(10, 120, 4), // "redo"
QT_MOC_LITERAL(11, 125, 4), // "save"
QT_MOC_LITERAL(12, 130, 4), // "pack"
QT_MOC_LITERAL(13, 135, 6), // "ending"
QT_MOC_LITERAL(14, 142, 19) // "stageUpdateListCall"

    },
    "Window_editor_main\0stageKeyArrow\0\0"
    "stageKeyMove\0stageKeyCut\0stageKeySelect\0"
    "stageKeyBrush\0stageUpdateList\0backToHome\0"
    "undo\0redo\0save\0pack\0ending\0"
    "stageUpdateListCall"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_editor_main[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   87,    2, 0x0a /* Public */,
       9,    0,   88,    2, 0x0a /* Public */,
      10,    0,   89,    2, 0x0a /* Public */,
      11,    0,   90,    2, 0x0a /* Public */,
      12,    0,   91,    2, 0x0a /* Public */,
      13,    0,   92,    2, 0x0a /* Public */,
      14,    1,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Window_editor_main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_editor_main *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stageKeyArrow(); break;
        case 1: _t->stageKeyMove(); break;
        case 2: _t->stageKeyCut(); break;
        case 3: _t->stageKeySelect(); break;
        case 4: _t->stageKeyBrush(); break;
        case 5: _t->stageUpdateList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->backToHome(); break;
        case 7: _t->undo(); break;
        case 8: _t->redo(); break;
        case 9: _t->save(); break;
        case 10: _t->pack(); break;
        case 11: _t->ending(); break;
        case 12: _t->stageUpdateListCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Window_editor_main::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_main::stageKeyArrow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Window_editor_main::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_main::stageKeyMove)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Window_editor_main::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_main::stageKeyCut)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Window_editor_main::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_main::stageKeySelect)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Window_editor_main::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_main::stageKeyBrush)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Window_editor_main::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_main::stageUpdateList)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Window_editor_main::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Window_editor_main.data,
    qt_meta_data_Window_editor_main,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_editor_main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_editor_main::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_editor_main.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Window_editor_main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Window_editor_main::stageKeyArrow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Window_editor_main::stageKeyMove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Window_editor_main::stageKeyCut()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Window_editor_main::stageKeySelect()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Window_editor_main::stageKeyBrush()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Window_editor_main::stageUpdateList(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
