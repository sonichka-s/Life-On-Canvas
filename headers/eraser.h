#ifndef ERASER_H
#define ERASER_H

#include "headers/tool.h"

class Eraser : public Tool
{

public:

    void paint(QPoint) override;
    void mouseMoved(QMouseEvent *) override;
    void mouseClicked(QMouseEvent *) override;
    void mouseReleased(QMouseEvent *) override;

    void setWidth(const int width) override;

private:
    QPoint lastPoint;
};

#endif // ERASER_H
