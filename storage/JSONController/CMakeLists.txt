add_library(JSONController server-storage.h json.hpp)

target_include_directories(JSONController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(JSONController graphicsItem SQLController)
