TEMPLATE = app
TARGET = AmineTemplar
QT += core widgets

CONFIG += c++17

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    templatewidget.cpp

# Header files
HEADERS += \
    mainwindow.h \
    templatewidget.h

# UI form files (removed conflicting UI files: projects.ui, editor.ui, library.ui, settings.ui)
FORMS += \
    mainwindow.ui \
    Profile.ui \
    Shop.ui \
    login.ui \
    template.ui

# Resource files
RESOURCES += \
    resources.qrc

# Additional files
OTHER_FILES += \
    style.qss

# Windows-specific settings
win32 {
    TARGET = AmineTemplar.exe
}