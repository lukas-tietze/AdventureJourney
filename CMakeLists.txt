#--------------------------------------------------------
# General
#--------------------------------------------------------
cmake_minimum_required (VERSION 3.7)

set(COMPILE_GUI on)
set(COMPILE_TESTS on)
set(COMPILE_PLAYGROUND on)
set(COMPILE_TESTS on)
set(COMPILE_TUI on)
set(COMPILE_GUI on)

include(compile.cfg OPTIONAl)
include(ExternalData) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_ENABLE_EXPERIMENTAL")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Creating release build")
    option(DEBUG "Debug build" OFF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    message("Creating debug build")
    option(DEBUG "Debug build" ON)

    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wswitch-default -Wswitch-enum -g")
    endif()
endif()

set(CMAKE_BUILD_TYPE Debug)

enable_language(CXX)

Set(CURSES_NEED_NCURSES TRUE)
find_package(Curses)
 
#workaround https://gitlab.kitware.com/cmake/cmake/issues/17297
set(_Boost_STACKTRACE_BASIC_HEADERS     "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_BACKTRACE_HEADERS "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_ADDR2LINE_HEADERS "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_NOOP_HEADERS      "boost/stacktrace.hpp")
find_package(Boost 1.65.0 COMPONENTS stacktrace_backtrace filesystem chrono thread REQUIRED)

#external includes
include_directories(${Boost_INCLUDE_DIRS})

#libs/submodules
include_directories(libs/glad/include)
include_directories(submodules/glfw/include)
include_directories(submodules/glm/)
include_directories(submodules/stb)

#projects
include_directories(common/include)
include_directories(core/include)
include_directories(playground)
include_directories(terminal_ui/include)
include_directories(gui/include)
include_directories(.)

add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
add_definitions(-DBOOST_STACKTRACE_LINK)
add_definitions(-DBOOST_STACKTRACE_USE_BACKTRACE)

#Common
file(GLOB_RECURSE COMMON_SRC "common/src/**/*.cpp")
file(GLOB_RECURSE COMMON_TESTS "common/test/**/*.cpp")
#Core
file(GLOB_RECURSE CORE_SRC "core/src/**/*.cpp")
file(GLOB_RECURSE CORE_TESTS "core/test/**/*.cpp")
#Terminal
file(GLOB_RECURSE TUI_SRC "terminal_ui/src/**/*.cpp")
file(GLOB_RECURSE TUI_TESTS "terminal_ui/test/**/*.cpp")
#Gui
file(GLOB_RECURSE GUI_SRC "gui/src/**/*.cpp")
file(GLOB_RECURSE GUI_TESTS "gui/test/**/*.cpp")

#--------------------------------------------------------
# Library - enthält Utils und Wrapper, die in verschiedenen Projekten genutzt werden könnten.
#--------------------------------------------------------
project(Common)

configure_file(common/include/config.in.hpp common/include/config.hpp)
add_library(Common STATIC ${COMMON_SRC})
target_link_libraries(Common ${CURSES_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_DL_LIBS})

#Tests dazu
if(COMPILE_TESTS)
    project(CommonTests)
    add_executable(CommonTests common/test/main.cpp ${COMMON_TESTS})
    target_link_libraries(CommonTests ${Boost_LIBRARIES} Common)
else()
    message(STATUS "Skipping CommonTests")
endif()
#--------------------------------------------------------
# Playground
#--------------------------------------------------------
if(COMPILE_PLAYGROUND)
    project (Playground)
    add_executable(Playground playground/main.cpp)
    target_link_libraries(Playground Common)
    target_link_libraries(Playground)
else()
    message(STATUS "Skipping playground")
endif()

#--------------------------------------------------------
# Core
#--------------------------------------------------------
project(Core)
add_library(Core STATIC ${CORE_SRC})
target_link_libraries(Core Common ${Boost_LIBRARIES})
#Tests dazu
if(COMPILE_TESTS)
    project(CoreTests)
    add_executable(CoreTests core/test/main.cpp ${CORE_TESTS})
    target_link_libraries(CoreTests Common Core)
else()
    message(STATUS "Skipping CoreTests")
endif()

#--------------------------------------------------------
# Terminal UI - Stellt das Spiel in einer einfachen Form im Terminal dar
#--------------------------------------------------------
if(COMPILE_TUI)
    if(CURSES_FOUND)
        include_directories(${CURSES_INCLUDE_DIRS})

        project(TerminalUi)
        configure_file(terminal_ui/include/config.in.hpp terminal_ui/include/config.hpp)
        add_executable(TerminalUi terminal_ui/src/main.cpp ${TUI_SRC})
        target_link_libraries(TerminalUi Common Core ${Boost_LIBRARIES} ${CURSES_LIBRARIES})
        
        #Tests dazu
        project(TerminalUiTests)
        add_executable(TerminalUiTests terminal_ui/test/main.cpp ${TUI_TESTS})
        target_link_libraries(TerminalUiTests Common Core ${CURSES_LIBRARIES})
    else()
        message(STATUS "Skipping TerminalUi -> Curses not found")
    endif()
else()
    message(STATUS "Skipping TerminalUi")
endif()
#--------------------------------------------------------
# GUI - Grafische UI mittels OpenGl
#--------------------------------------------------------
if(COMPILE_GUI)
    project(Gui)
    
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory("submodules/glfw") 

    configure_file(gui/include/config.in.hpp gui/include/config.hpp)
    add_executable(Gui gui/src/main.cpp libs/glad/src/glad.c ${GUI_SRC})
    target_link_libraries(Gui Common Core glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} )

    #Tests dazu
    project(GuiTests)
    add_executable(GuiTests gui/test/main.cpp libs/glad/src/glad.c ${GUI_TESTS})
    target_link_libraries(GuiTests Common Core ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} glfw ${GLFW_LIBRARIES})
else()
    message(STATUS "Skipping VulkanGui")
endif()
