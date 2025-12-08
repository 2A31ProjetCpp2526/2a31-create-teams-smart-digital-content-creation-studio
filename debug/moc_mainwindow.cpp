/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "addSponsor",
    "",
    "loadSponsoring",
    "deleteSelectedSponsor",
    "updateSponsor",
    "searchSponsorById",
    "on_pdfexport_clicked",
    "on_sort_clicked",
    "clearFields",
    "onSponsorSelected",
    "QModelIndex",
    "index",
    "drawPieChart",
    "QMap<QString,int>",
    "stats",
    "getStatusFromTable",
    "on_pushButton_stat_clicked",
    "openTodoManager",
    "openCalendar"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    0,  100,    2, 0x08,    3 /* Private */,
       5,    0,  101,    2, 0x08,    4 /* Private */,
       6,    0,  102,    2, 0x08,    5 /* Private */,
       7,    0,  103,    2, 0x08,    6 /* Private */,
       8,    0,  104,    2, 0x08,    7 /* Private */,
       9,    0,  105,    2, 0x08,    8 /* Private */,
      10,    1,  106,    2, 0x08,    9 /* Private */,
      13,    1,  109,    2, 0x08,   11 /* Private */,
      16,    0,  112,    2, 0x08,   13 /* Private */,
      17,    0,  113,    2, 0x08,   14 /* Private */,
      18,    0,  114,    2, 0x08,   15 /* Private */,
      19,    0,  115,    2, 0x08,   16 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    0x80000000 | 14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'addSponsor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadSponsoring'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteSelectedSponsor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateSponsor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchSponsorById'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pdfexport_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sort_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearFields'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSponsorSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'drawPieChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QMap<QString,int> &, std::false_type>,
        // method 'getStatusFromTable'
        QtPrivate::TypeAndForceComplete<QMap<QString,int>, std::false_type>,
        // method 'on_pushButton_stat_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openTodoManager'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openCalendar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addSponsor(); break;
        case 1: _t->loadSponsoring(); break;
        case 2: _t->deleteSelectedSponsor(); break;
        case 3: _t->updateSponsor(); break;
        case 4: _t->searchSponsorById(); break;
        case 5: _t->on_pdfexport_clicked(); break;
        case 6: _t->on_sort_clicked(); break;
        case 7: _t->clearFields(); break;
        case 8: _t->onSponsorSelected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 9: _t->drawPieChart((*reinterpret_cast< std::add_pointer_t<QMap<QString,int>>>(_a[1]))); break;
        case 10: { QMap<QString,int> _r = _t->getStatusFromTable();
            if (_a[0]) *reinterpret_cast< QMap<QString,int>*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->on_pushButton_stat_clicked(); break;
        case 12: _t->openTodoManager(); break;
        case 13: _t->openCalendar(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
