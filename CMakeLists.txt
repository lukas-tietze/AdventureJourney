cmake_minimum_required (VERSION 2.8.9)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "tests/**/*.cpp")

project (Journey)
include_directories(src)
add_executable(Journey ${SOURCES})

#--------------------------------------------------------------------
#
#--------------------------------------------------------------------

project (Test)
include_directories(src)
include_directories(test)
add_executable(Test test/main.cpp ${TESTS} ${SOURCES})
