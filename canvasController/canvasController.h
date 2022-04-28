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
    CanvasController(QMainWindow* mainWindow, NetworkController* netMng, Serializer serializer);
    ~CanvasController();
private:

    QMainWindow* mv;
    NetworkController* netMng;
    Serializer* serializer;

private slots:



signals:

    void receivedToRender();

};



#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
