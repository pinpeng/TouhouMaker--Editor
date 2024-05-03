/****************************************************************************
** Meta object code from reading C++ file 'window_editor_stage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/window_editor_stage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_editor_stage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_editor_stage_t {
    QByteArrayData data[10];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_editor_stage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_editor_stage_t qt_meta_stringdata_Window_editor_stage = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Window_editor_stage"
QT_MOC_LITERAL(1, 20, 13), // "requestUpdate"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "_request_id"
QT_MOC_LITERAL(4, 47, 14), // "timeoutRepaint"
QT_MOC_LITERAL(5, 62, 17), // "updateFromOutside"
QT_MOC_LITERAL(6, 80, 16), // "codeEditFinished"
QT_MOC_LITERAL(7, 97, 17), // "stageEditFinished"
QT_MOC_LITERAL(8, 115, 28), // "codeEditBossAddEventFinished"
QT_MOC_LITERAL(9, 144, 29) // "codeEditBossAddThreadFinished"

    },
    "Window_editor_stage\0requestUpdate\0\0"
    "_request_id\0timeoutRepaint\0updateFromOutside\0"
    "codeEditFinished\0stageEditFinished\0"
    "codeEditBossAddEventFinished\0"
    "codeEditBossAddThreadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window_editor_stage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x08 /* Private */,
       5,    1,   53,    2, 0x08 /* Private */,
       6,    0,   56,    2, 0x08 /* Private */,
       7,    0,   57,    2, 0x08 /* Private */,
       8,    0,   58,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window_editor_stage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Window_editor_stage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->timeoutRepaint(); break;
        case 2: _t->updateFromOutside((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->codeEditFinished(); break;
        case 4: _t->stageEditFinished(); break;
        case 5: _t->codeEditBossAddEventFinished(); break;
        case 6: _t->codeEditBossAddThreadFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Window_editor_stage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Window_editor_stage::requestUpdate)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Window_editor_stage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Window_editor_stage.data,
    qt_meta_data_Window_editor_stage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Window_editor_stage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window_editor_stage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window_editor_stage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Window_editor_stage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Window_editor_stage::requestUpdate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
