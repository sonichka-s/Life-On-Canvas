//
// Created by sonichka on 14.05.22.
//

#include "../include/listener.h"

listener::listener(asio::io_context &ioc,
                   tcp::endpoint ep)
        : ioc_(ioc), acceptor_(ioc) {
    beast::error_code ec;

    std::cout << "\n" << "Open the acceptor";
    acceptor_.open(ep.protocol(), ec);
    if (ec) {
        manager->cb.trigger_on_error("open");
        return;
    }
    std::cout << "\n" << "Allow address reuse";
    acceptor_.set_option(asio::socket_base::reuse_address(true), ec);

    if (ec) {
        manager->cb.trigger_on_error("set_options");
        return;
    }

    std::cout << "\n" << "Bind to server address";
    acceptor_.bind(ep, ec);
    if (ec) {
        manager->cb.trigger_on_error("bind");
        return;
    }

    std::cout << "\n" << "Start listening to connection";
    acceptor_.listen(asio::socket_base::max_listen_connections, ec);
    if (ec) {
        manager->cb.trigger_on_error("listen");
        return;
    }

//    manager->cb.trigger_on_listen();
}

void listener::run(server_manager *server_manager) {
    beast::error_code ec;
    this->manager = server_manager;

    if (ec) {
        manager->cb.trigger_on_error("run");
        return;
    }

    std::cout << "\n" << "%s " << "ws run...";
    accept();
}

void listener::accept() {
    std::cout << "\n" << " The new connection gets its own strand";
    acceptor_.async_accept(
            asio::make_strand(ioc_),
            beast::bind_front_handler(
                    &listener::on_accept,
                    shared_from_this()));
}

void listener::on_accept(beast::error_code, tcp::socket socket) {
    std::cout << "\n" << "Acception proceed";
    beast::error_code ec;

    if (ec) {
        manager->cb.trigger_on_error("accept");
        return;
    }

    std::cout << "\n" << "Create the session and run it";
    std::make_shared<websocket_session>(std::move(socket))->run(manager);
    accept();
}