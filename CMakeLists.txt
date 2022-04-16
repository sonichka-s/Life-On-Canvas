cmake_minimum_required(VERSION 3.22)
project(LifeOnCanvasDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

add_subdirectory(frame)

target_link_libraries(main PUBLIC frame)
