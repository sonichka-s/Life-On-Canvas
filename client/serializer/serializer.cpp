
#include <iostream>
#include "serializer.h"


nlohmann::json Serializer::serializeDiff(const std::vector<GraphicsItem>& lineItems, unsigned int canvasId) {

    nlohmann::json j;
    j["Type"] = "Put";
    j["LineItems"] = lineItems;
    j["canvasId"] = canvasId;
    return j;
}


void Serializer::parseCanvas(const std::string& inJson_str, std::vector<GraphicsItem>& itemsToDisplay) {

    nlohmann::json j = nlohmann::json::parse(inJson_str);

    j["LineItems"].get_to<std::vector<GraphicsItem>>(itemsToDisplay);
};



int Serializer::parseId(std::string inJson_str) {

    nlohmann::json j = nlohmann::json::parse(inJson_str);
    int canvasId;
    j.at("canvasId").get_to(canvasId);
    return canvasId;
}