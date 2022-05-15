#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>


class MainScene : public QGraphicsScene
{
public:
    MainScene();

    void setType(QString t);    // Установка типа чертежа
    QString getType();          // Получить тип чертежа
    void setRect(QRectF rect); // Установите область обновления
    QRectF getRect();          // Получить область обновления
    void setPen(QPen *p);       // Набор кистей
    QPen *getPen();             // Получить кисть
    void setBrush(QBrush *b);   // Установите кисть
    QBrush *getBrush();        // Достань щетку
    void setFont(QFont f);      // Установить шрифт
    QFont getFont();            // Получить шрифт
    void setText(QString t);    // Установить для рисования текста
    void deleteOne();          // Возврат к предыдущей операции
    void deleteAll();         // Очистите чертежную доску
    void mousePressd(QMouseEvent *event);   // Реагировать на событие нажатия мыши
    void mouseMoved(QMouseEvent *event);    // Реагировать на события перемещения мыши
    void mouseReleased(QMouseEvent *event); // Реагировать на событие отпускания мыши

private:
    QString draw_type = "None";    // Тип чертежа метки
    QRectF draw_rect;              // Область обновления просмотра хранилища
    QPen *pen;                     // Основная щетка
    QPen *pen_eraser;               // Кисть, используемая для реализации ластика
    QBrush *brush;                  // Основная щетка
    QBrush *brush_text;             
    QFont font;                    
    QString text;                   // Текстовое содержимое чертежа
    QPoint start_point, end_point;  // Начальная и конечная точки щелчков мыши
    QVector<QGraphicsItem*> items;  // Сохранить все элементы, добавленные во время рисования
    QVector<QPoint> polygonPoints;  // Сохранить все точки, полученные щелчком мыши во время рисования полигона
    QVector<QGraphicsLineItem*> polygonLines;   // Временное сохранение сегментов линий, созданных во время рисования полигонов
    QPoint freePointLast;          // Сохранение предыдущей конечной точки при рисовании свободной кривой
    QGraphicsItemGroup* freeGroup;  // Коллекция элементов, используемая для хранения всех сегментов линий, созданных при рисовании свободных кривых
};

#endif // MAINSCENE_H
