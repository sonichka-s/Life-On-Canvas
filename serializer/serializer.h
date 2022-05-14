//
// Created by egornulllet on 20.04.22.
//

#ifndef CLIENTLOC_SERIALIZER_H
#define CLIENTLOC_SERIALIZER_H

#include <string>
#include <nlohmann/json.hpp>
#include "canvasController.h"

using namespace nlohmann;

struct Point {
    unsigned int xCoord;
    unsigned int yCoord;
    unsigned int RGBcolor;

    Point():xCoord ( 0 ), yCoord ( 0 ), RGBcolor ( 0 ) {}
};

class Serializer {
public:
    json serealizeDiff(std::vector<Point>);

    void parseCanvas(const std::string& inJson_str, std::vector<Point>& canvasArr);

    int parseId(std::string inJson_str);

private:
    int CanvasId;
    void from_json( const json& j, Point& point);
};

#endif //CLIENTLOC_SERIALIZER_H
