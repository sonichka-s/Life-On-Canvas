//
// Created by sonichka on 13.05.22.
//

#ifndef SERVER_CPP_CONNECTION_H
#define SERVER_CPP_CONNECTION_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

class websocket_session : public std::enable_shared_from_this<websocket_session> {
public:
    explicit
    websocket_session(tcp::socket&& socket)
    : ws_(std::move(socket))
    {
    }

    void run()
    {
        asio::dispatch(ws_.get_executor(),
                       beast::bind_front_handler(
                               &websocket_session::on_run,
                               shared_from_this()));
    }

    void on_run()
    {
        ws_.async_accept(
                beast::bind_front_handler(
                        &websocket_session::on_accept,
                        shared_from_this()));
    }

private:
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    
};


#endif //SERVER_CPP_CONNECTION_H
