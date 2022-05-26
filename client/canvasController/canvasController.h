
#ifndef LIFE_ON_CANVAS_CANVASCONTROLLER_H
#define LIFE_ON_CANVAS_CANVASCONTROLLER_H

#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>
#include <QHostAddress>
#include <QGraphicsItemGroup>

#include "serializer.h"


class CanvasController: public QObject{
    Q_OBJECT
public:
    explicit CanvasController(QGraphicsScene* mainScene);
    ~CanvasController();

    void initCanvas();

private:

    QGraphicsScene* mainScene;
    QTimer* timer;
    QTcpSocket* socket;

    Serializer* serializer;
    unsigned int CanvasId;

    QVector<QGraphicsLineItem*> currentFreeLineItems;


    void setTimer(QTimer* timer);

    void sendDiff( std::vector<GraphicsItem> diffArr);

    std::vector<GraphicsItem> convertQLineItems(const QVector<QGraphicsLineItem*>& lineItems);

public slots:

    //network processing slots
    void sendRegularRequest();
    void onReadyRead();
    void onResponseReceived(QString responseStr);

    //free curve draw tracking slots
    void onMousePressedFreeCurve();
    void onMouseMovedFreeCurve(QGraphicsLineItem *lineItem);
    void onMouseReleasedFreeCurve();

    //single line item draw tracking slot
    void onMouseReleasedSingleLine(QGraphicsLineItem* lineItem);

    //ellipse item draw tracking slot
    void onMouseReleasedEllipse(QGraphicsEllipseItem* ellipseItem);

    // rectangle item draw tracking slot
    void onMouseReleasedRectangle(QGraphicsRectItem* rectItem);

signals:

    void responseReceived(QString responseStr);
};


#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
