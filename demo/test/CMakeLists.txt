cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(test_demo)


include_directories(../../include)
include_directories(/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/)
link_directories(../../lib)

INCLUDE_DIRECTORIES(/usr/local/mysql-5.7.17-macos10.12-x86_64/include)
LINK_DIRECTORIES(/usr//local/mysql-5.7.17-macos10.12-x86_64/lib/)

set(init_test test_init.cpp ../db_connection_pool.cpp ../db.cpp)
set(threadsafe_stack_test threadsafe_stack_test.cpp)
set(db_test db_test.cpp ../db.cpp)
set(db_connection_pool_test db_connection_pool_test.cpp ../db_connection_pool.cpp ../db.cpp)
set(user_test user_test.cpp ../db_connection_pool.cpp ../db.cpp ../user.cpp)


set(exec_target ${init_test} ${threadsafe_stack_test} ${db_test} ${db_connection_pool_test} ${user_test})
add_executable(test_demo ${exec_target})

target_link_libraries(test_demo libgtest.a libgtest_main.a)
target_link_libraries(test_demo libmysqlclient.a)
