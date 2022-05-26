add_library(graphicsItem graphicsItem.cpp graphicsItem.h)

target_include_directories(graphicsItem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(graphicsItem canvasController)
