cmake_minimum_required(VERSION 3.16)
project(PasswordManager VERSION 1.2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Network)

qt_add_executable(PasswordManager
    main.cpp
    mainwindow.h mainwindow.cpp
    databasemanager.h databasemanager.cpp
)

target_link_libraries(PasswordManager PRIVATE Qt6::Widgets Qt6::Sql Qt6::Network)
