cmake_minimum_required(VERSION 3.16.3)
project("server")

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(src)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main/main.cpp)