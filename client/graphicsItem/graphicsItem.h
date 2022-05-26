#include <nlohmann/json.hpp>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPen>

struct Color {
    int r;
    int g;
    int b;
    int a;
};

struct GraphicsItem {
    float x1;
    float y1;
    float x2;
    float y2;
    int width;
    Color color;
    std::string type;

    GraphicsItem(QGraphicsLineItem* lineItem);
    GraphicsItem(QGraphicsEllipseItem* ellipseItem);
    GraphicsItem(QGraphicsRectItem* rectItem);
};


void from_json(const nlohmann::json &j, GraphicsItem &graphicsItem);
void to_json( nlohmann::json &j, const GraphicsItem &graphicsItem);

void from_json(const nlohmann::json &j, Color &color_x);
void to_json( nlohmann::json &j, const Color &color_);