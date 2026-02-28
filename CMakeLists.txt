cmake_minimum_required(VERSION 3.16)
project(ninkill VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-DUNICODE -D_UNICODE)
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    src/*.cpp
)
add_executable(ninkill ${SRC})
target_include_directories(ninkill PRIVATE include)
if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    target_link_libraries(ninkill PRIVATE
        User32
        Gdi32
        Shell32
        Advapi32
    )
else()
    find_package(Threads REQUIRED)
    target_link_libraries(ninkill PRIVATE Threads::Threads)
endif()
target_compile_options(ninkill PRIVATE
    $<$<CONFIG:Release>:-O2>
)
target_link_options(ninkill PRIVATE
    $<$<CONFIG:Release>:-s>
)