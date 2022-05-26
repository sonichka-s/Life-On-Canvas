
#include <iostream>
#include "serializer.h"


std::string Serializer::serializeDiff(const std::vector<GraphicsItem>& graphicsItems, unsigned int canvasId) {

    nlohmann::json j;
    j["Type"] = "Put";
    j["GraphicsItems"] = graphicsItems;
    j["CanvasId"] = canvasId;
    return j.dump();
}


void Serializer::parseDiff(const std::string& inJson_str, std::vector<GraphicsItem>& itemsToDisplay) {

    nlohmann::json j = nlohmann::json::parse(inJson_str.c_str());

    j["GraphicsItems"].get_to<std::vector<GraphicsItem>>(itemsToDisplay);
};



int Serializer::parseId(const std::string &inJson_str) {

    nlohmann::json j = nlohmann::json::parse(inJson_str.c_str());
    int canvasId;
    j["CanvasId"].get_to(canvasId);
    return canvasId;
}