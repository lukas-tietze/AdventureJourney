#--------------------------------------------------------
# General
#--------------------------------------------------------
cmake_minimum_required (VERSION 3.6.2)

include(build.cfg OPTIONAl RESULT_VARIABLE CFG_FOUND)

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
Set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_package(glfw3)
find_package(glm)
find_package(Boost REQUIRED)

if(Boost_FOUND)
message("Found Boost ${Boost_VERSION}")
endif()

add_definitions( -DCMAKE_EXE_LINKER_FLAGS=-ldl)

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

include_directories(common/include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CURSES_INCLUDE_DIRS})

add_library(Common STATIC ${COMMON_SRC})

target_link_libraries(Common ${CURSES_LIBRARIES})
target_link_libraries(Common ${Boost_LIBRARIES})

#Tests dazu
if(NOT CFGFOUND OR COMPILE_TESTS)
    project(CommonTests)

    include_directories(common/include)
    include_directories(common/test)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(CommonTests common/test/main.cpp ${COMMON_TESTS})

    target_link_libraries(CommonTests ${Boost_LIBRARIES})
    target_link_libraries(CommonTests backtrace)
    target_link_libraries(CommonTests Common)
    target_link_libraries(CommonTests Threads::Threads)
else()
    message("Skipping CommonTests")
endif()
#--------------------------------------------------------
# Playground
#--------------------------------------------------------
if(NOT CFGFOUND OR COMPILE_PLAYGROUND)
    project (Playground)

    include_directories(common/include)
    include_directories(playground)

    add_executable(Playground playground/main.cpp)

    target_link_libraries(Playground Common)
else()
    message("Skipping playground")
endif()

#--------------------------------------------------------
# Core
#--------------------------------------------------------
project(Core)

include_directories(common/include)
include_directories(core/include)

add_library(Core core/src/main.cpp ${CORE_SRC})
target_link_libraries(Common ${Boost_LIBRARIES})

target_link_libraries(Core Common)
target_link_libraries(Core Threads::Threads)
target_link_libraries(Core ${Boost_INCLUDE_DIRS})
#Tests dazu
if(NOT CFGFOUND OR COMPILE_TESTS)
    project(CoreTests)

    include_directories(common/include)
    include_directories(core/include)
    include_directories(core/test)

    add_executable(CoreTests core/test/main.cpp ${CORE_TESTS})

    target_link_libraries(CoreTests Common)
    target_link_libraries(CoreTests Core)
    target_link_libraries(CoreTests Threads::Threads)
else()
    message("Skipping CoreTests")
endif()

#--------------------------------------------------------
# Terminal UI - Stellt das Spiel in einer einfachen Form im Terminal dar
#--------------------------------------------------------
if(NOT CFGFOUND OR COMPILE_TUI)
    project(TerminalUi)

    configure_file(terminal_ui/include/config.in.hpp terminal_ui/include/config.hpp)

    include_directories(common/include)
    include_directories(core/include)
    include_directories(${CURSES_INCLUDE_DIRS})
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(TerminalUi terminal_ui/src/main.cpp ${TUI_SRC})

    target_link_libraries(TerminalUi Common)
    target_link_libraries(TerminalUi Core)
    target_link_libraries(TerminalUi Threads::Threads)
    target_link_libraries(TerminalUi ${Boost_LIBRARIES})
    target_link_libraries(TerminalUi ${CURSES_LIBRARIES})
    #Tests dazu
    project(TerminalUiTests)

    include_directories(common/include)
    include_directories(core/include)
    include_directories(core/test)
    include_directories(${CURSES_INCLUDE_DIRS})

    add_executable(TerminalUiTests terminal_ui/test/main.cpp ${TUI_TESTS})

    target_link_libraries(TerminalUiTests Common)
    target_link_libraries(TerminalUiTests Core)
    target_link_libraries(TerminalUiTests Threads::Threads)
    target_link_libraries(TerminalUiTests ${CURSES_LIBRARIES})
else()
    message("Skipping TerminalUi")
endif()
#--------------------------------------------------------
# Vulkan GUI - Grafische UI mittels Vulkan
#--------------------------------------------------------
if(NOT CFGFOUND OR COMPILE_GUI)
    if(glfw3_FOUND)
        if(glm_FOUND)
            project(VulkanGui)

            configure_file(terminal_ui/include/config.in.hpp terminal_ui/include/config.hpp)
            
            include_directories(common/include)
            include_directories(core/include)
            include_directories(${VULKAN_INCLUDE_DIRS})
            include_directories(${Boost_INCLUDE_DIRS})
            
            add_executable(VulkanGui terminal_ui/src/main.cpp ${GUI_SRC})
            
            target_link_libraries(VulkanGui Common)
            target_link_libraries(VulkanGui Core)
            target_link_libraries(VulkanGui Threads::Threads)
            target_link_libraries(VulkanGui ${VULKAN_LIBRARIES})
            target_link_libraries(VulkanGui ${Boost_LIBRARIES})
            #Tests dazu
            project(VulkanGuiTests)
            
            include_directories(common/include)
            include_directories(core/include)
            include_directories(core/test)
            include_directories(${VULKAN_INCLUDE_DIRS})
            
            add_executable(VulkanGuiTests terminal_ui/test/main.cpp ${GUI_TESTS})
            
            target_link_libraries(VulkanGuiTests Common)
            target_link_libraries(VulkanGuiTests Core)
            target_link_libraries(VulkanGuiTests Threads::Threads)
            target_link_libraries(VulkanGuiTests ${VULKAN_LIBRARIES})
        else()
            message("Can't build GUI, glm is missing!")
        endif()
    else()
        message("Can't build GUI, glfw3 is missing!")
    endif()
else()
    message("Skipping VulkanGui")
endif()
