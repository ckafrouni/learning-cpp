cmake_minimum_required(VERSION 3.10)
project(tokenizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb -O3")

include_directories("include")

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

include(CTest)
# Tests
if (ENABLE_TESTING)
    add_subdirectory(tests)
    enable_testing()
endif(ENABLE_TESTING)
