/****************************************************************************
** Meta object code from reading C++ file 'window_editor_menubar_audio.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_editor_menubar_audio.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_editor_menubar_audio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_editor_menubar_audio_t {
    QByteArrayData data[9];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_editor_menubar_audio_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_editor_menubar_audio_t qt_meta_stringdata_Window_editor_menubar_audio = {
    {
QT_MOC_LITERAL(0, 0, 27), // "Window_editor_menubar_audio"
QT_MOC_LITERAL(1, 28, 10), // "updateList"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 6), // "accept"
QT_MOC_LITERAL(4, 47, 9), // "editAudio"
QT_MOC_LITERAL(5, 57, 6), // "_index"
QT_MOC_LITERAL(6, 64, 10), // "openFolder"
QT_MOC_LITERAL(7, 75, 3), // "add"
QT_MOC_LITERAL(8, 79, 3) // "del"

    },
    "Window_editor_menubar_audio\0updateList\0"
    "\0accept\0editAudio\0_index\0openFolder\0"
    "add\0del"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_editor_menubar_audio[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window_editor_menubar_audio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_editor_menubar_audio *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateList(); break;
        case 1: _t->accept(); break;
        case 2: _t->editAudio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->openFolder(); break;
        case 4: _t->add(); break;
        case 5: _t->del(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Window_editor_menubar_audio::staticMetaObject = { {
    QMetaObject::SuperData::link<Window_small::staticMetaObject>(),
    qt_meta_stringdata_Window_editor_menubar_audio.data,
    qt_meta_data_Window_editor_menubar_audio,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_editor_menubar_audio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_editor_menubar_audio::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_editor_menubar_audio.stringdata0))
        return static_cast<void*>(this);
    return Window_small::qt_metacast(_clname);
}

int Window_editor_menubar_audio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window_small::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
