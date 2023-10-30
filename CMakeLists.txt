cmake_minimum_required(VERSION 3.26)
project(Notepad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Notepad main.cpp
        Pad.cpp
        Pad.h
        Text.cpp
        Text.h
        header.h
)
target_link_libraries(Notepad
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

