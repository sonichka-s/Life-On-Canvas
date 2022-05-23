//
// Created by sonichka on 22.05.22.
//

#ifndef WEBSOCKET_SESSION_CPP_UTILITY_H
#define WEBSOCKET_SESSION_CPP_UTILITY_H

#include <iostream>
#include <deserializer.h>
#include <unordered_map>

using unordered_map = std::unordered_map<std::string, std::string>;

class request_message {
public:
    std::string get_header() {
        unordered_map json_fields;

        return json_fields.at("header");
    }
    
private:
    //cover to lambda
    unordered_map json_to_parse(deserializer json_map) {
        return json_map.get_json_map();
    }
};


#endif //WEBSOCKET_SESSION_CPP_UTILITY_H
