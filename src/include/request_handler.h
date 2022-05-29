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
                "Get",
                [](json json_, std::function<void(const json)> prepare_respond) {
                    json data = json::parse(json_.dump());
                    std::cout << "\n" << "GET request handled";

                    //add DB request
                });

        custom(
                "Put",
                [](json json_, std::function<void(const json)> prepare_respond) {
                    json data_ = json::parse(json_.dump());
                    std::cout << "\n" << "POST request handled";

                    //add DB request
                    prepare_respond(data_);
                });

        custom(
                "Test",
                [](json json_, std::function<void(const json)> prepare_response) {
                    json data_ = json::parse(json_.dump());
                    std::cout << "\n" << "TEST request handled";

                    prepare_response(data_);
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
