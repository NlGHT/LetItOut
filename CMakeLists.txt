cmake_minimum_required(VERSION 3.16)
project(LetItOut)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# https://stackoverflow.com/a/71321163
SET(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

add_subdirectory(framelesshelper)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Add the source files to the target using file globbing
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

# Add the Windows-specific icon resource file
if (WIN32)
    set(WINDOWS_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/letitout.rc")
    list(APPEND SOURCES ${WINDOWS_ICON_RESOURCE})
endif()

qt6_add_resources(QT_RESOURCES resources/resources.qrc)
# Generate the MOC files
qt6_wrap_cpp(MOC_SOURCES src/mainwindow.h src/customtitlebar.h)

# Create the executable target
if (WIN32)
    add_executable(LetItOut WIN32 ${SOURCES} ${MOC_SOURCES} ${QT_RESOURCES})
else()
    add_executable(LetItOut ${SOURCES} ${MOC_SOURCES} ${QT_RESOURCES})
endif()

# Link libraries and include directories
target_link_libraries(LetItOut PRIVATE
    Qt6::Widgets
    FramelessHelper::Core
    FramelessHelper::Widgets
)

target_include_directories(LetItOut PRIVATE
    src
)

if (WIN32)
    set(CMAKE_RC_COMPILER_INIT windres)
    enable_language(RC)
    set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")

    # Add the WIN32 flag to the executable (Windows-specific)
    target_compile_definitions(LetItOut PRIVATE
        WIN32
    )

    set(FRAMELESSHELPER_DLLS_DIR "${CMAKE_CURRENT_BINARY_DIR}/framelesshelper/bin64")

    # Copy framelesshelper DLLs after the build
    add_custom_command(TARGET LetItOut POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${FRAMELESSHELPER_DLLS_DIR}"
        $<TARGET_FILE_DIR:LetItOut>
    )
endif()
