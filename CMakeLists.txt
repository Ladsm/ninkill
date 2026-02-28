cmake_minimum_required(VERSION 3.10)
project(ninkill VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
add_definitions(-DUNICODE -D_UNICODE)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)
add_executable(ninkill ${SRC_FILES})
target_include_directories(ninkill PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(ninkill PRIVATE Threads::Threads)
else()
    enable_language(RC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    target_link_libraries(ninkill PRIVATE
        User32
        Gdi32
        Shell32
        Advapi32
    )
endif()
target_compile_options(ninkill PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang>>:-O2 -s>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 /GL>
)

target_link_options(ninkill PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang>>:-s>
)