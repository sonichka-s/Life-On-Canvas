#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "headers/tool.h"

class ColorPicker : public Tool
{
 
public:

    void paint(QPoint) override;
    void mouseMoved(QMouseEvent *) override;
    void mouseClicked(QMouseEvent *) override;
    void mouseReleased(QMouseEvent *) override;

    void setWidth(const int width) override;


private:
    QPoint lastPoint;
    QColor *myPrimary, *mySecondary;
    Qt::MouseButton pickerButton;

    void setColor(QColor color);
};

#endif // COLORPICKER_H
