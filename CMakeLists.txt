cmake_minimum_required (VERSION 2.8.9)

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
