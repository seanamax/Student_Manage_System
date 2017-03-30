cmake_minimum_required(VERSION 3.5)
project(Student_Manage_System_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(exe_target main.cpp)
add_executable(Student_Manage_System_Server ${exe_target})

