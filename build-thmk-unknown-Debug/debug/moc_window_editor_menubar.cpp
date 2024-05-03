/****************************************************************************
** Meta object code from reading C++ file 'window_editor_menubar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_editor_menubar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_editor_menubar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_editor_menubar_t {
    QByteArrayData data[20];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_editor_menubar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_editor_menubar_t qt_meta_stringdata_Window_editor_menubar = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Window_editor_menubar"
QT_MOC_LITERAL(1, 22, 11), // "requestUndo"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "requestRedo"
QT_MOC_LITERAL(4, 47, 13), // "requestUpdate"
QT_MOC_LITERAL(5, 61, 11), // "_request_id"
QT_MOC_LITERAL(6, 73, 17), // "requestBackToHome"
QT_MOC_LITERAL(7, 91, 14), // "timeoutRepaint"
QT_MOC_LITERAL(8, 106, 10), // "backToHome"
QT_MOC_LITERAL(9, 117, 4), // "save"
QT_MOC_LITERAL(10, 122, 4), // "pack"
QT_MOC_LITERAL(11, 127, 5), // "func0"
QT_MOC_LITERAL(12, 133, 5), // "func1"
QT_MOC_LITERAL(13, 139, 5), // "func2"
QT_MOC_LITERAL(14, 145, 5), // "func3"
QT_MOC_LITERAL(15, 151, 5), // "func4"
QT_MOC_LITERAL(16, 157, 5), // "func5"
QT_MOC_LITERAL(17, 163, 5), // "func6"
QT_MOC_LITERAL(18, 169, 5), // "func7"
QT_MOC_LITERAL(19, 175, 19) // "stageUpdateListCall"

    },
    "Window_editor_menubar\0requestUndo\0\0"
    "requestRedo\0requestUpdate\0_request_id\0"
    "requestBackToHome\0timeoutRepaint\0"
    "backToHome\0save\0pack\0func0\0func1\0func2\0"
    "func3\0func4\0func5\0func6\0func7\0"
    "stageUpdateListCall"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_editor_menubar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    1,  101,    2, 0x06 /* Public */,
       6,    0,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  105,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x0a /* Public */,
      10,    0,  108,    2, 0x0a /* Public */,
      11,    0,  109,    2, 0x0a /* Public */,
      12,    0,  110,    2, 0x0a /* Public */,
      13,    0,  111,    2, 0x0a /* Public */,
      14,    0,  112,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    0,  115,    2, 0x0a /* Public */,
      18,    0,  116,    2, 0x0a /* Public */,
      19,    0,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window_editor_menubar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_editor_menubar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestUndo(); break;
        case 1: _t->requestRedo(); break;
        case 2: _t->requestUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->requestBackToHome(); break;
        case 4: _t->timeoutRepaint(); break;
        case 5: _t->backToHome(); break;
        case 6: _t->save(); break;
        case 7: _t->pack(); break;
        case 8: _t->func0(); break;
        case 9: _t->func1(); break;
        case 10: _t->func2(); break;
        case 11: _t->func3(); break;
        case 12: _t->func4(); break;
        case 13: _t->func5(); break;
        case 14: _t->func6(); break;
        case 15: _t->func7(); break;
        case 16: _t->stageUpdateListCall(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Window_editor_menubar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_menubar::requestUndo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Window_editor_menubar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_menubar::requestRedo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Window_editor_menubar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_menubar::requestUpdate)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Window_editor_menubar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_menubar::requestBackToHome)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Window_editor_menubar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Window_editor_menubar.data,
    qt_meta_data_Window_editor_menubar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_editor_menubar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_editor_menubar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_editor_menubar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Window_editor_menubar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void Window_editor_menubar::requestUndo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Window_editor_menubar::requestRedo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Window_editor_menubar::requestUpdate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Window_editor_menubar::requestBackToHome()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
