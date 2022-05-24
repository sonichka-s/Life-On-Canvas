#include <nlohmann/json.hpp>

struct Color {
    int r;
    int g;
    int b;
    int a;
};

struct LineItem {
    float x1;
    float y1;
    float x2;
    float y2;
    int width;
    Color color;

};


void from_json(const nlohmann::json &j, LineItem &lineItem);
void to_json( nlohmann::json &j, const LineItem &lineItem);

void from_json(const nlohmann::json &j, Color &color_x);
void to_json( nlohmann::json &j, const Color &color_);