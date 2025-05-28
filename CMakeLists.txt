cmake_minimum_required(VERSION 3.26)

project(atv-tools VERSION 1.0.0 LANGUAGES CXX C)

option(BUILD_GNURADIO_BLOCKS "Build the gnuradio blocks" ON)

set( CMAKE_MESSAGE_LOG_LEVEL VERBOSE )
#set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

enable_testing()

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)

set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS Off)

if(UNIX)
    add_compile_options( -fPIC -flto=auto)
    if( CMAKE_BUILD_TYPE STREQUAL Debug )
        add_compile_options( -g3 -O0)
    endif()
elseif(WIN32)
    add_compile_definitions("BOOST_USE_WINAPI_VERSION=0x0602")
    add_compile_definitions("_WIN32_WINNT=0x0602")
    add_compile_definitions("BOOST_PROCESS_VERSION=2")
    string(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
    string(REPLACE "/Ob1" "/Ob0" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
endif()

include(cmake/FindLibAtvTools.cmake)
include(cmake/FindRTSPServerTemplate.cmake)

add_subdirectory(src)
