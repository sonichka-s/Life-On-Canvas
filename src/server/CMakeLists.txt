add_library(server server.h server.cpp websocket_session.cpp websocket_session.h acceptor.cpp acceptor.h listener.cpp listener.h http_session.cpp http_session.h)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})