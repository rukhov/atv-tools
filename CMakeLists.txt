cmake_minimum_required(VERSION 3.26)

project(atv-tools VERSION 1.0.0 LANGUAGES CXX C)

enable_testing()

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

add_subdirectory(src)
