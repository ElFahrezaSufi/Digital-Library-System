cmake_minimum_required(VERSION 3.16)

project(LibraSys VERSION 1.0.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt Configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Try Qt6 first, fallback to Qt5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Source Files
set(PROJECT_SOURCES
    src/main.cpp
    src/UI/MainWindow.cpp
    src/UI/MainWindow.h
    src/UI/Components/BookCard.cpp
    src/UI/Components/BookCard.h
    src/UI/Components/NavBar.cpp
    src/UI/Components/NavBar.h
    src/Models/Book.h
    src/Models/DataStore.h
    src/Models/LibraryEngine.h
    src/Models/LibraryEngine.cpp
    src/Utils/StyleLoader.h
    src/Utils/StyleLoader.cpp
)

# Resource Files
set(PROJECT_RESOURCES
    Resources/resources.qrc
)

# Executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LibraSys
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
else()
    add_executable(LibraSys
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
endif()

# Link Qt Libraries
target_link_libraries(LibraSys PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Include Directories
target_include_directories(LibraSys PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils
)

# Platform-specific settings
if(WIN32)
    set_target_properties(LibraSys PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Finalization for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LibraSys)
endif()
