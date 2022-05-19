
cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(clientLoC CXX)

find_package (Qt5Widgets)
find_package (Qt5Network)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5  COMPONENTS Network REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(clientLoC main.cpp)

add_subdirectory(client)
add_subdirectory(draw)

target_link_libraries(clientLoC LINK_PUBLIC  canvasController networkController draw)
#add_subdirectory(tests)