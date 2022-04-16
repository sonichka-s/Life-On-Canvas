#ifndef BUCKET_H
#define BUCKET_H

#include "headers/tool.h"

class Bucket : public Tool
{
public:

    void paint(QPoint) override;
    void mouseMoved(QMouseEvent *) override;
    void mouseClicked(QMouseEvent *) override;
    void mouseReleased(QMouseEvent *) override;

    void setWidth(const int width) override;
    void colorFill(QPoint startPoint, QColor color);

private:
    QPoint lastPoint;
};

#endif // BUCKET_H
