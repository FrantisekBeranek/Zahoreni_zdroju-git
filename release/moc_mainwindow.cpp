/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "statusChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "appStatus"
QT_MOC_LITERAL(4, 36, 11), // "managePaket"
QT_MOC_LITERAL(5, 48, 6), // "Paket*"
QT_MOC_LITERAL(6, 55, 5), // "paket"
QT_MOC_LITERAL(7, 61, 11), // "startManage"
QT_MOC_LITERAL(8, 73, 10), // "stopManage"
QT_MOC_LITERAL(9, 84, 12), // "limitsManage"
QT_MOC_LITERAL(10, 97, 11), // "calibManage"
QT_MOC_LITERAL(11, 109, 11), // "connectPort"
QT_MOC_LITERAL(12, 121, 8), // "QAction*"
QT_MOC_LITERAL(13, 130, 6), // "action"
QT_MOC_LITERAL(14, 137, 14), // "disconnectPort"
QT_MOC_LITERAL(15, 152, 4), // "read"
QT_MOC_LITERAL(16, 157, 18), // "calibrationFailure"
QT_MOC_LITERAL(17, 176, 17), // "cancelCalibration"
QT_MOC_LITERAL(18, 194, 14), // "endCalibration"
QT_MOC_LITERAL(19, 209, 10), // "endMeasure"
QT_MOC_LITERAL(20, 220, 10), // "startError"
QT_MOC_LITERAL(21, 231, 15), // "statusBarTiming"
QT_MOC_LITERAL(22, 247, 17), // "portStatusChanged"
QT_MOC_LITERAL(23, 265, 7) // "Serial*"

    },
    "MainWindow\0statusChanged\0\0appStatus\0"
    "managePaket\0Paket*\0paket\0startManage\0"
    "stopManage\0limitsManage\0calibManage\0"
    "connectPort\0QAction*\0action\0disconnectPort\0"
    "read\0calibrationFailure\0cancelCalibration\0"
    "endCalibration\0endMeasure\0startError\0"
    "statusBarTiming\0portStatusChanged\0"
    "Serial*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  102,    2, 0x0a /* Public */,
       7,    0,  105,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x0a /* Public */,
      10,    0,  108,    2, 0x0a /* Public */,
      11,    1,  109,    2, 0x0a /* Public */,
      14,    0,  112,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    0,  115,    2, 0x0a /* Public */,
      18,    0,  116,    2, 0x0a /* Public */,
      19,    1,  117,    2, 0x0a /* Public */,
      19,    0,  120,    2, 0x0a /* Public */,
      20,    0,  121,    2, 0x0a /* Public */,
      21,    0,  122,    2, 0x0a /* Public */,
      22,    1,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< appStatus(*)>(_a[1]))); break;
        case 1: _t->managePaket((*reinterpret_cast< Paket*(*)>(_a[1]))); break;
        case 2: _t->startManage(); break;
        case 3: _t->stopManage(); break;
        case 4: _t->limitsManage(); break;
        case 5: _t->calibManage(); break;
        case 6: _t->connectPort((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 7: _t->disconnectPort(); break;
        case 8: _t->read(); break;
        case 9: _t->calibrationFailure(); break;
        case 10: _t->cancelCalibration(); break;
        case 11: _t->endCalibration(); break;
        case 12: _t->endMeasure((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->endMeasure(); break;
        case 14: _t->startError(); break;
        case 15: _t->statusBarTiming(); break;
        case 16: _t->portStatusChanged((*reinterpret_cast< Serial*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Serial* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(appStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::statusChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::statusChanged(appStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
