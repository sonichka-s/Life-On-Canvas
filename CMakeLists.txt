cmake_minimum_required(VERSION 3.22)
project (Tutorial)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

add_executable(Tutorial main.cpp)

add_subdirectory(storage)

find_package (SQLite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (Tutorial ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)
