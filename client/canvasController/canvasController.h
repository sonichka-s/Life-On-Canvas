
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
    CanvasController();
    ~CanvasController();

    void initCanvas();



private:

    QGraphicsScene* mainScene;
    QTimer* timer;
    QTcpSocket* socket;

    Serializer* serializer;
    unsigned int CanvasId;

    QVector<QGraphicsLineItem*> currentFreeLineItems;


    void sendDiff( std::vector<LineItem> diffArr);

    void setTimer(QTimer* timer);

    std::vector<LineItem> convertQLineItems(const QVector<QGraphicsLineItem*>& lineItems);

public slots:

    void onReadyRead();
    void onReceivedMessage(QString responseStr);
    void sendRegularRequest();

    void onMousePressed();
    void onMouseMoved(QGraphicsLineItem *lineItem);
    void onMouseReleased();


signals:

    void receivedToRender(QString responseStr);

};


#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
