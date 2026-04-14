cmake_minimum_required(VERSION 3.16)

project(PasswordManager VERSION 1.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    databasemanager.h
    databasemanager.cpp
)

qt_add_executable(PasswordManager ${PROJECT_SOURCES})

target_link_libraries(PasswordManager PRIVATE Qt6::Widgets Qt6::Sql)
