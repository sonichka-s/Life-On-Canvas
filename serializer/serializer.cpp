//
// Created by egornulllet on 20.04.22.
//

#include "serializer.h"

void Serializer::parseCanvas(const std::string& inJson_str, std::vector<Point>& canvasArr) {

    json j = json::parse(inJson_str.c_str());
    for( auto pointIterator: j.at("Points")){
        Point curPoint;
        from_json(j, curPoint);
        canvasArr.push_back(curPoint);
    }
};

void Serializer::from_json(const json &j, Point &point) {
    j.at("x").get_to(point.xCoord);
    j.at("y").get_to(point.yCoord);
    j.at("color").get_to(point.RGBcolor);
}

int Serializer::parseId(std::string inJson_str) {
    json j = json::parse(inJson_str.c_str());
    int canvasId;
    j.at("canvasId").get_to(canvasId);
    return canvasId;
}