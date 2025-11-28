QT += core widgets sql network multimedia printsupport

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
    ui/templatewidget.cpp \
    ui/clientwidget.cpp \
    ui/sponsorwidget.cpp \
    ui/sponsorwindow.cpp \
    ui/ressourcewidget.cpp \
    ui/projectwidget.cpp \
    ui/facerecognitionwidget.cpp \
    backend/connection.cpp \
    backend/employer.cpp \
    backend/client.cpp \
    backend/ressource.cpp \
    backend/project.cpp \
    backend/sponsor.cpp \
    backend/openai_chatbot.cpp

# Header files
HEADERS += \
    mainwindow.h \
    ui/templatewidget.h \
    ui/clientwidget.h \
    ui/sponsorwidget.h \
    ui/sponsorwindow.h \
    ui/ressourcewidget.h \
    ui/projectwidget.h \
    ui/facerecognitionwidget.h \
    backend/connection.h \
    backend/employer.h \
    backend/client.h \
    backend/ressource.h \
    backend/project.h \
    backend/sponsor.h \
    backend/openai_chatbot.h

# UI forms
FORMS += \
    mainwindow.ui \
    ui/login.ui \
    ui/Profile.ui \
    ui/employerform.ui \
    ui/projectform.ui \
    ui/template.ui \
    ui/client.ui \
    ui/sponsor.ui \
    ui/ressource.ui \
    ui/project.ui

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
*-mingw*:QMAKE_CXXFLAGS += -fno-keep-inline-dllexport
*-mingw*:QMAKE_CXXFLAGS_RELEASE += -O2
*-mingw*:QMAKE_CXXFLAGS_DEBUG += -g

# Disable deprecated warnings
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Include directories
INCLUDEPATH += \
    $$PWD \
    $$PWD/backend \
    $$PWD/ui

# Threading support
CONFIG += thread
