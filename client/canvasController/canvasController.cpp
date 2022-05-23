
#include "canvasController.h"

#include <nlohmann/json.hpp>
#include <QJsonObject>

CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QTcpSocket(this);
    serializer = new Serializer();

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(receivedToRender(QString responseStr)), this, SLOT(onReceivedMesage(QString responseStr)));


}

CanvasController::CanvasController(): CanvasId ( 0 ){

    socket = new QTcpSocket(this);
    serializer = new Serializer();

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(receivedToRender(QString )), this, SLOT(onReceivedMessage(QString )));


}

void CanvasController::initCanvas() {

    socket->connectToHost("127.0.0.1", 4269);

    if(socket->waitForConnected())
    {

        qDebug() << "Connected!";

    }
    else
    {
        qDebug() << "Not connected!";
    }

}



void CanvasController::sendDiff( std::vector<Point> diffArr) {


    nlohmann::json jsonToSend = serializer->serializeDiff(diffArr, CanvasId);

    QString toSend = QString::fromUtf8(jsonToSend.dump().c_str());

    socket->write(toSend.toUtf8());

    if (!socket->waitForReadyRead()){
        qDebug() << "connection is lost";
    }

}


void CanvasController::onReadyRead(){


    qDebug() << "Reading: " << socket->bytesAvailable();

    QByteArray response = socket->readAll();

    QString responseStr = QString(response);

    emit receivedToRender(responseStr);

}

void CanvasController:: onReceivedMessage(QString responseStr) {



    qDebug() << responseStr;
}

void CanvasController::mousePressed(QMouseEvent *event){



}

CanvasController::~CanvasController(){
    delete socket;
    delete serializer;
}