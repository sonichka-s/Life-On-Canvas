add_library(point point.cpp point.h)

target_include_directories(point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(point serializer)