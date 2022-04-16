#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "headers/tool.h"

class Triangle : public Tool
{
    
public:
  
    void paint(QPoint) override;
    void mouseMoved(QMouseEvent *) override;
    void mouseClicked(QMouseEvent *) override;
    void mouseReleased(QMouseEvent *) override;

    void setWidth(const int width) override;

private:
    QPoint lastPoint;
    QPoint Point1;
    QPoint Point2;
    QPoint Point3;
    QImage tmp;
    QImage localCopy;
    bool finallDrawing;
};


#endif // TRIANGLE_H
