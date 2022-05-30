add_library(SQLController storage.h)

target_include_directories(SQLController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SQLController graphicsItem)
