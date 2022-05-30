add_library(SQLController INTERFACE)

target_include_directories(SQLController INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SQLController INTERFACE graphicsItem)
