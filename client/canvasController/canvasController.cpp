
#include "canvasController.h"

#include <nlohmann/json.hpp>
#include <QTimer>


CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    serializer = new Serializer();


    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(receivedToRender(QString responseStr)), this, SLOT(onReceivedMesage(QString responseStr)));

    //event loop neded to start timer, set timer in application or scene
    connect(timer, SIGNAL(timeout()), this, SLOT(sendRegularRequest()));

}

CanvasController::CanvasController(): CanvasId ( 0 ){

    socket = new QTcpSocket(this);
    timer = new QTimer;

    serializer = new Serializer();


    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(receivedToRender(QString )), this, SLOT(onReceivedMessage(QString )));

    //event loop neded to start timer, set timer in application or scene
    connect(timer, SIGNAL(timeout()), this, SLOT(sendRegularRequest()));

}

void CanvasController::initCanvas() {

    socket->connectToHost("127.0.0.1", 4269);


    if(socket->waitForConnected())
    {

        //this->setTimer(timer);


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

void CanvasController::sendRegularRequest() {

    nlohmann::json jsonToSend;
    jsonToSend["Type"] = "Get";
    jsonToSend["canvasId"] = CanvasId;

    QString toSend = QString::fromUtf8(jsonToSend.dump().c_str());

    socket->write(toSend.toUtf8());

    if (!socket->waitForReadyRead()){
        qDebug() << "connection is lost";
    }

}

void CanvasController:: onReceivedMessage(QString responseStr) {


    qDebug() << responseStr;
}

void CanvasController::mousePressed(QMouseEvent *event){



}

void CanvasController::setTimer(QTimer* timer) {
   timer->start(100);
}

CanvasController::~CanvasController(){
    delete socket;
    delete serializer;
    delete timer;
}