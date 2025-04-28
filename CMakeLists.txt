cmake_minimum_required(VERSION 3.16)
project(impp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/DropArea.cpp
    src/ImageConverter.cpp
    include/MainWindow.h
    include/DropArea.h
    include/ImageConverter.h
)

add_executable(impp ${PROJECT_SOURCES})

target_include_directories(impp PRIVATE include)
target_link_libraries(impp PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)