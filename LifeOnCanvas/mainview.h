#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QGraphicsView>
#include "mainscene.h"


class MainView : public QGraphicsView
{
public:
    MainView(MainScene *scene);

protected:
    /* События мыши автоматически запускаются в основном программном цикле, 
    а захват событий и реагирование на них достигаются путем 
    перезаписи следующих трех функций */
    void mousePressEvent(QMouseEvent *event);   // Событие нажатия мыши
    void mouseMoveEvent(QMouseEvent *event);    // Событие перемещения мыши (по умолчанию срабатывает только после нажатия)
    void mouseReleaseEvent(QMouseEvent *event); // Событие освобождения мыши

private:
    MainScene *scene;
};

#endif // MAINVIEW_H
