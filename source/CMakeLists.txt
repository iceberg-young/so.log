cmake_minimum_required(VERSION 2.8.4)

project(so.log)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES
    log.cpp
    log_data.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
include_directories(../include)
include(Dependencies.cmake)
