//
// Created by gallaann on 5/25/22.
//

#ifndef TUTORIAL_SERVER_STORAGE_H
#define TUTORIAL_SERVER_STORAGE_H

#pragma once

#include <iostream>

#include <nlohmann/json.hpp>

#include "../SQLController/storage.h"
#include "../graphicsItem/GraphicsItem.h"

using json = nlohmann::json;

//to pack object into JSON
void to_json(json &j, const GraphicsItem &Item) {
    j = {
            {"Color", {
                              {"r", Item.GetColorR()},
                              {"g", Item.GetColorG()},
                              {"b", Item.GetColorB()},
                              {"a", Item.GetColorA()},
                      }},
            {"type",  Item.GetLineItem()},
            {"width", Item.GetWidth()},
            {"x1",    Item.GetX1()},
            {"x2",    Item.GetX2()},
            {"y1",    Item.GetY1()},
            {"y2",    Item.GetY2()}
    };
}

//single element -> JSON
void to_json(json &j, const GraphicsItem &Item, const uint Key) {
//    j["Type"] = "Get";
    j["GraphicsItem"] = Item;
    j["CanvasId"] = Key;
}

//vector -> JSON
void to_json(json &j, const std::vector<GraphicsItem> &vec, const uint Key) {
//    j["Type"] = "Get";
    j["GraphicsItem"] = json(vec);
    j["CanvasId"] = Key;
}


//get object from JSON
void from_json(const json &j, GraphicsItem &Item) {
    uint8_t R, G, B, A;
    json Colors = j["Color"];
    Colors.at("r").get_to(R);
    Colors.at("g").get_to(G);
    Colors.at("b").get_to(B);
    Colors.at("a").get_to(A);

    char type;
    j.at("type").get_to(type);

    int width;
    j.at("width").get_to(width);

    uint32_t X1, Y1, X2, Y2;
    j.at("x1").get_to(X1);
    j.at("x2").get_to(X2);
    j.at("y1").get_to(Y1);
    j.at("y2").get_to(Y2);

    Item = GraphicsItem(X1, Y1, X2, Y2, R, G, B, A, width, type);
}

//JSON -> vector of Objects
void GetVector(const json &j, std::vector<GraphicsItem> &vec) {
    for (size_t i = 0; i < j.size(); ++i) {
        auto line = j[i].get<GraphicsItem>();
        vec.push_back(line);
    }
}

//JSON -> GraphicsItem -> DB
int IntoDB(const json &put){
    json array = put["GraphicsItem"];
    std::vector<GraphicsItem> arr;
    GetVector(array,arr);

    DataBase db;
    for (size_t i = 0; i < arr.size(); ++i) {
        auto line = array[i].get<GraphicsItem>();
        if (!db.Insert(42069,put["CanvasId"],line)) return 0;
    }

    return 1;
}

//DB -> vector -> JSON
json FromDB(const json &get){
    DataBase db;
    std::vector<GraphicsItem> line;
    if(!db.Get(42069,get["CanvasId"],line)) return nullptr;

    json j;
    to_json(j,line,1);
    return j;
}

#endif //TUTORIAL_SERVER_STORAGE_H
