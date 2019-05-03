#--------------------------------------------------------
# General
#--------------------------------------------------------
cmake_minimum_required (VERSION 3.7)

if(WIN32)
    cmake_policy(SET CMP0074 NEW)

    set(CMAKE_PROJECT_NAME "Project")
endif()

set(COMPILE_GUI on)
set(COMPILE_TESTS on)
set(COMPILE_PLAYGROUND on)
set(COMPILE_TESTS on)
set(COMPILE_TUI on)
set(COMPILE_GUI on)
set(ENABLE_BACKTRACE off)

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

# Set(CURSES_NEED_NCURSES TRUE)
# find_package(Curses)
 
#workaround https://gitlab.kitware.com/cmake/cmake/issues/17297
set(_Boost_STACKTRACE_BASIC_HEADERS     "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_BACKTRACE_HEADERS "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_ADDR2LINE_HEADERS "boost/stacktrace.hpp")
set(_Boost_STACKTRACE_NOOP_HEADERS      "boost/stacktrace.hpp")

add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
add_definitions(-DBOOST_STACKTRACE_DYN_LINK)
# add_definitions(-DBOOST_STACKTRACE_USE_BACKTRACE)

find_package(Boost 1.65.0 COMPONENTS filesystem chrono thread REQUIRED)

if(ENABLE_BACKTRACE)
    if(MSVC)
        find_package(Boost 1.65.0 COMPONENTS stacktrace_windbg)
    else()
        find_package(Boost 1.65.0 COMPONENTS stacktrace_backtrace)
    endif()
else()
    find_package(Boost 1.65.0 COMPONENTS stacktrace_noop)
endif()
# find_package(Boost 1.70.0)

#external includes
include_directories(${Boost_INCLUDE_DIRS})

#external libs/submodules
include_directories(libs/glad/include)
include_directories(submodules/glfw/include)
include_directories(submodules/glm/)
include_directories(submodules/stb)

#projects - libs
include_directories(libCommon/include)
include_directories(libTermUtil/include)
include_directories(libGlUtil/include)

#projects - exe
include_directories(core/include)
include_directories(playground)
include_directories(terminal_ui/include)
include_directories(gui/include)

#general (root as include dir)
include_directories(.)

#LibCommon
file(GLOB_RECURSE LIB_COMMON_SRC "libCommon/src/**/*.cpp" "libCommon/src/*.cpp")
file(GLOB_RECURSE LIB_COMMON_TESTS "libCommon/test/**/*.cpp" "libCommon/test/*.cpp")
#LibCommon
file(GLOB_RECURSE LIB_TERM_UTIL_SRC "libTermUtil/src/**/*.cpp" "libTermUtil/src/*.cpp")
file(GLOB_RECURSE LIB_TERM_UTIL_TESTS "libTermUtil/test/**/*.cpp" "libTermUtil/test/*.cpp")
#LibCommon
file(GLOB_RECURSE LIB_GL_UTIL_SRC "libGlUtil/src/**/*.cpp" "libGlUtil/src/*.cpp")
file(GLOB_RECURSE LIB_GL_UTIL_TESTS "libGlUtil/test/**/*.cpp" "libGlUtil/test/*.cpp")
#Core
file(GLOB_RECURSE CORE_SRC "core/src/**/*.cpp" "core/src/*.cpp")
file(GLOB_RECURSE CORE_TESTS "core/test/**/*.cpp" "core/test/*.cpp")
#Terminal
file(GLOB_RECURSE TUI_SRC "terminal_ui/src/**/*.cpp" "terminal_ui/src/*.cpp")
file(GLOB_RECURSE TUI_TESTS "terminal_ui/test/**/*.cpp" "terminal_ui/test/*.cpp")
#Gui
file(GLOB_RECURSE GUI_SRC "gui/src/**/*.cpp" "gui/src/*.cpp")
file(GLOB_RECURSE GUI_TESTS "gui/test/**/*.cpp" "gui/test/*.cpp")

#--------------------------------------------------------
# LibCommon - enthält Utils und Wrapper, die in verschiedenen Projekten genutzt werden könnten.
#--------------------------------------------------------
project(LibCommon)

configure_file(libCommon/include/config.in.hpp libCommon/include/config.hpp)
add_library(LibCommon STATIC ${LIB_COMMON_SRC})
target_link_libraries(LibCommon ${Boost_LIBRARIES} ${CMAKE_DL_LIBS})

#Tests dazu
if(COMPILE_TESTS)
    project(LibCommonTests)
    add_executable(LibCommonTests libCommon/test/main.cpp ${LIB_COMMON_TESTS})
    target_link_libraries(LibCommonTests ${Boost_LIBRARIES} LibCommon)
else()
    message(STATUS "Skipping LibCommon/Tests")
