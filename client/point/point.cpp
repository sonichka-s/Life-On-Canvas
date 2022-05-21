#include "point.h"

void from_json(const nlohmann::json &j,  Point &point) {
    j.at("x").get_to(point.xCoord);
    j.at("y").get_to(point.yCoord);
    j.at("color").get_to(point.RGBcolor);
}

void to_json(nlohmann::json &j, const Point &point) {
    j = nlohmann::json{ {"x", point.xCoord}, {"y", point.yCoord}, {"color", point.RGBcolor}};
}