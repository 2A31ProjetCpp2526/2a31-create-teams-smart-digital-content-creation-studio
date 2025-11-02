QT += core widgets
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
    templatewidget.cpp

# Header files  
HEADERS += \
    mainwindow.h \
    templatewidget.h

# UI forms (removed conflicting UI files: projects.ui, editor.ui, library.ui, settings.ui)
FORMS += \
    mainwindow.ui \
    Profile.ui \
    Shop.ui \
    login.ui \
    template.ui

# Resources
RESOURCES += \
    resources.qrc

# Additional files
OTHER_FILES += \
    style.qss

# Build directories
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/build/debug
    OBJECTS_DIR = $$PWD/build/debug/obj
    MOC_DIR = $$PWD/build/debug/moc
    RCC_DIR = $$PWD/build/debug/rcc
    UI_DIR = $$PWD/build/debug/ui
}

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/build/release
    OBJECTS_DIR = $$PWD/build/release/obj
    MOC_DIR = $$PWD/build/release/moc
    RCC_DIR = $$PWD/build/release/rcc
    UI_DIR = $$PWD/build/release/ui
}

# Disable deprecated warnings
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Windows-specific configuration
win32 {
    CONFIG += qt
    
    # Compiler settings for MinGW
    *-g++* {
        QMAKE_CXXFLAGS += -fno-keep-inline-dllexport
        QMAKE_CXXFLAGS_RELEASE += -O2
        QMAKE_CXXFLAGS_DEBUG += -g
    }
}
