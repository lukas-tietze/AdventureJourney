#--------------------------------------------------------
# General
#--------------------------------------------------------
cmake_minimum_required (VERSION 2.8)

set(COMPILE_GUI on)
set(COMPILE_TESTS on)
set(COMPILE_PLAYGROUND on)
set(COMPILE_TESTS on)
set(COMPILE_TUI on)
set(COMPILE_GUI on)

include(compile.cfg OPTIONAl)
include(ExternalData)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Creating release build")
    option(DEBUG "Debug build" OFF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Creating debug build")
    option(DEBUG "Debug build" ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wswitch-default -Wswitch-enum -g")
endif()

enable_language(CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

Set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

find_package(glfw3)

find_package(glm)

#workaround https://gitlab.kitware.com/cmake/cmake/issues/17297
set(_Boost_STACKTRACE_BASIC_HEADERS     "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_BACKTRACE_HEADERS "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_ADDR2LINE_HEADERS "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_NOOP_HEADERS      "boost/stacktrace.hpp")
find_package(Boost 1.65.0 COMPONENTS stacktrace_basic stacktrace_backtrace stacktrace_addr2line stacktrace_noop)

include_directories(${CURSES_INCLUDE_DIRS})
include_directories(${VULKAN_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(common/include)
include_directories(core/include)
include_directories(playground)
include_directories(terminal_ui/include)
include_directories(vulkan_gui/include)

message(STATUS "Boost_VERSION=" ${Boost_VERSION})

if(glfw3_FOUND)
    include_directories(${Glfw_INCLUDE_DIRS})
else()
    message("Could not find glfw3!")
endif()

if(glm_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
else()
    message("Could not find glm!")
endif()

#Common
file(GLOB_RECURSE COMMON_SRC "common/src/**/*.cpp")
file(GLOB_RECURSE COMMON_TESTS "common/test/**/*.cpp")
#Core
file(GLOB_RECURSE CORE_SRC "core/src/**/*.cpp")
file(GLOB_RECURSE CORE_TESTS "core/test/**/*.cpp")
#Terminal
file(GLOB_RECURSE TUI_SRC "terminal_ui/src/**/*.cpp")
file(GLOB_RECURSE TUI_TESTS "terminal_ui/test/**/*.cpp")
#Vulkan
file(GLOB_RECURSE GUI_SRC "vulkan_gui/src/**/*.cpp")
file(GLOB_RECURSE GUI_TESTS "vulkan_gui/test/**/*.cpp")

#--------------------------------------------------------
# Library - enthält Utils und Wrapper, die in verschiedenen Projekten genutzt werden könnten.
#--------------------------------------------------------
project(Common)

configure_file(common/include/config.in.hpp common/include/config.hpp)
add_library(Common STATIC ${COMMON_SRC})
target_link_libraries(Common ${CURSES_LIBRARIES} ${Boost_LIBRARIES})

#Tests dazu
if(COMPILE_TESTS)
    project(CommonTests)
    add_executable(CommonTests common/test/main.cpp ${COMMON_TESTS})
    target_link_libraries(CommonTests ${Boost_LIBRARIES} Common Threads::Threads)
else()
    message("Skipping CommonTests")
endif()
#--------------------------------------------------------
# Playground
#--------------------------------------------------------
if(COMPILE_PLAYGROUND)
    project (Playground)
    add_executable(Playground playground/main.cpp)
    target_link_libraries(Playground Common)
else()
    message("Skipping playground")
endif()

#--------------------------------------------------------
# Core
#--------------------------------------------------------
project(Core)
add_library(Core core/src/main.cpp ${CORE_SRC})
target_link_libraries(Core Common Threads::Threads ${Boost_LIBRARIES})
#Tests dazu
if(COMPILE_TESTS)
    project(CoreTests)
    add_executable(CoreTests core/test/main.cpp ${CORE_TESTS})
    target_link_libraries(CoreTests Common Core)
else()
    message("Skipping CoreTests")
endif()

#--------------------------------------------------------
# Terminal UI - Stellt das Spiel in einer einfachen Form im Terminal dar
#--------------------------------------------------------
if(COMPILE_TUI)
    project(TerminalUi)
    configure_file(terminal_ui/include/config.in.hpp terminal_ui/include/config.hpp)
    add_executable(TerminalUi terminal_ui/src/main.cpp ${TUI_SRC})
    target_link_libraries(TerminalUi Common Core ${Boost_LIBRARIES} ${CURSES_LIBRARIES})
    
    #Tests dazu
    project(TerminalUiTests)
    add_executable(TerminalUiTests terminal_ui/test/main.cpp ${TUI_TESTS})
    target_link_libraries(TerminalUiTests Common Core Threads::Threads ${CURSES_LIBRARIES})
else()
    message("Skipping TerminalUi")
endif()
#--------------------------------------------------------
# Vulkan GUI - Grafische UI mittels Vulkan
#--------------------------------------------------------
if(COMPILE_GUI)
    if(glfw3_FOUND)
        if(glm_FOUND)
            project(VulkanGui)
            configure_file(terminal_ui/include/config.in.hpp terminal_ui/include/config.hpp)
            add_executable(VulkanGui terminal_ui/src/main.cpp ${GUI_SRC})
            target_link_libraries(VulkanGui Common Core Threads::Threads ${VULKAN_LIBRARIES} ${Boost_LIBRARIES} glfw ${glm_LIBRARIES})

            #Tests dazu
            project(VulkanGuiTests)
            add_executable(VulkanGuiTests terminal_ui/test/main.cpp ${GUI_TESTS})
            target_link_libraries(VulkanGuiTests Common Core ${VULKAN_LIBRARIES} glfw ${glm_LIBRARIES} Threads::Threads)
        else()
            message("Can't build GUI, glm is missing!")
        endif()
    else()
        message("Can't build GUI, glfw3 is missing!")
    endif()
else()
    message("Skipping VulkanGui")
endif()
