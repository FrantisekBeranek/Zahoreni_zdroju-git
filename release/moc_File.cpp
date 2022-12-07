/****************************************************************************
** Meta object code from reading C++ file 'File.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../File.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'File.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_limits_t {
    const uint offsetsAndSize[2];
    char stringdata0[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_limits_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_limits_t qt_meta_stringdata_limits = {
    {
QT_MOC_LITERAL(0, 6) // "limits"

    },
    "limits"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_limits[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void limits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject limits::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_limits.offsetsAndSize,
    qt_meta_data_limits,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_limits_t
, QtPrivate::TypeAndForceComplete<limits, std::true_type>



>,
    nullptr
} };


const QMetaObject *limits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *limits::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_limits.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int limits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_File_t {
    const uint offsetsAndSize[12];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_File_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_File_t qt_meta_stringdata_File = {
    {
QT_MOC_LITERAL(0, 4), // "File"
QT_MOC_LITERAL(5, 15), // "calibrationOver"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 20), // "calibrationCancelled"
QT_MOC_LITERAL(43, 10), // "saveLimits"
QT_MOC_LITERAL(54, 7) // "showLog"

    },
    "File\0calibrationOver\0\0calibrationCancelled\0"
    "saveLimits\0showLog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_File[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,
       3,    0,   39,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   40,    2, 0x0a,    3 /* Public */,
       5,    0,   41,    2, 0x0a,    4 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void File::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<File *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->calibrationOver(); break;
        case 1: _t->calibrationCancelled(); break;
        case 2: _t->saveLimits(); break;
        case 3: _t->showLog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (File::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&File::calibrationOver)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (File::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&File::calibrationCancelled)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject File::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_File.offsetsAndSize,
    qt_meta_data_File,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_File_t
, QtPrivate::TypeAndForceComplete<File, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *File::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *File::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_File.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int File::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void File::calibrationOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void File::calibrationCancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
