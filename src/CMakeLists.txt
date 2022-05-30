cmake_minimum_required(VERSION 3.16)

project(server_lib CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE local_sources ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)
set(SOURCES ${local_sources})

add_library(server_lib ${SOURCES})
target_include_directories(server_lib PUBLIC include)
target_include_directories(server_lib PRIVATE server)
target_link_libraries(server_lib ${Boost_LIBRARIES} Threads::Threads)