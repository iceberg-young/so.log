cmake_minimum_required(VERSION 2.8.4)

project(log)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES suit.cpp)

add_executable(log ${SOURCE_FILES})

add_subdirectory(source)
add_dependencies(${PROJECT_NAME} so.log)
target_link_libraries(${PROJECT_NAME} so.log)

include(Dependencies.cmake)
