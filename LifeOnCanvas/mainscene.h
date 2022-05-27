#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>

#include "canvasController.h"

class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainScene();

    void setController(CanvasController* controller_);
    CanvasController* getController();
    void addItemToVector(QGraphicsItem* graphicsItem);

    void setType(QString t);    // Установка типа чертежа
    QString getType();          // Получить тип чертежа
    void setRect(QRectF rect);  // Установка области обновления
    QRectF getRect();           // Получить область обновления
    void setPen(QPen *p);       // Набор кистей
    QPen *getPen();             // Получить кисть
    void setBrush(QBrush *b);
    QBrush *getBrush();         // Получить кисть
    void deleteOne();           // Возврат к предыдущей операции
    void mousePressd(QMouseEvent *event);   // Реагировать на событие нажатия мыши
    void mouseMoved(QMouseEvent *event);    // Реагировать на события перемещения мыши
    void mouseReleased(QMouseEvent *event); // Реагировать на событие отпускания мыши

private:
    CanvasController* controller;

    QString draw_type = "None";    // Тип чертежа метки
    QRectF draw_rect;              // Область обновления просмотра хранилища
    QPen *pen;                     // Основная кисть
    QPen *pen_eraser;               // Кисть, используемая для реализации ластика
    QBrush *brush;
    QFont font;
    QPoint start_point, end_point;  // Начальная и конечная точки щелчков мыши
    QVector<QGraphicsItem*> items;  // Сохранить все элементы, добавленные во время рисования
    QPoint freePointLast;          // Сохранение предыдущей конечной точки при рисовании свободной кривой
    QGraphicsItemGroup* freeGroup;  // Коллекция элементов, используемая для хранения всех сегментов линий, созданных при рисовании свободных кривых


signals:
    void mousePressedFreeCurve();
    void mouseMovedFreeCurve(QGraphicsLineItem*);
    void mouseReleasedFreeCurve();

    void mouseReleasedSingleLine(QGraphicsLineItem* );

    void mouseReleasedEllipse(QGraphicsEllipseItem*);

    void mouseReleasedRectangle(QGraphicsRectItem* );

};

#endif // MAINSCENE_H