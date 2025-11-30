/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
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
    "onCancelSelectionClicked",
    "addSponsor",
    "updateSponsor",
    "deleteSelectedSponsor",
    "searchSponsorById",
    "loadSponsoring",
    "clearFields",
    "clearSponsorFields",
    "onSponsorSelected",
    "QModelIndex",
    "index",
    "on_pdfexport_clicked",
    "on_sort_clicked",
    "on_pushButton_stat_clicked",
    "drawPieChart",
    "QMap<QString,int>",
    "stats",
    "getStatusFromTable",
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
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  266,    2, 0x08,    1 /* Private */,
       3,    0,  267,    2, 0x08,    2 /* Private */,
       4,    0,  268,    2, 0x08,    3 /* Private */,
       5,    0,  269,    2, 0x08,    4 /* Private */,
       6,    0,  270,    2, 0x08,    5 /* Private */,
       7,    0,  271,    2, 0x08,    6 /* Private */,
       8,    0,  272,    2, 0x08,    7 /* Private */,
       9,    0,  273,    2, 0x08,    8 /* Private */,
      10,    0,  274,    2, 0x08,    9 /* Private */,
      11,    0,  275,    2, 0x08,   10 /* Private */,
      12,    0,  276,    2, 0x08,   11 /* Private */,
      13,    0,  277,    2, 0x08,   12 /* Private */,
      14,    0,  278,    2, 0x08,   13 /* Private */,
      15,    0,  279,    2, 0x08,   14 /* Private */,
      16,    0,  280,    2, 0x08,   15 /* Private */,
      17,    0,  281,    2, 0x08,   16 /* Private */,
      18,    0,  282,    2, 0x08,   17 /* Private */,
      19,    0,  283,    2, 0x08,   18 /* Private */,
      20,    0,  284,    2, 0x08,   19 /* Private */,
      21,    0,  285,    2, 0x08,   20 /* Private */,
      22,    0,  286,    2, 0x08,   21 /* Private */,
      23,    0,  287,    2, 0x08,   22 /* Private */,
      24,    0,  288,    2, 0x08,   23 /* Private */,
      25,    0,  289,    2, 0x08,   24 /* Private */,
      26,    0,  290,    2, 0x08,   25 /* Private */,
      27,    1,  291,    2, 0x08,   26 /* Private */,
      30,    0,  294,    2, 0x08,   28 /* Private */,
      31,    0,  295,    2, 0x08,   29 /* Private */,
      32,    0,  296,    2, 0x08,   30 /* Private */,
      33,    0,  297,    2, 0x08,   31 /* Private */,
      34,    0,  298,    2, 0x08,   32 /* Private */,
      35,    0,  299,    2, 0x08,   33 /* Private */,
      36,    0,  300,    2, 0x08,   34 /* Private */,
      37,    0,  301,    2, 0x08,   35 /* Private */,
      38,    1,  302,    2, 0x08,   36 /* Private */,
      41,    0,  305,    2, 0x08,   38 /* Private */,
      42,    0,  306,    2, 0x08,   39 /* Private */,
      43,    0,  307,    2, 0x08,   40 /* Private */,
      44,    1,  308,    2, 0x08,   41 /* Private */,
      47,    0,  311,    2, 0x08,   43 /* Private */,
      48,    0,  312,    2, 0x08,   44 /* Private */,
      49,    0,  313,    2, 0x08,   45 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 45,   46,
    0x80000000 | 45,
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
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addSponsor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateSponsor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteSelectedSponsor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchSponsorById'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadSponsoring'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearFields'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearSponsorFields'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSponsorSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_pdfexport_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sort_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_stat_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'drawPieChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QMap<QString,int> &, std::false_type>,
        // method 'getStatusFromTable'
        QtPrivate::TypeAndForceComplete<QMap<QString,int>, std::false_type>,
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
        case 27: _t->addSponsor(); break;
        case 28: _t->updateSponsor(); break;
        case 29: _t->deleteSelectedSponsor(); break;
        case 30: _t->searchSponsorById(); break;
        case 31: _t->loadSponsoring(); break;
        case 32: _t->clearFields(); break;
        case 33: _t->clearSponsorFields(); break;
        case 34: _t->onSponsorSelected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 35: _t->on_pdfexport_clicked(); break;
        case 36: _t->on_sort_clicked(); break;
        case 37: _t->on_pushButton_stat_clicked(); break;
        case 38: _t->drawPieChart((*reinterpret_cast< std::add_pointer_t<QMap<QString,int>>>(_a[1]))); break;
        case 39: { QMap<QString,int> _r = _t->getStatusFromTable();
            if (_a[0]) *reinterpret_cast< QMap<QString,int>*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->openTodoManager(); break;
        case 41: _t->openCalendar(); break;
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
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 42)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 42;
    }
    return _id;
}
QT_WARNING_POP
