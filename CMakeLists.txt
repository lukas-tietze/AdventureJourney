cmake_minimum_required (VERSION 3.6.2)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Creating release build")
    option(DEBUG "Debug build" OFF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Creating debug build")
    option(DEBUG "Debug build" ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wswitch-default -Wswitch-enum")
endif()

project (Test)
file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE TESTS "test/**/*.cpp")
file(GLOB_RECURSE LIB "lib/**/*.cpp")

include_directories(include)
include_directories(test)
include_directories(src)

configure_file(include/config.in.hpp include/config.hpp)

add_library(COMMON STATIC ${LIB})

add_executable(Test test/main.cpp ${TESTS})
target_link_libraries(Test COMMON)
