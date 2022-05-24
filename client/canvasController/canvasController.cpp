
#include "canvasController.h"

#include <nlohmann/json.hpp>
#include <QTimer>



CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    serializer = new Serializer();


    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(receivedToRender(QString )), this, SLOT(onReceivedMessage(QString )));
    connect(timer, SIGNAL(timeout()), this, SLOT(sendRegularRequest()));

    connect(mainScene, SIGNAL(mousePressedSignal()), this, SLOT(onMousePressed()));
    connect(mainScene, SIGNAL(mouseMovedSignal(QGraphicsLineItem* )), this, SLOT(onMouseMoved(QGraphicsLineItem*)));
    connect(mainScene, SIGNAL(mouseReleasedSignal()), this, SLOT(onMouseReleased()));



}


void CanvasController::initCanvas() {

    socket->connectToHost("127.0.0.1", 4269);


    if(socket->waitForConnected())
    {

        this->setTimer(timer);

        qDebug() << "Connected!";

    }
    else
    {
        qDebug() << "Not connected!";
    }

}



void CanvasController::sendDiff( std::vector<LineItem> diffArr) {


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

void CanvasController::onMousePressed(){
    currentFreeLineItems.clear();
}

void CanvasController::onMouseMoved(QGraphicsLineItem *lineItem){
    currentFreeLineItems.push_back(lineItem);

}

void CanvasController::onMouseReleased(){

    std::vector<LineItem> diffToSend = convertQLineItems(currentFreeLineItems);
    this->sendDiff(diffToSend);
}


std::vector<LineItem> CanvasController::convertQLineItems(const QVector<QGraphicsLineItem *> &lineItems) {
    std::vector<LineItem> diffArray;
    for ( int i = 0; i < lineItems.size(); ++i) {
        LineItem itemToConvert;
        itemToConvert.x1 = static_cast<float>(lineItems[i]->line().x1());
        itemToConvert.y1 = static_cast<float>(lineItems[i]->line().y1());
        itemToConvert.x2 = static_cast<float>(lineItems[i]->line().x2());
        itemToConvert.y2 = static_cast<float>(lineItems[i]->line().y2());
        itemToConvert.width = lineItems[i]->pen().width();
        itemToConvert.color.r = lineItems[i]->pen().color().red();
        itemToConvert.color.g = lineItems[i]->pen().color().green();
        itemToConvert.color.b = lineItems[i]->pen().color().blue();
        itemToConvert.color.a = lineItems[i]->pen().color().alpha();
        diffArray.push_back(itemToConvert);
    }
    return diffArray;
}

void CanvasController::setTimer(QTimer* timer) {
   timer->start(100);
}

CanvasController::~CanvasController(){
    delete socket;
    delete serializer;
    delete timer;
}