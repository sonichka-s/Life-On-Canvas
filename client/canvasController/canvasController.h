
#ifndef LIFE_ON_CANVAS_CANVASCONTROLLER_H
#define LIFE_ON_CANVAS_CANVASCONTROLLER_H

#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>
#include <QHostAddress>

#include "serializer.h"


class CanvasController: public QObject{
    Q_OBJECT
public:

    explicit CanvasController(QGraphicsScene* mainScene);
    CanvasController();
    ~CanvasController();

    void initCanvas();
    void sendDiff( std::vector<Point> diffArr);


private:

    QGraphicsScene* mainScene;
    QTimer* timer;
    QTcpSocket* socket;

    Serializer* serializer;
    unsigned int CanvasId;

    void mousePressed(QMouseEvent *event);
    void setTimer(QTimer* timer);

public slots:

    void onReadyRead();
    void onReceivedMessage(QString responseStr);
    void sendRegularRequest();

signals:

    void receivedToRender(QString responseStr);

};


#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
