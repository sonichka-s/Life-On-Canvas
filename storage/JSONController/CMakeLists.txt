add_library(JSONController INTERFACE)

target_include_directories(JSONController INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(JSONController INTERFACE graphicsItem SQLController)
