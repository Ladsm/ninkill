cmake_minimum_required(VERSION 3.10)
project(ninkill VERSION 1.0)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DUNICODE -D_UNICODE)
set(PROJECT_SOURCES
src/main.cpp
src/usrAndPass.cpp
src/usrAndPass.hpp
src/boot.cpp
src/boot.hpp
src/beep.h
src/consolestart.cpp
src/consolestart.hpp
src/ninkill.cpp
src/ninkill.hpp
src/userinput.cpp
src/userinput.hpp
src/page.cpp
src/page.hpp
src/savefile.cpp
src/savefile.hpp
src/website.cpp
src/website.hpp
src/obfstr.hpp
)
add_executable(ninkill ${PROJECT_SOURCES})
if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(ninkill PRIVATE Threads::Threads)
else()
    enable_language(RC)
    target_link_libraries(ninkill PRIVATE
        User32
        Gdi32
        Shell32
        Advapi32
    )
endif()
target_include_directories(ninkill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(ninkill PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang>>:-O2 -s>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 /GL>
)
target_link_options(ninkill PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang>>:-s>
)