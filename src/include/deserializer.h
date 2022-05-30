//
// Created by sonichka on 22.05.22.
//

#ifndef WEBSOCKET_SESSION_CPP_DESERIALIZER_H
#define WEBSOCKET_SESSION_CPP_DESERIALIZER_H

#include <iostream>
#include <unordered_map>

class deserializer {
public:
    std::unordered_map<std::string, std::string> get_json_map() {
        return json_map;
    }
private:
    std::unordered_map<std::string, std::string> json_map;
};

#endif //WEBSOCKET_SESSION_CPP_DESERIALIZER_H
