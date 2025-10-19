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
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Verify Qt6 was found correctly
if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 was not found. Please install Qt6 or set CMAKE_PREFIX_PATH correctly.")
endif()

# Automatically handle Qt's MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set build output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    templatewidget.cpp
    clientwidget.cpp
    sponsorwidget.cpp
    ressourcewidget.cpp
    projectwidget.cpp
)

# Header files
set(HEADERS
    mainwindow.h
    templatewidget.h
    clientwidget.h
    sponsorwidget.h
    ressourcewidget.h
    projectwidget.h
)

# UI form files
set(UI_FILES
    mainwindow.ui
    Profile.ui
    login.ui
    template.ui
    client.ui
    sponsor.ui
    ressource.ui
    project.ui
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

# Link Qt6 libraries and threading support
target_link_libraries(AmineTemplar
    Qt6::Core
    Qt6::Widgets
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