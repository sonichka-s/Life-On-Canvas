//
// Created by sonichka on 13.05.22.
//

#ifndef SERVER_CPP_CONNECTION_H
#define SERVER_CPP_CONNECTION_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <callbacks.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;


class websocket_session : public std::enable_shared_from_this<websocket_session> {
public:
    server_manager *manager;
    std::vector<std::string> *response_queue;
    uint64_t sessionID;
    bool reading = false;
    bool writing = false;

    explicit
    websocket_session(tcp::socket &&socket) : ws_(std::move(socket)) {}

    void run(server_manager *manager) {
        std::cout << "\n" << "Run session";
        sessionID = (uint64_t) std::time(nullptr);

        this->manager = manager;
        response_queue = new std::vector<std::string>();
        std::cout << "\n" << "Manager initialized";

        ws_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::server));
        std::cout << "\n" << "Role: server";
        
        ws_.set_option(websocket::stream_base::decorator([](websocket::response_type &res) {
            res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) + "websocket-server-async");
        }));

        std::cout << "\n" << "Accept point";
        ws_.async_accept(
                beast::bind_front_handler(
                        &websocket_session::on_accept,
                        shared_from_this()));
    }

    void on_accept(beast::error_code ec) {
        std::cout << "\n" << "Accept connection";

        if (ec) {
            manager->cb.trigger_on_error("accept");
            return;
        }

        sessionID = (uint64_t) std::time(nullptr);
        manager->sessions->push_back(this);
        manager->cb.trigger_on_open(this);

        // Read a message
        this->do_read();
    }

    void do_read() {
        std::cout << "\n" << "Read msg";
        if (response_queue->size() > 0 && !writing) {
            std::vector<std::string> q = *response_queue;
            this->do_write(q[0]);
        }

        if (!reading) {
            reading == true;

            ws_.async_read(buffer_,
                           beast::bind_front_handler(
                                   &websocket_session::on_read,
                                   shared_from_this()));
        }
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        std::cout << "\n" << "Read proceed";
        manager->cb.err.ec = ec;

        if (ec == websocket::error::closed) {
            manager->cb.trigger_on_close();

            for (int i = 0; i < manager->sessions->size(); ++i) {
                std::vector<void *> sessions = *manager->sessions;
                websocket_session *con_ = ((websocket_session *) sessions[i]);
                if (con_->sessionID == this->sessionID) {
                    manager->sessions->erase(manager->sessions->begin() + i);
                    break;
                }
            }
        }

        if (ec) {
            manager->cb.trigger_on_error("read");
        }

        auto msg = new std::string(beast::buffers_to_string(buffer_.data()));
        if (msg->length() > 0)
            manager->cb.on_message(msg, this);

        buffer_.consume(buffer_.size());
        reading = false;
        this->do_read();
    }

//    void handle_request() {
//        auto res = std::make_shared<std::string>();
//        auto req = beast::buffers_to_string(buffer_.data());
//        //обработка запроса
//    }

    void do_write(std::string msg) {
        std::cout << "\n" << "Write response";

        if (writing == true)
            return;

        writing = true;

        this->ws_.async_write(asio::buffer(msg),
                              beast::bind_front_handler(
                                      &websocket_session::on_write,
                                      shared_from_this()
                              ));
    }

    void on_write(beast::error_code ec, std::size_t bytes_transferred) {
        std::cout << "\n" << "Writing proceed";

        if (ec) {
            manager->cb.trigger_on_error("write");
            return;
        }

        if (response_queue->size() > 0) {
            response_queue->erase(response_queue->begin());
            std::cout << "\n" << "Session erased";
            std::vector<std::string> q = *response_queue;
            if (response_queue->size() > 0)
                this->do_write(q[0]);
        } else {
            writing = false;
        }
    }

private:
    beast::flat_buffer buffer_;
    websocket::stream<tcp::socket> ws_;
};


#endif //SERVER_CPP_CONNECTION_H
