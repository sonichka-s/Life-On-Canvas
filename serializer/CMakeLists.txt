add_library( serializer serializer.cpp serializer.h )

target_include_directories(serializer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})