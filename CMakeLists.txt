cmake_minimum_required(VERSION 3.16)
project(LetItOut)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_add_resources(QT_RESOURCES resources.qrc)
qt6_wrap_cpp(MOC_SOURCES mainwindow.h customtitlebar.h)
set(WINDOWS_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/letitout.rc")

if (WIN32)
    set(CMAKE_RC_COMPILER_INIT windres)
    enable_language(RC)
    set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
    add_executable(LetItOut WIN32 main.cpp mainwindow.cpp customtitlebar.cpp ${MOC_SOURCES} ${QT_RESOURCES} ${WINDOWS_ICON_RESOURCE})
    target_sources(LetItOut PRIVATE ${WINDOWS_ICON_RESOURCE})
elseif(UNIX)
    add_executable(LetItOut main.cpp mainwindow.cpp customtitlebar.cpp ${MOC_SOURCES} ${QT_RESOURCES})
endif()
target_link_libraries(LetItOut PRIVATE Qt6::Widgets)
