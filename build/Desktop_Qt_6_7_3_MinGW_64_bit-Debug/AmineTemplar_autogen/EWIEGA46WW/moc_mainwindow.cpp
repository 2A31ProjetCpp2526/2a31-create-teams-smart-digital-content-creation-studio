/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtNetwork/QSslError>
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
    "onRemoveResourceClicked",
    "onAddProjectClicked",
    "onRemoveProjectClicked"
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
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    1,   57,    2, 0x08,    2 /* Private */,
       5,    0,   60,    2, 0x08,    4 /* Private */,
       6,    0,   61,    2, 0x08,    5 /* Private */,
       7,    0,   62,    2, 0x08,    6 /* Private */,
       8,    0,   63,    2, 0x08,    7 /* Private */,
       9,    0,   64,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
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
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddProjectClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRemoveProjectClicked'
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
        case 5: _t->onAddProjectClicked(); break;
        case 6: _t->onRemoveProjectClicked(); break;
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSProjectFormENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSProjectFormENDCLASS = QtMocHelpers::stringData(
    "ProjectForm",
    "clearErrorMessage",
    ""
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProjectFormENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProjectForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSProjectFormENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSProjectFormENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSProjectFormENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProjectForm, std::true_type>,
        // method 'clearErrorMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ProjectForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProjectForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clearErrorMessage(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ProjectForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSProjectFormENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ProjectForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_CLASSProjectSelectionDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSProjectSelectionDialogENDCLASS = QtMocHelpers::stringData(
    "ProjectSelectionDialog"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProjectSelectionDialogENDCLASS[] = {

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

Q_CONSTINIT const QMetaObject ProjectSelectionDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSProjectSelectionDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSProjectSelectionDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSProjectSelectionDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProjectSelectionDialog, std::true_type>
    >,
    nullptr
} };

void ProjectSelectionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *ProjectSelectionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectSelectionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSProjectSelectionDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ProjectSelectionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    "onLoginBackClicked",
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
    "onSearchInputChanged",
    "text",
    "onSortEmployersClicked",
    "onStatisticsClicked",
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
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  194,    2, 0x08,    1 /* Private */,
       3,    0,  195,    2, 0x08,    2 /* Private */,
       4,    0,  196,    2, 0x08,    3 /* Private */,
       5,    0,  197,    2, 0x08,    4 /* Private */,
       6,    0,  198,    2, 0x08,    5 /* Private */,
       7,    0,  199,    2, 0x08,    6 /* Private */,
       8,    0,  200,    2, 0x08,    7 /* Private */,
       9,    0,  201,    2, 0x08,    8 /* Private */,
      10,    0,  202,    2, 0x08,    9 /* Private */,
      11,    0,  203,    2, 0x08,   10 /* Private */,
      12,    0,  204,    2, 0x08,   11 /* Private */,
      13,    0,  205,    2, 0x08,   12 /* Private */,
      14,    0,  206,    2, 0x08,   13 /* Private */,
      15,    0,  207,    2, 0x08,   14 /* Private */,
      16,    0,  208,    2, 0x08,   15 /* Private */,
      17,    0,  209,    2, 0x08,   16 /* Private */,
      18,    0,  210,    2, 0x08,   17 /* Private */,
      19,    0,  211,    2, 0x08,   18 /* Private */,
      20,    0,  212,    2, 0x08,   19 /* Private */,
      21,    0,  213,    2, 0x08,   20 /* Private */,
      22,    0,  214,    2, 0x08,   21 /* Private */,
      23,    0,  215,    2, 0x08,   22 /* Private */,
      24,    0,  216,    2, 0x08,   23 /* Private */,
      25,    0,  217,    2, 0x08,   24 /* Private */,
      26,    1,  218,    2, 0x08,   25 /* Private */,
      28,    0,  221,    2, 0x08,   27 /* Private */,
      29,    0,  222,    2, 0x08,   28 /* Private */,
      30,    0,  223,    2, 0x08,   29 /* Private */,
      31,    1,  224,    2, 0x08,   30 /* Private */,
      34,    0,  227,    2, 0x08,   32 /* Private */,

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
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
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
        // method 'onLoginBackClicked'
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
        // method 'onSearchInputChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onSortEmployersClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStatisticsClicked'
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
        case 9: _t->onLoginBackClicked(); break;
        case 10: _t->setupDashboardAnimations(); break;
        case 11: _t->showSignUpForm(); break;
        case 12: _t->showLoginForm(); break;
        case 13: _t->showForgotPasswordForm(); break;
        case 14: _t->validateAndSendResetLink(); break;
        case 15: _t->onSaveProfileClicked(); break;
        case 16: _t->onResetProfileClicked(); break;
        case 17: _t->validateAndLogin(); break;
        case 18: _t->validateAndSignUp(); break;
        case 19: _t->onAddEmployerClicked(); break;
        case 20: _t->onModifyEmployerClicked(); break;
        case 21: _t->onDeleteEmployerClicked(); break;
        case 22: _t->onExportEmployersClicked(); break;
        case 23: _t->onSearchEmployersClicked(); break;
        case 24: _t->onSearchInputChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->onSortEmployersClicked(); break;
        case 26: _t->onStatisticsClicked(); break;
        case 27: _t->onEmployeeTableSelectionChanged(); break;
        case 28: _t->onEmployeeTableItemClicked((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 29: _t->onCancelSelectionClicked(); break;
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
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 30;
    }
    return _id;
}
QT_WARNING_POP
