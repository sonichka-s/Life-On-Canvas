
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
#include <QHostAddress>

#include "serializer.h"
#include "networkController.h"



class CanvasController: public QObject{
    Q_OBJECT
public:

    explicit CanvasController(QGraphicsScene* mainScene);
    ~CanvasController();

private:

    QGraphicsScene* mainScene;
    Serializer* serializer;
    QTcpSocket* socket;
    unsigned int CanvasId;

    unsigned int initCanvas();
    unsigned int getCanvasById(int canvasID);

    void sendDiff();

    void mousePressed(QMouseEvent *event);


public slots:

    void onReadyRead();
    void connected();
    void disconnected();
    void onReceivedMesage(nlohmann::json inJson);


signals:

    void receivedToRender(nlohmann::json inJson);

};



#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
