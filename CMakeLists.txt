cmake_minimum_required(VERSION 3.16)

project(SecureVault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
)

qt_add_executable(SecureVault ${PROJECT_SOURCES})

target_link_libraries(SecureVault PRIVATE Qt6::Widgets)
