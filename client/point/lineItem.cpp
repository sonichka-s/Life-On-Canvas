#include "lineItem.h"

void from_json(const nlohmann::json &j, LineItem &lineItem) {
    j.at("x1").get_to(lineItem.x1);
    j.at("y1").get_to(lineItem.y1);
    j.at("x2").get_to(lineItem.x2);
    j.at("y2").get_to(lineItem.y2);
    j.at("width").get_to(lineItem.width);
    j.at("color").get_to(lineItem.color);

}

void to_json(nlohmann::json &j, const LineItem &lineItem) {
    j = nlohmann::json{{"x1", lineItem.x1},
                       {"y1", lineItem.y1},
                       {"x2", lineItem.x2},
                       {"y2", lineItem.y2},
                       {"width", lineItem.width},
                       {"Color", lineItem.color}};
}

void from_json(const nlohmann::json &j, Color &color_){
    j.at("r").get_to(color_.r);
    j.at("g").get_to(color_.g);
    j.at("b").get_to(color_.b);
    j.at("a").get_to(color_.a);

}
void to_json( nlohmann::json &j, const Color &color_){
    j = nlohmann::json{{"r", color_.r},
                       {"g", color_.g},
                       {"b", color_.b},
                       {"a", color_.a}
    };
}