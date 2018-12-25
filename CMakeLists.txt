cmake_minimum_required(VERSION 2.8)

project(hello_world)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

message(STATUS ${CMAKE_BUILD_TYPE})
add_executable(hello_world_demo main.cpp)

target_link_libraries(hello_world_demo ${OpenCV_LIBS})
