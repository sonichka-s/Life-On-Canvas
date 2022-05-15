cmake_minimum_required(VERSION 3.16)

project(Life-On_Canvas CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} include/connection.h include/listener.h server/websocket_session.cpp server/listener.cpp)

target_include_directories(src PUBLIC include)
target_include_directories(src PRIVATE server)
target_link_libraries(src ${Boost_LIBRARIES} Threads::Threads)