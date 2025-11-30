QT += core widgets sql

# Project configuration
TARGET = AmineTemplar
TEMPLATE = app

# C++ standard
CONFIG += c++17
CONFIG -= c++11 c++14 c++1z c++2a c++20

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ui/ressourcewidget.cpp \
    backend/connection.cpp \
    backend/employer.cpp \
    backend/client.cpp \
    backend/ressource.cpp

# Header files
HEADERS += \
    mainwindow.h \
    ui/ressourcewidget.h \
    backend/connection.h \
    backend/employer.h \
    backend/client.h \
    backend/ressource.h

# UI forms
FORMS += \
    mainwindow.ui

# Resources
RESOURCES += resources.qrc

# Additional files
OTHER_FILES += style.qss

# Build directories (debug/release)
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/build/debug
    OBJECTS_DIR = $$PWD/build/debug/obj
    MOC_DIR     = $$PWD/build/debug/moc
    RCC_DIR     = $$PWD/build/debug/rcc
    UI_DIR      = $$PWD/build/debug/ui
}

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/build/release
    OBJECTS_DIR = $$PWD/build/release/obj
    MOC_DIR     = $$PWD/build/release/moc
    RCC_DIR     = $$PWD/build/release/rcc
    UI_DIR      = $$PWD/build/release/ui
}

# Compiler-specific flags for MinGW (Windows)
win32:CONFIG += qt
*--mingw*:QMAKE_CXXFLAGS += -fno-keep-inline-dllexport
*--mingw*:QMAKE_CXXFLAGS_RELEASE += -O2
*--mingw*:QMAKE_CXXFLAGS_DEBUG += -g

# Disable deprecated warnings
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Include directories (like target_include_directories)
INCLUDEPATH += \
    $$PWD \
    $$PWD/backend \
    $$PWD/ui

# Threading support
CONFIG += thread
