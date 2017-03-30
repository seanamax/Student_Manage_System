cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#project(demo)

INCLUDE_DIRECTORIES(/usr/local/mysql-5.7.17-macos10.12-x86_64/include)
LINK_DIRECTORIES(/usr//local/mysql-5.7.17-macos10.12-x86_64/lib/)
#INCLUDE_DIRECTORIES(../include/)
#LINK_DIRECTORIES(../include/lib/)



#set(exec_target main.cpp)

#add_executable(demo ${exec_target})

#target_link_libraries(demo libgtest.a libgtest_main.a)
#target_link_libraries(demo libmysqlclient.a)
#target_link_libraries(demo libmysqld-debug.a)
#target_link_libraries(demo libmysqlservices.a)

add_subdirectory(test)
