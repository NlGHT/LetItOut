cmake_minimum_required(VERSION 3.16)
project(LetItOut)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_wrap_cpp(MOC_SOURCES mainwindow.h)

add_executable(LetItOut main.cpp mainwindow.cpp ${MOC_SOURCES})
target_link_libraries(LetItOut PRIVATE Qt6::Widgets)