endif()

#--------------------------------------------------------
# LibTermUtil - enthält Wrapper für NCurses-Funktionen
#--------------------------------------------------------
project(LibGlUtil)

configure_file(libGlUtil/include/config.in.hpp libGlUtil/include/config.hpp)
add_library(LibGlUtil STATIC ${LIB_GL_UTIL_SRC})
target_link_libraries(LibGlUtil LibCommon ${CMAKE_DL_LIBS} )

#Tests dazu
if(COMPILE_TESTS)
    project(LibGlUtilTests)
    add_executable(LibGlUtilTests libGlUtil/test/main.cpp ${LIB_GL_UTIL_TESTS})
    target_link_libraries(LibGlUtilTests LibGlUtil LibCommon)
else()
    message(STATUS "Skipping LibGlUtil/Tests")
endif()

#--------------------------------------------------------
# Common Library - enthält Utils und Wrapper, die in verschiedenen Projekten genutzt werden könnten.
#--------------------------------------------------------
if(CURSES_FOUND)
    project(LibTermUtil)
    include_directories(${CURSES_INCLUDE_DIRS})

    configure_file(libTermUtil/include/config.in.hpp libTermUtil/include/config.hpp)
    add_library(LibTermUtil STATIC ${LIB_TERM_UTIL_SRC})
    target_link_libraries(LibTermUtil ${CURSES_LIBRARIES} LibCommon ${CMAKE_DL_LIBS})

    #Tests dazu
    if(COMPILE_TESTS)
        project(LibTermUtilTests)
        add_executable(LibTermUtilTests libTermUtil/test/main.cpp ${LIB_TERM_UTIL_TESTS})
        target_link_libraries(LibTermUtilTests ${Boost_LIBRARIES} LibTermUtil)
    else()
        message(STATUS "Skipping LibTermUtil/Tests")
    endif()
else()
    message(STATUS "Skipping LibTermUtil (Curses not found)")
endif()

#--------------------------------------------------------
# Playground
#--------------------------------------------------------
if(COMPILE_PLAYGROUND)
    project (Playground)
    add_executable(Playground playground/main.cpp)
    target_link_libraries(Playground LibCommon)
    target_link_libraries(Playground)
else()
    message(STATUS "Skipping playground (project turned off)")
endif()

#--------------------------------------------------------
# Core
#--------------------------------------------------------
project(Core)
add_library(Core STATIC ${CORE_SRC})
target_link_libraries(Core LibCommon ${Boost_LIBRARIES})
#Tests dazu
if(COMPILE_TESTS)
    project(CoreTests)
    add_executable(CoreTests core/test/main.cpp ${CORE_TESTS})
    target_link_libraries(CoreTests LibCommon Core)
else()
    message(STATUS "Skipping Core/Tests")
endif()

#--------------------------------------------------------
# Terminal UI - Stellt das Spiel in einer einfachen Form im Terminal dar
#--------------------------------------------------------
if(COMPILE_TUI)
    if(CURSES_FOUND)
        project(TerminalUi)
        include_directories(${CURSES_INCLUDE_DIRS})

        configure_file(terminal_ui/include/config.in.hpp terminal_ui/include/config.hpp)
        add_executable(TerminalUi terminal_ui/src/main.cpp ${TUI_SRC})
        target_link_libraries(TerminalUi LibCommon LibTermUtil Core ${Boost_LIBRARIES} ${CURSES_LIBRARIES})
        
        if(COMPIlE_TESTS)
            #Tests dazu
            project(TerminalUiTests)
            add_executable(TerminalUiTests terminal_ui/test/main.cpp ${TUI_TESTS})
            target_link_libraries(TerminalUiTests LibCommon LibTermUtil Core ${CURSES_LIBRARIES})
        else()
            message(STATUS "Skipping TerminalUi/Tests")
        endif()
    else()
        message(STATUS "Skipping TerminalUi (Curses not found)")
    endif()
else()
    message(STATUS "Skipping TerminalUi (project turned off)")
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
    # add_subdirectory("libs/glad")

    configure_file(gui/include/config.in.hpp gui/include/config.hpp)
    add_executable(Gui gui/src/main.cpp libs/glad/src/glad.c ${GUI_SRC})
    target_link_libraries(Gui LibCommon LibGlUtil Core glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} )

    if(COMPILE_TESTS)
        #Tests dazu
        project(GuiTests)
        add_executable(GuiTests gui/test/main.cpp libs/glad/src/glad.c ${GUI_TESTS})
        target_link_libraries(GuiTests LibCommon LibGlUtil Core ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} glfw ${GLFW_LIBRARIES})
    else()
        message(STATUS "Skipping Gui/Tests")
    endif()
else()
    message(STATUS "Skipping Gui (project turend off)")
endif()
