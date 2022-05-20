
#ifndef LIFE_ON_CANVAS_CANVASCONTROLLER_H
#define LIFE_ON_CANVAS_CANVASCONTROLLER_H

#include <QCoreApplication>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTcpSocket>
#include <QUrl>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>

#include "serializer.h"
#include "networkController.h"



class CanvasController: public QObject{
    Q_OBJECT
public:

    CanvasController(QGraphicsScene* mainScene);
    ~CanvasController();

private:

    QGraphicsScene* mainScene;
    Serializer* serializer;
    int CanvasId;
    int initCanvas();
    void mousePressed(QMouseEvent *event);

    void sendData();

    QTcpSocket* socket;
public slots:

    void onReadyRead();
    void connected();
    void disconnected();



signals:

    void receivedToRender();

};



#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
