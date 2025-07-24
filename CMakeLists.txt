# PROJECT_IS_TOP_LEVEL need 3.21 or later
cmake_minimum_required(VERSION 3.21)

option(PRETTY_SERIALIZE "Pretty xml output" ON)
option(TEST_TMPOFD "Enable test" OFF)

# project version
set(TMPOFD_VERSION_MAJOR 0)
set(TMPOFD_VERSION_MINOR 1)
set(TMPOFD_VERSION_PATCH 0)
if (WIN32)
    execute_process(
            COMMAND "powershell" "-Command" "Get-Date -Format 'yyyyMMddHHmmss'"
            OUTPUT_VARIABLE TMPOFD_VERSION_TIMESTAMP
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else ()
    execute_process(
            COMMAND date "+%Y%m%d%H%M%S"
            OUTPUT_VARIABLE TMPOFD_VERSION_TIMESTAMP
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif ()
set(TMPOFD_VERSION ${TMPOFD_VERSION_MAJOR}.${TMPOFD_VERSION_MINOR}.${TMPOFD_VERSION_PATCH}.${TMPOFD_VERSION_TIMESTAMP})
set(TMPOFD_VERSION_STRING "${TMPOFD_VERSION}")

project(tmpofd VERSION ${TMPOFD_VERSION} LANGUAGES CXX)
message(STATUS "Build ${PROJECT_NAME} ${TMPOFD_VERSION_STRING} on ${CMAKE_SYSTEM_NAME} ${CMAKE_CXX_COMPILER}")

# replace version & time in version.h
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/templates/version.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/version.h"
        @ONLY
)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
endif ()

include_directories(${PROJECT_SOURCE_DIR})

if (PRETTY_SERIALIZE)
    add_definitions(-DPRETTY_SERIALIZE)
endif ()

if (DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
else ()
    message(FATAL_ERROR "Vcpkg toolchain not set!")
endif ()

find_package(unofficial-skia CONFIG REQUIRED)

if (PROJECT_IS_TOP_LEVEL)
    set(TEST_TMPOFD ON CACHE BOOL "Build ${PROJECT_NAME} test" FORCE)
endif ()

if (TEST_TMPOFD)
    enable_testing()
    add_subdirectory(tests)
endif ()
