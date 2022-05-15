#include <QDebug>
#include "mainscene.h"

MainScene::MainScene()
{
   // Инициализировать кисть-ластик
    pen_eraser = new QPen(*(new QColor("white")));
    pen_eraser->setWidth(10);

    brush_text = new QBrush(*(new QColor("black")), Qt::SolidPattern);

    font = QFont("Times", 18, QFont::Normal);
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

void MainScene::setFont(QFont f)
{
    font = f;
}

QFont MainScene::getFont()
{
    return font;
}

void MainScene::setText(QString t)
{
    text = t;
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
        // Создайте новый тип строки и сохраните его в векторе элементов
        QGraphicsLineItem *lineItem = new QGraphicsLineItem();
        lineItem->setLine(start_point.x(), start_point.y(),
                          end_point.x(), end_point.y());
        lineItem->setPen(*pen);
        /* Добавить текущий элемент в вектор элементов, то есть все элементы, 
        присутствующие в сцене, индексируются по элементам*/
        items.push_back(lineItem);
        /* Добавьте текущий элемент в сцену с помощью функции addItem() QGrsphicsScene 
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
    else if(draw_type == "Polygon")     // Многоугольник
    {
        /* В процессе рисования многоугольника вам нужно несколько раз щелкнуть левой 
        кнопкой мыши, чтобы определить ключевые точки, и, наконец, щелкнуть 
        правой кнопкой мыши, чтобы подтвердить все ключевые точки */
        if(event->button() == Qt::LeftButton)  // Щелкните левой кнопкой мыши, чтобы добавить ключевые точки
        {
            /* Набор ключевых точек не является пустым, что указывает на наличие точек, 
            которые были добавлены ранее. В дополнение к добавлению ключевых точек 
            вам также необходимо добавить существующие ребра.*/

            /* Края временно рисуются линейными элементами, и все они удаляются 
            после выбора ключевых точек (то есть щелчка правой кнопкой мыши). */
            if(!polygonPoints.isEmpty())
            {
                QPoint p1 = polygonPoints.last();
                QPoint p2 = start_point;
                QGraphicsLineItem *lineItem = new QGraphicsLineItem();
                lineItem->setLine(p1.x(), p1.y(), p2.x(), p2.y());
                lineItem->setPen(*pen);
                polygonLines.push_back(lineItem);   // Добавить все временные сегменты линии в вектор для управления
                polygonPoints.push_back(start_point);   // Добавить ключевые точки в набор ключевых точек
                addItem(lineItem);
            /* update() - это функция слота QGraphicsScene, которая используется для 
            обновления экрана в указанном прямоугольном поле */
                update(draw_rect);
            }
            /* Набор ключевых точек - это пустой набор, что означает, что теперь это первая ключевая точка. 
            Вам нужно только добавить точки, и вам не нужно рисовать линии. */
            else
            {
                polygonPoints.push_back(start_point);
            }
        }
        else if(event->button() == Qt::RightButton) // Щелкните правой кнопкой мыши, многоугольник будет нарисован
        {
            if(!polygonPoints.isEmpty())
            {
               // Удалить все временно нарисованные края
                while(!polygonLines.isEmpty())
                {
                    removeItem(polygonLines.last());
                    polygonLines.pop_back();
                }
                // Создайте новый элемент типа полигона с существующими ключевыми точками
                QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem();
                polygonItem->setPolygon(*(new QPolygonF(polygonPoints)));
                polygonItem->setPen(*pen);
                polygonItem->setBrush(*brush);
                items.push_back(polygonItem);
                addItem(polygonItem);
               // Согласно официальной документации, рекомендуемые методы освобождения QVector и освобождения места следующие
                QVector<QPoint>().swap(polygonPoints);
            }
        }
    }
    else if(draw_type == "Free" || draw_type == "Eraser")   // Свободная кривая или ластик
    {
       /* В процессе нажатия и перемещения мыши большое количество 
        сегментов линии соединяется для получения свободных кривых */

       /* Ластик - это, по сути, белая свободная кривая определенной ширины, 
        которая используется для покрытия содержимого, подлежащего удалению */

        freePointLast = start_point;    // Запишите последнюю конечную точку свободной кривой, которая будет постоянно обновляться
       /* Создайте новую группу элементов и добавить все сегменты линии, 
        составляющие свободную кривую, в группу для управления */

        /* После создания группы с помощью createItemGroup() сам элемент группы будет автоматически 
        добавлен в сцену, и нет необходимости добавлять его отдельно. */
        freeGroup = createItemGroup(*(new QList<QGraphicsItem*>));
        items.push_back(freeGroup);     // Добавить группу в целом к элементам в качестве элемента
       // Сгенерируйте первый отрезок линии (точку) и добавьте его в группу
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
    else if(draw_type == "Text")        // Текст
    {
        QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem();
        if(!text.isEmpty())
        {
            textItem->setText(text);
            textItem->setFont(font);
            textItem->setPos(end_point);
            textItem->setPen(*pen);
            brush_text->setColor(pen->color());// Сохраняйте тот же цвет, что и линия, каждый раз, когда вы рисуете
            textItem->setBrush(*brush_text);
            items.push_back(textItem);
            addItem(textItem);
        }
    }
}

void MainScene::mouseMoved(QMouseEvent *event)  // Продолжайте обновлять статус элемента при перемещении мыши
{
    end_point = event->pos();  // Запишите положение, в которое перемещается мышь
    if(draw_type == "Line")
    {
      /* Приведите тип, извлеките последний элемент в элементах, 
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
    else if(draw_type == "Polygon")
    {
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
        freeGroup->addToGroup(lineItem);    // Добавьте этот отрезок линии в группу свободных кривых
        freePointLast = end_point;          // Обновить последнюю конечную точку свободной кривой
    }
    else if(draw_type == "Text")
    {
    }
    update(draw_rect);                     // Используйте функцию слота update() для обновления отображения на экране
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
    else if(draw_type == "Polygon")
    {
    }
    else if(draw_type == "Free")
    {
    }
    else if(draw_type == "Text")
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

void MainScene::deleteAll()
{
    while(!items.isEmpty())
    {
        removeItem(items.last());
        items.pop_back();
    }
    update(draw_rect);
}
