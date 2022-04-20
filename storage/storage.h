//
// Created by gallaann on 16.04.22.
//

#include <string>

#ifndef LIFEONCANVAS_STORAGE_H
#define LIFEONCANVAS_STORAGE_H

struct Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; // alpha channel
};

struct Position{
    uint32_t x;
    uint32_t y;
};

class Pixel{
public:
    Pixel MakePixel( std::string );
    std::string MakeJSON( Pixel );

private:
    Color color;
    Position position;
};

class DataBase{
private:
    uint8_t canvasId;
    Pixel pixel;

    bool Connection(); // not sure about this / connect to DB
    bool Create(); // create canvas
    std::string Give(uint8_t canvasId); // give canvas to server
    bool Read(std::string JSON); // make Pixel from Json and push it into DB
    bool Delete(uint8_t canvasId); // delete canvas
    bool CloseConnection(); // also not sure / break the connection
};

#endif //LIFEONCANVAS_STORAGE_H
