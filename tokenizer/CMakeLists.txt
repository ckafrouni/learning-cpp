cmake_minimum_required(VERSION 3.10)
project(tokenizer) # Keep your project name

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb -O3")

include_directories("include")

# Since PEGTL is header-only, there's no need for link_directories for PEGTL
link_directories(lib)

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES}) # Use your executable name
