//
// Created by sonichka on 27.05.22.
//

#ifndef MAIN_CPP_REQUEST_HANDLER_H
#define MAIN_CPP_REQUEST_HANDLER_H

#include <callbacks.h>
#include <nlohmann/json.hpp>
#include <iostream>

class request_handler {
public:
    request_handler(triggers *triggers) : triggers_(triggers) {}

    void set_types() {

        custom(
                "GET",
                [](json json_, std::function<void(const json)> prepare_respond) {
                    json data = json::parse(json_.dump());

                    //add DB request
                });

        custom(
                "POST",
                [](json json_, std::function<void(const json)> prepare_respond) {
                    json data = json::parse(json_.dump());

                    //add DB request
                });
    }

private:
    void custom(std::string request_type,
                std::function<void(const json,
                                   std::function<void(const json)>)> do_handle) {
        triggers_->add(request_type, do_handle, 0, 0);
    }

    triggers *triggers_;
};

#endif //MAIN_CPP_REQUEST_HANDLER_H
