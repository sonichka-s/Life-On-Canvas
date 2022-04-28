add_library(canvasController canvasController.cpp canvasController.h)

target_include_directories(canvasController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(canvasController Qt5::Widgets Qt5::Core Qt5::Network serializer networkController)