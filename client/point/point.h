#include <nlohmann/json.hpp>

struct Point {
    unsigned int xCoord;
    unsigned int yCoord;
    unsigned int RGBcolor;

    //Point():xCoord ( 0 ), yCoord ( 0 ), RGBcolor ( 0 ) {}
};

void from_json(const nlohmann::json &j, Point &point);
void to_json( nlohmann::json &j, const Point &point);