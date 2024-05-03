/****************************************************************************
** Meta object code from reading C++ file 'window_editor_menubar_image_edit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_editor_menubar_image_edit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_editor_menubar_image_edit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_editor_menubar_image_edit_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_editor_menubar_image_edit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_editor_menubar_image_edit_t qt_meta_stringdata_Window_editor_menubar_image_edit = {
    {
QT_MOC_LITERAL(0, 0, 32), // "Window_editor_menubar_image_edit"
QT_MOC_LITERAL(1, 33, 3), // "end"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "open"
QT_MOC_LITERAL(4, 43, 7) // "preview"

    },
    "Window_editor_menubar_image_edit\0end\0"
    "\0open\0preview"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_editor_menubar_image_edit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window_editor_menubar_image_edit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_editor_menubar_image_edit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->end(); break;
        case 1: _t->open(); break;
        case 2: _t->preview(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Window_editor_menubar_image_edit::staticMetaObject = { {
    QMetaObject::SuperData::link<Window_small::staticMetaObject>(),
    qt_meta_stringdata_Window_editor_menubar_image_edit.data,
    qt_meta_data_Window_editor_menubar_image_edit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_editor_menubar_image_edit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_editor_menubar_image_edit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_editor_menubar_image_edit.stringdata0))
        return static_cast<void*>(this);
    return Window_small::qt_metacast(_clname);
}

int Window_editor_menubar_image_edit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window_small::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
