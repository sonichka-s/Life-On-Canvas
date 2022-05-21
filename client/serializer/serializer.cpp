
#include <iostream>
#include "serializer.h"

void Serializer::parseCanvas(const std::string& inJson_str, std::vector<Point>& canvasArr) {

    nlohmann::json j = nlohmann::json::parse(inJson_str);

    j["Points"].get_to<std::vector<Point>>(canvasArr);
};

nlohmann::json Serializer::serializeDiff(const std::vector<Point>& points, unsigned int canvasId) {

    nlohmann::json j;
    j["Type"] = "Put";
    j["Points"] = points;
    j["canvasId"] = canvasId;
    return j;
}



int Serializer::parseId(std::string inJson_str) {

    nlohmann::json j = nlohmann::json::parse(inJson_str);
    int canvasId;
    j.at("canvasId").get_to(canvasId);
    return canvasId;
}