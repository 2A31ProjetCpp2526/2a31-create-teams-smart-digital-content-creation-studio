cmake_minimum_required(VERSION 3.28)

# Project declaration
project(AmineTemplar LANGUAGES CXX)

# Qt configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    Sql
    REQUIRED
)

# Source files - Main application
set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    style.qss
    resources.qrc
)

# Backend source files
set(BACKEND_SOURCES
    backend/connection.cpp
    backend/connection.h
    backend/employer.cpp
    backend/employer.h
    backend/client.cpp
    backend/client.h
    backend/ressource.cpp
    backend/ressource.h
)

# UI source files
set(UI_SOURCES
    ui/ressourcewidget.cpp
    ui/ressourcewidget.h
)

# Combine all sources
set(ALL_SOURCES ${SOURCES} ${BACKEND_SOURCES} ${UI_SOURCES})

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backend
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

# Resource files
qt_add_resources(${PROJECT_NAME} "resources" FILES resources.qrc)
