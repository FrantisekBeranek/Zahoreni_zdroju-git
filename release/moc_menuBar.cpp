/****************************************************************************
** Meta object code from reading C++ file 'menuBar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../menuBar.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_menuZahoreni_t {
    const uint offsetsAndSize[16];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_menuZahoreni_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_menuZahoreni_t qt_meta_stringdata_menuZahoreni = {
    {
QT_MOC_LITERAL(0, 12), // "menuZahoreni"
QT_MOC_LITERAL(13, 12), // "startRequest"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 11), // "stopRequest"
QT_MOC_LITERAL(39, 12), // "changeLimits"
QT_MOC_LITERAL(52, 14), // "showLogRequest"
QT_MOC_LITERAL(67, 7), // "handler"
QT_MOC_LITERAL(75, 8) // "QAction*"

    },
    "menuZahoreni\0startRequest\0\0stopRequest\0"
    "changeLimits\0showLogRequest\0handler\0"
    "QAction*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_menuZahoreni[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,
       3,    0,   45,    2, 0x06,    2 /* Public */,
       4,    0,   46,    2, 0x06,    3 /* Public */,
       5,    0,   47,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   48,    2, 0x0a,    5 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void menuZahoreni::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<menuZahoreni *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startRequest(); break;
        case 1: _t->stopRequest(); break;
        case 2: _t->changeLimits(); break;
        case 3: _t->showLogRequest(); break;
        case 4: _t->handler((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (menuZahoreni::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&menuZahoreni::startRequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (menuZahoreni::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&menuZahoreni::stopRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (menuZahoreni::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&menuZahoreni::changeLimits)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (menuZahoreni::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&menuZahoreni::showLogRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject menuZahoreni::staticMetaObject = { {
    QMetaObject::SuperData::link<QMenu::staticMetaObject>(),
    qt_meta_stringdata_menuZahoreni.offsetsAndSize,
    qt_meta_data_menuZahoreni,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_menuZahoreni_t
, QtPrivate::TypeAndForceComplete<menuZahoreni, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>


>,
    nullptr
} };


const QMetaObject *menuZahoreni::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *menuZahoreni::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_menuZahoreni.stringdata0))
        return static_cast<void*>(this);
    return QMenu::qt_metacast(_clname);
}

int menuZahoreni::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void menuZahoreni::startRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void menuZahoreni::stopRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void menuZahoreni::changeLimits()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void menuZahoreni::showLogRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_menuBar_t {
    const uint offsetsAndSize[8];
    char stringdata0[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_menuBar_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_menuBar_t qt_meta_stringdata_menuBar = {
    {
QT_MOC_LITERAL(0, 7), // "menuBar"
QT_MOC_LITERAL(8, 8), // "setState"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 9) // "appStatus"

    },
    "menuBar\0setState\0\0appStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_menuBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void menuBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<menuBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setState((*reinterpret_cast< std::add_pointer_t<appStatus>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject menuBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QMenuBar::staticMetaObject>(),
    qt_meta_stringdata_menuBar.offsetsAndSize,
    qt_meta_data_menuBar,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_menuBar_t
, QtPrivate::TypeAndForceComplete<menuBar, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<appStatus, std::false_type>


>,
    nullptr
} };


const QMetaObject *menuBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *menuBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_menuBar.stringdata0))
        return static_cast<void*>(this);
    return QMenuBar::qt_metacast(_clname);
}

int menuBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenuBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
