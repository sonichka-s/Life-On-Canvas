//
// Created by sonichka on 14.05.22.
//

#ifndef ACCEPTOR_CPP_LISTENER_H
#define ACCEPTOR_CPP_LISTENER_H

#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <iostream>

namespace beast = boost::beast;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class listener : public std::enable_shared_from_this<listener> {
public:
    listener(asio::io_context& ioc,
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

    void run()
    {
        accept();
    }

private:
    void accept()
    {
        acceptor_.async_accept(
                asio::make_strand(ioc_),
                beast::bind_front_handler(
                        &listener::on_accept,
                        shared_from_this()));
    }

    void on_accept(beast::error_code, tcp::socket socket)
    {
        //create session
        accept();
    }
    asio::io_context& ioc_;
    tcp::acceptor acceptor_;
};


#endif //ACCEPTOR_CPP_LISTENER_H
