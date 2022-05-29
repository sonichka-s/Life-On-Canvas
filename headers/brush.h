#ifndef BRUSH_H
#define BRUSH_H

#include "headers/tool.h"

class Brush : public Tool
{
public:


    void paint(QPoint) override;
    void mouseMoved(QMouseEvent *) override;
    void mouseClicked(QMouseEvent *) override;
    void mouseReleased(QMouseEvent *) override;

    int penWidth() const;
    void setWidth(const int width) override;
private:
    QPoint lastPoint;
};

#endif // BRUSH_H
