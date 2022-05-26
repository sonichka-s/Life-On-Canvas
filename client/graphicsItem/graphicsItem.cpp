#include "graphicsItem.h"


GraphicsItem::GraphicsItem(QGraphicsLineItem* lineItem){
    x1 = static_cast<float>(lineItem->line().x1());
    y1 = static_cast<float>(lineItem->line().y1());
    x2 = static_cast<float>(lineItem->line().x2());
    y2 = static_cast<float>(lineItem->line().y2());
    width = lineItem->pen().width();
    color.r = lineItem->pen().color().red();
    color.g = lineItem->pen().color().green();
    color.b = lineItem->pen().color().blue();
    color.a = lineItem->pen().color().alpha();
    type = "Line";
}
GraphicsItem::GraphicsItem(QGraphicsEllipseItem* ellipseItem){

}
GraphicsItem::GraphicsItem(QGraphicsRectItem* rectItem){

}


void from_json(const nlohmann::json &j, GraphicsItem &graphicsItem) {
    j.at("x1").get_to(graphicsItem.x1);
    j.at("y1").get_to(graphicsItem.y1);
    j.at("x2").get_to(graphicsItem.x2);
    j.at("y2").get_to(graphicsItem.y2);
    j.at("type").get_to(graphicsItem.type);
    j.at("width").get_to(graphicsItem.width);
    j.at("color").get_to(graphicsItem.color);

}

void to_json(nlohmann::json &j, const GraphicsItem &graphicsItem) {
    j = nlohmann::json{{"x1",    graphicsItem.x1},
                       {"y1",    graphicsItem.y1},
                       {"x2",    graphicsItem.x2},
                       {"y2",    graphicsItem.y2},
                       {"type",  graphicsItem.type},
                       {"width", graphicsItem.width},
                       {"Color", graphicsItem.color}};
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