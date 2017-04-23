cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(test_demo)


include_directories(../../include)
#include_directories(/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/)
link_directories(../../lib)

set(mysql_base_dir /usr/local/mysql)
INCLUDE_DIRECTORIES(${mysql_base_dir}/include)
LINK_DIRECTORIES(${mysql_base_dir}/lib)


set(gnu_base_lib /usr/lib/x86_64-linux-gnu)
link_directories(${gnu_base_lib})

set(init_test test_init.cpp ../db_connection_pool.cpp ../db.cpp ../db_connection_guard.cpp)
set(threadsafe_stack_test threadsafe_stack_test.cpp)
set(db_test db_test.cpp ../db.cpp)
set(db_connection_pool_test db_connection_pool_test.cpp ../db_connection_pool.cpp ../db.cpp)
set(user_test user_test.cpp ${init_test} ../user.cpp)
set(db_connection_guard_test db_connection_guard_test.cpp ${init_test})

set(exec_target ${init_test} ${threadsafe_stack_test}
        ${db_test} ${db_connection_pool_test}
        ${user_test} ${db_connection_guard_test})


add_executable(test_demo ${exec_target})

target_link_libraries(test_demo libgtest.a libgtest_main.a)
target_link_libraries(test_demo libmysqlclient.so)
target_link_libraries(test_demo libpthread.so.0)

