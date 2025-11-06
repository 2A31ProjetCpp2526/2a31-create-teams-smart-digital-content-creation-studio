/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
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
struct qt_meta_stringdata_CLASSEmployerFormENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSEmployerFormENDCLASS = QtMocHelpers::stringData(
    "EmployerForm",
    "browseAvatar",
    "",
    "updateAvatarPreview",
    "path",
    "clearErrorMessage",
    "onAddResourceClicked",
    "onRemoveResourceClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSEmployerFormENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    1,   45,    2, 0x08,    2 /* Private */,
       5,    0,   48,    2, 0x08,    4 /* Private */,
       6,    0,   49,    2, 0x08,    5 /* Private */,
       7,    0,   50,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject EmployerForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSEmployerFormENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSEmployerFormENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSEmployerFormENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EmployerForm, std::true_type>,
        // method 'browseAvatar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateAvatarPreview'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'clearErrorMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddResourceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRemoveResourceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void EmployerForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EmployerForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->browseAvatar(); break;
        case 1: _t->updateAvatarPreview((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->clearErrorMessage(); break;
        case 3: _t->onAddResourceClicked(); break;
        case 4: _t->onRemoveResourceClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *EmployerForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmployerForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSEmployerFormENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int EmployerForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSResourceSelectionDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSResourceSelectionDialogENDCLASS = QtMocHelpers::stringData(
    "ResourceSelectionDialog"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSResourceSelectionDialogENDCLASS[] = {

 // content:
      12,       // revision
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

Q_CONSTINIT const QMetaObject ResourceSelectionDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSResourceSelectionDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSResourceSelectionDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSResourceSelectionDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ResourceSelectionDialog, std::true_type>
    >,
    nullptr
} };

void ResourceSelectionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *ResourceSelectionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResourceSelectionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSResourceSelectionDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ResourceSelectionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onDashboardClicked",
    "",
    "onProfileClicked",
    "onProjectsClicked",
    "onClientsClicked",
    "onResourcesClicked",
    "onSponsorsClicked",
    "onTemplatesClicked",
    "onAboutClicked",
    "onLoginClicked",
    "setupDashboardAnimations",
    "showSignUpForm",
    "showLoginForm",
    "showForgotPasswordForm",
    "validateAndSendResetLink",
    "onSaveProfileClicked",
    "onResetProfileClicked",
    "validateAndLogin",
    "validateAndSignUp",
    "onAddEmployerClicked",
    "onModifyEmployerClicked",
    "onDeleteEmployerClicked",
    "onExportEmployersClicked",
    "onSearchEmployersClicked",
    "onSortEmployersClicked",
    "onEmployeeTableSelectionChanged",
    "onEmployeeTableItemClicked",
    "QTableWidgetItem*",
    "item",
    "onCancelSelectionClicked"
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
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  176,    2, 0x08,    1 /* Private */,
       3,    0,  177,    2, 0x08,    2 /* Private */,
       4,    0,  178,    2, 0x08,    3 /* Private */,
       5,    0,  179,    2, 0x08,    4 /* Private */,
       6,    0,  180,    2, 0x08,    5 /* Private */,
       7,    0,  181,    2, 0x08,    6 /* Private */,
       8,    0,  182,    2, 0x08,    7 /* Private */,
       9,    0,  183,    2, 0x08,    8 /* Private */,
      10,    0,  184,    2, 0x08,    9 /* Private */,
      11,    0,  185,    2, 0x08,   10 /* Private */,
      12,    0,  186,    2, 0x08,   11 /* Private */,
      13,    0,  187,    2, 0x08,   12 /* Private */,
      14,    0,  188,    2, 0x08,   13 /* Private */,
      15,    0,  189,    2, 0x08,   14 /* Private */,
      16,    0,  190,    2, 0x08,   15 /* Private */,
      17,    0,  191,    2, 0x08,   16 /* Private */,
      18,    0,  192,    2, 0x08,   17 /* Private */,
      19,    0,  193,    2, 0x08,   18 /* Private */,
      20,    0,  194,    2, 0x08,   19 /* Private */,
      21,    0,  195,    2, 0x08,   20 /* Private */,
      22,    0,  196,    2, 0x08,   21 /* Private */,
      23,    0,  197,    2, 0x08,   22 /* Private */,
      24,    0,  198,    2, 0x08,   23 /* Private */,
      25,    0,  199,    2, 0x08,   24 /* Private */,
      26,    0,  200,    2, 0x08,   25 /* Private */,
      27,    1,  201,    2, 0x08,   26 /* Private */,
      30,    0,  204,    2, 0x08,   28 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
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
        // method 'onDashboardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onProfileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onProjectsClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClientsClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResourcesClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSponsorsClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTemplatesClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAboutClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLoginClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupDashboardAnimations'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showSignUpForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showLoginForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showForgotPasswordForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'validateAndSendResetLink'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveProfileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResetProfileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'validateAndLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'validateAndSignUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddEmployerClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onModifyEmployerClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteEmployerClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onExportEmployersClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSearchEmployersClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSortEmployersClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEmployeeTableSelectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEmployeeTableItemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>,
        // method 'onCancelSelectionClicked'
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
        case 0: _t->onDashboardClicked(); break;
        case 1: _t->onProfileClicked(); break;
        case 2: _t->onProjectsClicked(); break;
        case 3: _t->onClientsClicked(); break;
        case 4: _t->onResourcesClicked(); break;
        case 5: _t->onSponsorsClicked(); break;
        case 6: _t->onTemplatesClicked(); break;
        case 7: _t->onAboutClicked(); break;
        case 8: _t->onLoginClicked(); break;
        case 9: _t->setupDashboardAnimations(); break;
        case 10: _t->showSignUpForm(); break;
        case 11: _t->showLoginForm(); break;
        case 12: _t->showForgotPasswordForm(); break;
        case 13: _t->validateAndSendResetLink(); break;
        case 14: _t->onSaveProfileClicked(); break;
        case 15: _t->onResetProfileClicked(); break;
        case 16: _t->validateAndLogin(); break;
        case 17: _t->validateAndSignUp(); break;
        case 18: _t->onAddEmployerClicked(); break;
        case 19: _t->onModifyEmployerClicked(); break;
        case 20: _t->onDeleteEmployerClicked(); break;
        case 21: _t->onExportEmployersClicked(); break;
        case 22: _t->onSearchEmployersClicked(); break;
        case 23: _t->onSortEmployersClicked(); break;
        case 24: _t->onEmployeeTableSelectionChanged(); break;
        case 25: _t->onEmployeeTableItemClicked((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 26: _t->onCancelSelectionClicked(); break;
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
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 27;
    }
    return _id;
}
QT_WARNING_POP
