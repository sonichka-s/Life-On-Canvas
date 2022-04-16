cmake_minimum_required(VERSION 3.16.3)
project("TestServer")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_executable(Server src/server/server.cpp)
target_link_libraries(Server /usr/local/lib/libhttpserver.so)