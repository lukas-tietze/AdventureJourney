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
find_package(glfw3)
find_package(glm)

#Common
file(GLOB_RECURSE COMMON_SRC "common/lib/**/*.cpp")
file(GLOB_RECURSE COMMON_TESTS "common/test/**/*.cpp")
#Core
file(GLOB_RECURSE CORE_SRC "core/src/**/*.cpp")
file(GLOB_RECURSE CORE_TESTS "core/src/**/*.cpp")
#Terminal
file(GLOB_RECURSE TERMINALUI_SRC "terminal_ui/src/**/*.cpp")
file(GLOB_RECURSE TERMINALUI_TESTS "terminal_ui/src/**/*.cpp")
#Vulkan
file(GLOB_RECURSE VULKANGUI_SRC "vulkan_gui/src/**/*.cpp")
file(GLOB_RECURSE VULKANGUI_TESTS "vulkan_gui/src/**/*.cpp")

#--------------------------------------------------------
# Library - enthält Utils und Wrapper, die in verschiedenen Projekten genutzt werden könnten.
#--------------------------------------------------------
project(Common)
configure_file(common/include/config.in.hpp common/include/config.hpp)
include_directories(common/include)
add_library(Common STATIC ${COMMON_SRC})

#Tests dazu
project(CommonTests)
include_directories(common/include)
add_executable(CommonTests ${COMMON_TESTS})
target_link_libraries(CommonTests COMMON_SRC)

#--------------------------------------------------------
# Playground
#--------------------------------------------------------
project (Playground)
include_directories(common/include)
include_directories(playground)

add_executable(Playground playground/main.cpp)
target_link_libraries(Playground Common)
target_link_libraries(Playground ncurses)
target_link_libraries(Playground Threads::Threads)

#--------------------------------------------------------
# Core
#--------------------------------------------------------
project(Core)

include_directories(common/include)
include_directories(core/include)

add_library(Core core/src/main.cpp ${CORE_SRC})
target_link_libraries(Core Common)
target_link_libraries(Core Threads::Threads)
#Tests dazu
project(CoreTests)

include_directories(common/include)
include_directories(core/include)
include_directories(core/test)

add_executable(CoreTests core/test/main.cpp ${CORE_TESTS})
target_link_libraries(CoreTests Common)
target_link_libraries(CoreTests Core)
target_link_libraries(CoreTests Threads::Threads)