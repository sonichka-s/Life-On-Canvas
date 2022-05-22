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

    void run() {
        asio::dispatch(ws_.get_executor(),
                       beast::bind_front_handler(
                               &websocket_session::on_run(),
                               shared_from_this()));
    }

    void on_run() {
        ws_.async_accept(
                beast::bind_front_handler(
                        &websocket_session::on_accept,
                        shared_from_this()));
    }

    void on_accept(beast::error_code ec)
    {
        // Read a message
        do_read();
    }

    void do_read() {
        ws_.async_read(buffer_,
                       beast::bind_front_handler(
                               &websocket_session::on_read,
                               shared_from_this()));
    }

    void on_read(std::size_t bytes_transferred) {
        handle_request();
    }

    void handle_request() {
        auto res = std::make_shared<std::string>();
        auto req = beast::buffers_to_string(buffer_.data());
        //обработка запроса
    }

    void write(std::shared_ptr<std::string>& res) {
        ws_.text(ws_.got_text());
        ws_.async_write(asio::buffer(*res), [s = shared_from_this(), res](beast::error_code ec, size_t bytes_transferred)
        mutable {
            s->on_write(ec, res->size());
        });
    }

    void on_write(beast::error_code ec, std::size_t bytes_transferred) {
        buffer_.consume(buffer_.size());
        do_read();
    }

private:
    beast::flat_buffer buffer_;
    websocket::stream<tcp::socket> ws_;
};


#endif //SERVER_CPP_CONNECTION_H
