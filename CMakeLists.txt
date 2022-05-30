cmake_minimum_required(VERSION 3.16.3)
project("server")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(storage)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main/main.cpp)

find_package (SQLite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (Tutorial ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)

target_link_libraries(server PUBLIC server_lib)
target_link_libraries(server PUBLIC SQLController JSONController graphicsItem)
target_include_directories(server_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
