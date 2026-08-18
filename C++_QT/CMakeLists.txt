cmake_minimum_required(VERSION 3.16)

project(ElevatorSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(ElevatorSimulator WIN32
    main.cpp
    elevator.cpp
    elevator.h
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(ElevatorSimulator
    Qt6::Widgets
)