cmake_minimum_required(VERSION 3.10)
project(Andesite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/vm.cpp
    src/stack.cpp
)

include_directories(include)

add_executable(andesite_vm ${SOURCES})