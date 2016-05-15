/****************************************************************************
** Meta object code from reading C++ file 'work_loop.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../work_loop.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'work_loop.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WorkLoop_t {
    QByteArrayData data[8];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkLoop_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkLoop_t qt_meta_stringdata_WorkLoop = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WorkLoop"
QT_MOC_LITERAL(1, 9, 15), // "update_progress"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "std::string"
QT_MOC_LITERAL(4, 38, 4), // "name"
QT_MOC_LITERAL(5, 43, 3), // "pos"
QT_MOC_LITERAL(6, 47, 5), // "int64"
QT_MOC_LITERAL(7, 53, 5) // "speed"

    },
    "WorkLoop\0update_progress\0\0std::string\0"
    "name\0pos\0int64\0speed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkLoop[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 6,    4,    5,    7,

       0        // eod
};

void WorkLoop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkLoop *_t = static_cast<WorkLoop *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_progress((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkLoop::*_t)(const std::string & , int , int64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkLoop::update_progress)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WorkLoop::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WorkLoop.data,
      qt_meta_data_WorkLoop,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkLoop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkLoop::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkLoop.stringdata0))
        return static_cast<void*>(const_cast< WorkLoop*>(this));
    if (!strcmp(_clname, "base::RefCountedThreadSafe<WorkLoop>"))
        return static_cast< base::RefCountedThreadSafe<WorkLoop>*>(const_cast< WorkLoop*>(this));
    if (!strcmp(_clname, "WorkDelegate"))
        return static_cast< WorkDelegate*>(const_cast< WorkLoop*>(this));
    return QObject::qt_metacast(_clname);
}

int WorkLoop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WorkLoop::update_progress(const std::string & _t1, int _t2, int64 _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
