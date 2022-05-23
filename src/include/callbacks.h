//
// Created by sonichka on 23.05.22.
//

#ifndef WEBSOCKET_SESSION_CPP_CALLBACKS_H
#define WEBSOCKET_SESSION_CPP_CALLBACKS_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

namespace beast = boost::beast;

struct cb_error {
    std::string msg = "";
    beast::error_code  ec;
};

struct ws_callbacks {
    cb_error err;
    std::function<void()> on_listen = NULL;
    std::function<void(void*)> on_open;
    std::function<void(std::string*, const void*)> on_message;
    std::function<void()> on_close;

    std::function<void(cb_error)> on_error;

    void trigger_on_open(void* con = NULL) {
        if (this->on_open != 0)
            this->on_open(con);
    }

    void trigger_on_listen() {
        if (this->on_listen != 0)
            this->on_listen();
    }

    void trigger_on_message(std::string* msg, void* con) {
        if (this->on_message != 0) {
            this->on_message(msg, con);
        }
    }

    void trigger_on_close() {
        if (this->on_close != 0)
            this->on_close();
    }
};

struct trigger {
    std::string pid;
    std::string cmd;
    std::function<void(const json, std::function<void(const json)>)> do_handle;
    std::function<void(const json)> on_response;
    std::function<void(const json)> on_progress;
};

class triggers {
public:
    std::vector<trigger*> elems;

    trigger* add(
            std::string cmd,
    std::function<void(const json, std::function<void(const json)>)> do_handle,
    std::function<void(const json)> on_response,
    std::function<void(const json)> on_progress
            ) {
        trigger* trigger = new struct trigger();
        trigger->cmd = cmd;

        if (do_handle != 0) {
            trigger->do_handle = do_handle;
        }

        if (on_response != 0) {
            trigger->on_response = on_response;
        }

        if (on_progress != 0) {
            trigger->on_progress = on_progress;
        }

        elems.push_back(trigger);

        return trigger;
    }
};


#endif //WEBSOCKET_SESSION_CPP_CALLBACKS_H
