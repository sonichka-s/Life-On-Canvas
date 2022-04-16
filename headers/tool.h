#ifndef TOOL_H
#define TOOL_H



class Tool : public QObject
{

public:
    //Tool(const QColor);

    virtual void mouseClicked(QMouseEvent*);
    virtual void mouseMoved(QMouseEvent*) ;
    virtual void mouseReleased(QMouseEvent*) ;

    virtual void setWidth(const int width) ;

protected:
    virtual void paint(QPoint);
    QColor* myColor;
    int myWidth;
    QImage *image;
    bool modified = false;

    Tool(QColor*, const int, QImage*);
    Tool(QColor*, QImage*);
    Tool(QImage*);

private:
};

#endif // TOOL_H
