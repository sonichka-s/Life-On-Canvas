//
// Created by sonichka on 14.05.22.
//

#include "../include/listener.h"

listener::listener(asio::io_context& ioc,
tcp::endpoint ep)
: ioc_ (ioc)
, acceptor_ (ioc)
{
    beast::error_code ec;

    acceptor_.open(ep.protocol(), ec);
    if (ec)
    {
//            fail(ec, "open");
        return;
    }

    acceptor_.set_option(asio::socket_base::reuse_address(true), ec);

    if (ec)
    {
//            fail(ec, "open");
        return;
    }

    acceptor_.bind(ep, ec);

    acceptor_.listen(asio::socket_base::max_listen_connections, ec);
}

void listener::run()
{
    accept();
}

void listener::accept()
{
    acceptor_.async_accept(
            asio::make_strand(ioc_),
            beast::bind_front_handler(
                    &listener::on_accept,
                    shared_from_this()));
}

void listener::on_accept(beast::error_code, tcp::socket socket)
{
    //create session
    accept();
}