//
// Created by gallaann on 16.04.22.
//

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

    void Connect(); // connect to DB
    void Create(); // create canvas
    void Read(); // not sure for this
    void Insert(Pixel pixel); // pull changes to canvas/DB
    void Delete(); // for delete canvas
    void CloseConnection(); // break the connection
};

#endif //UNTITLED_FRAME_H
