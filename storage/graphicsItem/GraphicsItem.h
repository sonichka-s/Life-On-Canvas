//
// Created by gallaann on 5/24/22.
//

#ifndef TUTORIAL_GRAPHICSITEM_H
#define TUTORIAL_GRAPHICSITEM_H

#pragma once

#include <cstdio>

/* 0xff used like a mask of 11111111, so this put in reverse */
const uint first_byte = 24;
const uint second_byte = 16;
const uint third_byte = 8;
const uint fourth_byte = 0;

struct Color{
    Color(){
        r = g = b = a = 0;
    }

    Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    explicit Color(uint32_t rgba){
        this->r = (rgba >> first_byte) & 0xff;
        this->g = (rgba >> second_byte) & 0xff;
        this->b = (rgba >> third_byte) & 0xff;
        this->a = (rgba >> fourth_byte) & 0xff;
    }

    uint8_t r, g, b, a;
};


struct Coord{
    Coord(){
        x1 = y1 = x2= y2 = 0;
    }

    Coord(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    uint32_t x1, y1,x2,y2;
};


class GraphicsItem{
public:
    GraphicsItem(){
        width = 0;
        itemType = 'L';
    }

    GraphicsItem(uint32_t X1, uint32_t Y1, uint32_t X2, uint32_t Y2, uint8_t R, uint8_t G, uint8_t B, uint8_t A, int LineWidth, char LineItem){
        coord = Coord(X1, Y1, X2, Y2);
        color = Color(R,G,B,A);
        width = LineWidth;
        itemType = LineItem;
    }

    GraphicsItem(uint32_t X1, uint32_t Y1, uint32_t X2, uint32_t Y2, Color c, int LineWidth, char LineItem){
        coord = Coord(X1, Y1, X2, Y2);
        color = c;
        width = LineWidth;
        itemType = LineItem;
    }

    GraphicsItem(const GraphicsItem *) = delete;

    ~GraphicsItem() = default;

    [[nodiscard]] uint32_t GetColorR() const {return color.r;}
    [[nodiscard]] uint32_t GetColorG() const {return color.g;}
    [[nodiscard]] uint32_t GetColorB() const {return color.b;}
    [[nodiscard]] uint32_t GetColorA() const {return color.a;}

    [[nodiscard]] uint32_t GetX1() const {return coord.x1;}
    [[nodiscard]] uint32_t GetY1() const {return coord.y1;}
    [[nodiscard]] uint32_t GetX2() const {return coord.x2;}
    [[nodiscard]] uint32_t GetY2() const {return coord.y2;}

    [[nodiscard]] uint32_t GetWidth() const {return width;}

    [[nodiscard]] char GetLineItem() const {return itemType;}

private:
    Color color;
    Coord coord;
    int width;
    char itemType;
};

#endif //TUTORIAL_GRAPHICSITEM_H
