
#ifndef LIFE_ON_CANVAS_CANVASCONTROLLER_H
#define LIFE_ON_CANVAS_CANVASCONTROLLER_H

#include <QCoreApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItemGroup>
#include <QtWebSockets/QWebSocket>
#include <QUrl>



#include "serializer.h"




class CanvasController: public QObject {
    Q_OBJECT
public:
    explicit CanvasController(QGraphicsScene* mainScene);
    ~CanvasController();

private:

    QGraphicsScene* mainScene;
    QTimer* timer;
    QWebSocket* socket;
    const std::vector<GraphicsItem> buffer;

    unsigned int CanvasId;

    QVector<QGraphicsLineItem*> currentFreeLineItems;


    void setTimer(QTimer* timer);
    void sendDiff( const std::vector<GraphicsItem> &diffArr);
    void displayItems(const std::vector<GraphicsItem> &itemsToDisplay);
    std::vector<GraphicsItem> convertQLineItems(const QVector<QGraphicsLineItem*>& lineItems);

public slots:
    void initCanvas();

    //network processing slots
    void onConnected();
    void sendRegularRequest();
    void onResponseReceived(const QString &responseStr);

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
