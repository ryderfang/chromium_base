/****************************************************************************
** Meta object code from reading C++ file 'test_qt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../test_qt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_test_qt_t {
    QByteArrayData data[13];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_qt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_qt_t qt_meta_stringdata_test_qt = {
    {
QT_MOC_LITERAL(0, 0, 7), // "test_qt"
QT_MOC_LITERAL(1, 8, 8), // "sltStart"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "sltPause"
QT_MOC_LITERAL(4, 27, 9), // "sltDelete"
QT_MOC_LITERAL(5, 37, 11), // "sltStartAll"
QT_MOC_LITERAL(6, 49, 11), // "sltPauseAll"
QT_MOC_LITERAL(7, 61, 17), // "sltUpdateProgress"
QT_MOC_LITERAL(8, 79, 11), // "std::string"
QT_MOC_LITERAL(9, 91, 4), // "name"
QT_MOC_LITERAL(10, 96, 3), // "pos"
QT_MOC_LITERAL(11, 100, 5), // "int64"
QT_MOC_LITERAL(12, 106, 5) // "speed"

    },
    "test_qt\0sltStart\0\0sltPause\0sltDelete\0"
    "sltStartAll\0sltPauseAll\0sltUpdateProgress\0"
    "std::string\0name\0pos\0int64\0speed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test_qt[] = {

 // content:
       7,       // revision
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
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    3,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, 0x80000000 | 11,    9,   10,   12,

       0        // eod
};

void test_qt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        test_qt *_t = static_cast<test_qt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sltStart(); break;
        case 1: _t->sltPause(); break;
        case 2: _t->sltDelete(); break;
        case 3: _t->sltStartAll(); break;
        case 4: _t->sltPauseAll(); break;
        case 5: _t->sltUpdateProgress((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject test_qt::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_test_qt.data,
      qt_meta_data_test_qt,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *test_qt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_qt::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_test_qt.stringdata0))
        return static_cast<void*>(const_cast< test_qt*>(this));
    return QWidget::qt_metacast(_clname);
}

int test_qt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
