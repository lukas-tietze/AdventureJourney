#--------------------------------------------------------
# General
#--------------------------------------------------------

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

enable_language(CXX)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
# find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE TESTS "test/**/*.cpp")
file(GLOB_RECURSE LIB "lib/**/*.cpp")

#--------------------------------------------------------
# Library
#--------------------------------------------------------
project(Common)
configure_file(include/config.in.hpp include/config.hpp)
add_library(COMMON STATIC ${LIB})

#--------------------------------------------------------
# Test
#--------------------------------------------------------
project (Test)
include_directories(include)
include_directories(test)
include_directories(src)
# include_directories(Vulkan_INLCUDE_DIRS)

add_executable(Test test/main.cpp ${TESTS})
target_link_libraries(Test COMMON)
target_link_libraries(Test ncurses)
target_link_libraries(Test Threads::Threads)
# target_link_libraries(Test Vulkan_LIBRARIES)

#--------------------------------------------------------
# Runtime
#--------------------------------------------------------

project(Runtime)

include_directories(include)
include_directories(src)
# include_directories(Vulkan_INLCUDE_DIRS)

add_executable(Runtime src/main.cpp ${SORUCES})
target_link_libraries(Runtime COMMON)
target_link_libraries(Runtime ncurses)
target_link_libraries(Runtime Threads::Threads)
# target_link_libraries(Runtime Vulkan_LIBRARIES)
