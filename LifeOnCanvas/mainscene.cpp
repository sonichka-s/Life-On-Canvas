#include <QDebug>
#include "mainscene.h"

MainScene::MainScene()
{
   // Инициализировать кисть-ластик
    pen_eraser = new QPen(*(new QColor("white")));
    pen_eraser->setWidth(10);
}

void MainScene::setType(QString t)
{
    draw_type = t;
    qDebug()<<"in MainScene::setType: set type"<<t;
}

QString MainScene::getType()
{
    return draw_type;
}

void MainScene::setRect(QRectF rect)
{
    draw_rect = rect;
}

QRectF MainScene::getRect()
{
    return draw_rect;
}

void MainScene::setPen(QPen *p)
{
    pen = p;
}

QPen *MainScene::getPen()
{
    return pen;
}

void MainScene::setBrush(QBrush *b)
{
   brush = b;
}

QBrush *MainScene::getBrush()
{
    return brush;
}

void MainScene::mousePressd(QMouseEvent *event)
{
    /* Запись положения при нажатии мыши
    start_point больше не будет меняться до того, как мышь будет отпущена, 
    а значение end_point будет меняться по мере перемещения мыши */
    start_point = end_point = event->pos();

    // Определение различных типов чертежей на основе значения строки
    if(draw_type == "Line") // Прямые линии
    {
        // Создать новый тип строки и сохранить его в векторе элементов
        QGraphicsLineItem *lineItem = new QGraphicsLineItem();
        lineItem->setLine(start_point.x(), start_point.y(),
                          end_point.x(), end_point.y());
        lineItem->setPen(*pen);
        /* Добавить текущий элемент в вектор элементов, то есть все элементы, 
        присутствующие в сцене, индексируются по элементам*/
        items.push_back(lineItem);
        /* Добавить текущий элемент в сцену с помощью функции addItem() QGrsphicsScene
        для дальнейшего отображения */
        addItem(lineItem);
    }
    else if(draw_type == "Rectangle")   // Прямоугольник
    {
        QGraphicsRectItem *rectItem = new QGraphicsRectItem();
        rectItem->setRect(*(new QRect(start_point, end_point)));
        rectItem->setPen(*pen);
        rectItem->setBrush(*brush);
        items.push_back(rectItem);
        addItem(rectItem);
    }
    else if(draw_type == "Ellipse")     // Эллипс
    {
        QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem();
        ellipseItem->setRect(*(new QRect(start_point, end_point)));
        ellipseItem->setPen(*pen);
        ellipseItem->setBrush(*brush);
        items.push_back(ellipseItem);
        addItem(ellipseItem);
    }

    else if(draw_type == "Free" || draw_type == "Eraser")   // Свободная кривая или ластик
    {
       /* В процессе нажатия и перемещения мыши большое количество 
        сегментов линии соединяется для получения свободных кривых */

       /* Ластик - это, по сути, белая свободная кривая определенной ширины, 
        которая используется для покрытия содержимого, подлежащего удалению */

        freePointLast = start_point;    // Записать последнюю конечную точку свободной кривой, которая будет постоянно обновляться
       /* Создать новую группу элементов и добавить все сегменты линии,
        составляющие свободную кривую, в группу для управления */

        /* После создания группы с помощью createItemGroup() сам элемент группы будет автоматически 
        добавлен в сцену, и нет необходимости добавлять его отдельно. */
        freeGroup = createItemGroup(*(new QList<QGraphicsItem*>));
        items.push_back(freeGroup);     // Добавить группу в целом к элементам в качестве элемента
       // Сгенерировать первый отрезок линии (точку) и добавьте его в группу
        QGraphicsLineItem* lineItem = new QGraphicsLineItem();
        lineItem->setLine(freePointLast.x(), freePointLast.y(),
                          end_point.x(), end_point.y());
        if(draw_type == "Free")
        {
            lineItem->setPen(*pen);
        }
        else
        {
            lineItem->setPen(*pen_eraser);
        }
        freeGroup->addToGroup(lineItem);
    }
}

void MainScene::mouseMoved(QMouseEvent *event)  // Продолжить обновлять статус элемента при перемещении мыши
{
    end_point = event->pos();  // Записать положение, в которое перемещается мышь
    if(draw_type == "Line")
    {
      /* Привести тип, извлечь последний элемент в элементах,
        который является элементом текущей операции, а затем обновите элемент */
        QGraphicsLineItem* lineItem = static_cast<QGraphicsLineItem*>(items.last());
        lineItem->setLine(start_point.x(), start_point.y(),
                          end_point.x(), end_point.y());
    }
    else if(draw_type == "Rectangle")
    {
        QGraphicsRectItem* rectItem = static_cast<QGraphicsRectItem*>(items.last());
        rectItem->setRect(*(new QRect(start_point, end_point)));
    }
    else if(draw_type == "Ellipse")
    {
        QGraphicsEllipseItem* ellipseItem = static_cast<QGraphicsEllipseItem*>(items.last());
        ellipseItem->setRect(*(new QRect(start_point, end_point)));
    }

    else if(draw_type == "Free" || draw_type == "Eraser")
    {
       /* Каждый раз, когда обнаруживается сигнал движения мыши, 
        рисуется отрезок линии от последней конечной точки до текущей конечной точки мыши */
        QGraphicsLineItem* lineItem = new QGraphicsLineItem();
        lineItem->setLine(freePointLast.x(), freePointLast.y(),
                          end_point.x(), end_point.y());
        if(draw_type == "Free")
        {
            lineItem->setPen(*pen);
        }
        else
        {
            lineItem->setPen(*pen_eraser);
        }
        freeGroup->addToGroup(lineItem);    // Добавить этот отрезок линии в группу свободных кривых
        freePointLast = end_point;          // Обновить последнюю конечную точку свободной кривой
    }

    update(draw_rect);                     // Используем функцию слота update() для обновления отображения на экране
}

void MainScene::mouseReleased(QMouseEvent *event)   // Когда мышь отпущена, параметры элемента окончательно определены, и рисование завершено
{
    end_point = event->pos();
    if(draw_type == "Line")
    {
        QGraphicsLineItem* lineItem = static_cast<QGraphicsLineItem*>(items.last());
        lineItem->setLine(start_point.x(), start_point.y(),
                          end_point.x(), end_point.y());
    }
    else if(draw_type == "Rectangle")
    {
        QGraphicsRectItem* rectItem = static_cast<QGraphicsRectItem*>(items.last());
        rectItem->setRect(*(new QRect(start_point, end_point)));
    }
    else if(draw_type == "Ellipse")
    {
        QGraphicsEllipseItem* ellipseItem = static_cast<QGraphicsEllipseItem*>(items.last());
        ellipseItem->setRect(*(new QRect(start_point, end_point)));
    }

    else if(draw_type == "Free")
    {
    }

    else if(draw_type == "Eraser")
    {
    }
    update(draw_rect);
}

void MainScene::deleteOne()
{
    if(!items.isEmpty())
    {
        removeItem(items.last());
        items.pop_back();
        update(draw_rect);
    }
}


