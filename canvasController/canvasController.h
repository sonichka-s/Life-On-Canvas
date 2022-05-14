//
// Created by egornulllet on 20.04.22.
//

#ifndef LIFE_ON_CANVAS_CANVASCONTROLLER_H
#define LIFE_ON_CANVAS_CANVASCONTROLLER_H

#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QObject>

#include "serializer.h"
#include "networkController.h"



class CanvasController {

public:
    CanvasController(QGraphicsScene* mainScene);
    ~CanvasController();
private:
    QGraphicsScene* mc;
    NetworkController* netMng;
    Serializer* serializer;
    int CanvasId;


    int initCanvas();

    void mousePressed(QMouseEvent *event);
private slots:



signals:

    void receivedToRender();

};



#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
