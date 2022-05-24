//
// Created by sonichka on 24.05.22.
//

#ifndef WEBSOCKET_SESSION_CPP_THREAD_CONTROLLER_H
#define WEBSOCKET_SESSION_CPP_THREAD_CONTROLLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>
#include <callbacks.h>
#include <websocket_session.h>
#include <listener.h>

#include <nlohmann/json.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

class thread_controller {
    std::thread thread_;
    triggers* triggers_;
public:
    server_manager* manager;

    thread_controller() {
        manager = new server_manager;
        triggers_ = new triggers;
        manager->sessions = new std::vector<void*>();

    }

    void server_thread(server_manager* manager) {
        asio::io_context ioc {
            manager->threads
        };

        std::make_shared<listener>(ioc,
                                   tcp::endpoint {
            asio::ip::make_address(manager->ip.c_str()),
            static_cast<unsigned short>(manager->port)
        })->run();

        std::vector<std::thread> threads;
        threads.reserve(manager->threads - 1);

        for (auto i = manager->threads - 1; i > 0; --i) {
            threads.emplace_back([&ioc] {
                ioc.run();
            });
        }

        ioc.run();
    }

    void start_server() {
        manager->cb.on_message = [this] (std::string* msg, const void* con)->void {
            this->handle_message(*msg, con);
        };

        thread_ = std::thread([this] {
            this->server_thread(this->manager);
        });

        thread_.detach();
    }

    void handle_message(std::string msg, const void* con) {
        json json_;

        try {
            json_ = json::parse(msg.c_str());
        } catch (std::invalid_argument& invalid){
            std::cout << "\n" << "Error reading JSON " << invalid.what();
            return;
        }

        trigger* trig = triggers_->request_type(json_["Type"].get<std::string>());

        trig->do_handle(json_, [this, json_, con](json response) {
            this->send_response(response, NULL, con);
        });
     }

     void send_response(json json_, std::function<void(json)> on_response = NULL, const void* con = NULL) {
        if (con != NULL) {
            websocket_session* con_ = ((websocket_session*)con);
            con_->response_queue->push_back(json_.dump());
            if (!con_->writing) con_->do_read();
        }
        else {
            for (int i = 0; i < manager->sessions->size(); ++i) {
                std::vector<void*> sessions = *manager->sessions;
                websocket_session* con_ = ((websocket_session*)sessions[i]);
                con_->response_queue->push_back(json_.dump());
                if (!con_->writing) con_->do_read();
            }
        }
    }
};


#endif //WEBSOCKET_SESSION_CPP_THREAD_CONTROLLER_H
