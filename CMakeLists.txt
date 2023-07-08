cmake_minimum_required(VERSION 3.16)
project(LetItOut)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (WIN32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_add_resources(QT_RESOURCES resources.qrc)
qt6_wrap_cpp(MOC_SOURCES mainwindow.h)

if (WIN32)
    add_executable(LetItOut WIN32 main.cpp mainwindow.cpp ${MOC_SOURCES} ${QT_RESOURCES})
elseif(UNIX)
    add_executable(LetItOut main.cpp mainwindow.cpp ${MOC_SOURCES} ${QT_RESOURCES})
endif()
target_link_libraries(LetItOut PRIVATE Qt6::Widgets)
