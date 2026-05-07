cmake_minimum_required(VERSION 3.20)
project(RESYS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

add_executable(RESYS
        src/main.cpp
        src/mainwindow.cpp
        src/siparisdialog.cpp
        src/siparis_isleyici.cpp
        include/mainwindow.h
        include/siparisdialog.h
        include/siparis_isleyici.h
        include/logindialog.h
)

target_include_directories(RESYS PRIVATE include)
target_link_libraries(RESYS PRIVATE Qt6::Widgets Qt6::Charts)