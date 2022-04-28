add_library(networkController networkController.cpp networkController.h)

target_include_directories(networkController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(networkController Qt5::Widgets Qt5::Core Qt5::Network serializer)