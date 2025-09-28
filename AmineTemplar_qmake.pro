TEMPLATE = app
TARGET = AmineTemplar
QT += core widgets

CONFIG += c++17

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp

# Header files
HEADERS += \
    mainwindow.h

# UI form files
FORMS += \
    mainwindow.ui \
    Profile.ui \
    Shop.ui \
    projects.ui \
    editor.ui \
    library.ui \
    settings.ui \
    login.ui

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