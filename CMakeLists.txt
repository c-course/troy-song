cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(my-server my-server.cpp)
add_executable(mycurl my-client.cpp)
add_test(test-server my-server)
add_test(test-mycurl my-client)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
