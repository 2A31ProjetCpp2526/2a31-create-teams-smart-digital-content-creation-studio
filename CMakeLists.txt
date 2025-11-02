cmake_minimum_required(VERSION 3.22)

project(AmineTemplar LANGUAGES CXX)

# -------------------------------
# Qt and C++ setup
# -------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# -------------------------------
# Threading support
# -------------------------------
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# -------------------------------
# Help CMake find your Qt6 install (adjust path if needed)
# -------------------------------
if(WIN32)
    # Change this if your Qt is in a different location
    set(CMAKE_PREFIX_PATH "C:/Qt/6.7.3/mingw_64" ${CMAKE_PREFIX_PATH})
endif()

# -------------------------------
# Find Qt6 modules
# -------------------------------
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 was not found. Please install Qt6 or set CMAKE_PREFIX_PATH correctly.")
endif()

# -------------------------------
# Output directories
# -------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# -------------------------------
# Source files
# -------------------------------
set(SOURCES
    main.cpp
    mainwindow.cpp
    templatewidget.cpp
    clientwidget.cpp
    sponsorwidget.cpp
    ressourcewidget.cpp
    projectwidget.cpp
    connection.cpp
)

# -------------------------------
# Header files
# -------------------------------
set(HEADERS
    mainwindow.h
    templatewidget.h
    clientwidget.h
    sponsorwidget.h
    ressourcewidget.h
    projectwidget.h
    connection.h
)

# -------------------------------
# UI files
# -------------------------------
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

# -------------------------------
# Resource files (fonts, qss, etc.)
# -------------------------------
set(RESOURCES
    resources.qrc
    style.qss
)

# -------------------------------
# Create the executable
# -------------------------------
add_executable(AmineTemplar
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

# -------------------------------
# Link Qt and threading
# -------------------------------
target_link_libraries(AmineTemplar
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Threads::Threads
)

# -------------------------------
# Compiler options (Windows)
# -------------------------------
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(AmineTemplar PRIVATE
        -fno-keep-inline-dllexport
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Release>:-O2>
    )
endif()

# -------------------------------
# Define for disabling deprecated Qt APIs
# -------------------------------
target_compile_definitions(AmineTemplar PRIVATE
    QT_DISABLE_DEPRECATED_BEFORE=0x060000
)

# -------------------------------
# Windows executable property
# -------------------------------
if(WIN32)
    set_target_properties(AmineTemplar PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# -------------------------------
# Install target
# -------------------------------
install(TARGETS AmineTemplar
    DESTINATION bin
)
