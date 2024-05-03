/****************************************************************************
** Meta object code from reading C++ file 'window_editor_menubar_bullet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_editor_menubar_bullet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_editor_menubar_bullet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_editor_menubar_bullet_t {
    QByteArrayData data[8];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_editor_menubar_bullet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_editor_menubar_bullet_t qt_meta_stringdata_Window_editor_menubar_bullet = {
    {
QT_MOC_LITERAL(0, 0, 28), // "Window_editor_menubar_bullet"
QT_MOC_LITERAL(1, 29, 10), // "updateList"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 6), // "accept"
QT_MOC_LITERAL(4, 48, 10), // "editBullet"
QT_MOC_LITERAL(5, 59, 6), // "_index"
QT_MOC_LITERAL(6, 66, 3), // "add"
QT_MOC_LITERAL(7, 70, 3) // "del"

    },
    "Window_editor_menubar_bullet\0updateList\0"
    "\0accept\0editBullet\0_index\0add\0del"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_editor_menubar_bullet[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window_editor_menubar_bullet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_editor_menubar_bullet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateList(); break;
        case 1: _t->accept(); break;
        case 2: _t->editBullet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->add(); break;
        case 4: _t->del(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Window_editor_menubar_bullet::staticMetaObject = { {
    QMetaObject::SuperData::link<Window_small::staticMetaObject>(),
    qt_meta_stringdata_Window_editor_menubar_bullet.data,
    qt_meta_data_Window_editor_menubar_bullet,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_editor_menubar_bullet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_editor_menubar_bullet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_editor_menubar_bullet.stringdata0))
        return static_cast<void*>(this);
    return Window_small::qt_metacast(_clname);
}

int Window_editor_menubar_bullet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window_small::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
