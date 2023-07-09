cmake_minimum_required(VERSION 3.16)
project(LetItOut)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_add_resources(QT_RESOURCES resources.qrc)
qt6_wrap_cpp(MOC_SOURCES mainwindow.h)

if (WIN32)
    add_executable(LetItOut WIN32 main.cpp mainwindow.cpp ${MOC_SOURCES} ${QT_RESOURCES})
elseif(UNIX)
    add_executable(LetItOut main.cpp mainwindow.cpp ${MOC_SOURCES} ${QT_RESOURCES})
endif()
target_link_libraries(LetItOut PRIVATE Qt6::Widgets)
