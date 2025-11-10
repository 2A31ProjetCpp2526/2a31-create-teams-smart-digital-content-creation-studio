cmake_minimum_required(VERSION 3.22)

project(AmineTemplar LANGUAGES CXX)

# Set C++ standard (Qt6 requires C++17 minimum)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable threading support explicitly
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Set Qt6 path hint (helps CMake find Qt6 more reliably)
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.7.3/mingw_64" ${CMAKE_PREFIX_PATH})
endif()

# Find Qt6 components with better error handling
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

# Verify Qt6 was found correctly
if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 was not found. Please install Qt6 or set CMAKE_PREFIX_PATH correctly.")
endif()

# Automatically handle Qt's MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set AUTOUIC search paths to find .ui files in ui/ directory
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Set build output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    ui/templatewidget.cpp
    ui/clientwidget.cpp
    ui/sponsorwidget.cpp
    ui/ressourcewidget.cpp
    ui/projectwidget.cpp
    backend/connection.cpp
    backend/employer.cpp
    backend/client.cpp
    backend/ressource.cpp
)

# Header files
set(HEADERS
    mainwindow.h
    ui/templatewidget.h
    ui/clientwidget.h
    ui/sponsorwidget.h
    ui/ressourcewidget.h
    ui/projectwidget.h
    backend/connection.h
    backend/employer.h
    backend/client.h
    backend/ressource.h
)

# UI form files
set(UI_FILES
    mainwindow.ui
    ui/Profile.ui
    ui/login.ui
    ui/template.ui
    ui/client.ui
    ui/sponsor.ui
    ui/ressource.ui
    ui/project.ui
    ui/employerform.ui
)

# Resource files
set(RESOURCES
    resources.qrc
)

# Create the executable
add_executable(AmineTemplar
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
    style.qss
)

# Add include directories for new folder structure
target_include_directories(AmineTemplar PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backend
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

# Link Qt6 libraries and threading support
target_link_libraries(AmineTemplar
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Threads::Threads
)

# Compiler-specific options
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(AmineTemplar PRIVATE
        -fno-keep-inline-dllexport
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Release>:-O2>
    )
endif()

# Disable deprecated warnings for Qt6
target_compile_definitions(AmineTemplar PRIVATE
    QT_DISABLE_DEPRECATED_BEFORE=0x060000
)

# Windows-specific settings
if(WIN32)
    set_target_properties(AmineTemplar PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Install target
install(TARGETS AmineTemplar
    DESTINATION bin
)
