cmake_minimum_required(VERSION 2.8.4)
project(TpLabo)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(SOURCE_FILES tests.cpp arturo.h mini_test.h)
add_executable(TpLabo ${SOURCE_FILES})

