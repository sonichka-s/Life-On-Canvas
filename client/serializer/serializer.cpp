
#include <iostream>
#include "serializer.h"


nlohmann::json Serializer::serializeDiff(const std::vector<LineItem>& lineItems, unsigned int canvasId) {

    nlohmann::json j;
    j["Type"] = "Put";
    j["LineItems"] = lineItems;
    j["canvasId"] = canvasId;
    return j;
}


void Serializer::parseCanvas(const std::string& inJson_str, std::vector<LineItem>& itemsToDisplay) {

    nlohmann::json j = nlohmann::json::parse(inJson_str);

    j["LineItems"].get_to<std::vector<LineItem>>(itemsToDisplay);
};



int Serializer::parseId(std::string inJson_str) {

    nlohmann::json j = nlohmann::json::parse(inJson_str);
    int canvasId;
    j.at("canvasId").get_to(canvasId);
    return canvasId;
}