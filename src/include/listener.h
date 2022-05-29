//
// Created by sonichka on 14.05.22.
//

#ifndef ACCEPTOR_CPP_LISTENER_H
#define ACCEPTOR_CPP_LISTENER_H

#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <iostream>
#include <callbacks.h>
#include <websocket_session.h>

namespace beast = boost::beast;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class listener : public std::enable_shared_from_this<listener> {
public:
    server_manager *manager;

    listener(asio::io_context &ioc,
             tcp::endpoint ep);

    void run(server_manager *server_manager);

private:
    void accept();

    void on_accept(beast::error_code, tcp::socket socket);

    asio::io_context &ioc_;
    tcp::acceptor acceptor_;
};


#endif //ACCEPTOR_CPP_LISTENER_H
