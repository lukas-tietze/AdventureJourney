cmake_minimum_required (VERSION 3.6.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wswitch-default -Wswitch-enum")

project (Test)
file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE TESTS "test/**/*.cpp")
file(GLOB_RECURSE LIB "lib/**/*.cpp")

include_directories(include)
include_directories(test)
include_directories(src)

add_library(COMMON STATIC ${LIB})

add_executable(Test test/main.cpp ${TESTS})
target_link_libraries(Test COMMON)
