cmake_minimum_required(VERSION 3.5)
project(Student_Manage_System_Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(exec_target main.cpp)
add_executable(Student_Manage_System_Client ${exec_target})
