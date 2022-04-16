//
// Created by gallaann on 16.04.22.
//

#include <string>

#ifndef UNTITLED_FRAME_H
#define UNTITLED_FRAME_H

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Position{
    unsigned int x;
    unsigned int y;
};

class DataBase{
private:
    struct Pixel{
        Color color;
        Position position;
    };

    bool Connect(); // not sure about this / connect to DB
    bool Create(); // create canvas
    bool Give(); // Give canvas to guest
    bool Insert(Pixel pixel); // pull changes to canvas/DB
    Pixel Read(std::string); // make Pixel from Json
    bool Delete(); // for delete canvas
    bool CloseConnection(); // also not sure / break the connection
};

#endif //UNTITLED_FRAME_H
