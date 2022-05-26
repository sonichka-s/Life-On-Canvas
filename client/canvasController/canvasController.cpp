
#include "canvasController.h"

#include <nlohmann/json.hpp>
#include <QTimer>



CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    serializer = new Serializer();

    //connect network signals
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));

    connect(this, SIGNAL(responseReceived(QString)),
            this, SLOT(onResponseReceived(QString)));

    connect(timer, SIGNAL(timeout()),
            this, SLOT(sendRegularRequest()));

    //connect scene signals
    connect(mainScene, SIGNAL(mousePressedFreeCurve()),
            this, SLOT(onMousePressedFreeCurve()));
    connect(mainScene, SIGNAL(mouseMovedFreeCurve(QGraphicsLineItem* )),
            this, SLOT(
            onMouseMovedFreeCurve(QGraphicsLineItem * )));
    connect(mainScene, SIGNAL(mouseReleasedFreeCurve()),
            this, SLOT(onMouseReleasedFreeCurve()));

    connect(mainScene, SIGNAL(mouseReleasedEllipse(QGraphicsEllipseItem* )),
            this, SLOT(onMouseReleasedEllipse(QGraphicsEllipseItem* )));
    connect(mainScene, SIGNAL(mouseReleasedSingleLine(QGraphicsLineItem* )),
            this, SLOT(onMouseReleasedSingleLine(QGraphicsLineItem* )));
    connect(mainScene, SIGNAL(mouseReleasedRectangle(QGraphicsRectItem* )),
            this, SLOT(onMouseReleasedRectangle(QGraphicsRectItem* )));
}

void CanvasController::initCanvas() {

    socket->connectToHost("127.0.0.1", 4269);

    if(socket->waitForConnected()){

        this->setTimer(timer);

        qDebug() << "Connected!";
    } else {

        qDebug() << "Not connected!";
    }

}

void CanvasController::setTimer(QTimer* timer) {

    timer->start(100);
}

void CanvasController::sendDiff( std::vector<GraphicsItem> diffArr) {

    nlohmann::json jsonToSend = serializer->serializeDiff(diffArr, CanvasId);
    QString toSend = QString::fromUtf8(jsonToSend.dump().c_str());

    socket->write(toSend.toUtf8());

    if (!socket->waitForReadyRead()){

        qDebug() << "connection is lost";
    }
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

void CanvasController::onReadyRead(){

    qDebug() << "Reading: " << socket->bytesAvailable();

    QByteArray response = socket->readAll();
    QString responseStr = QString(response);

    emit responseReceived(responseStr);
}

void CanvasController:: onResponseReceived(QString responseStr) {

    qDebug() << responseStr;
}

void CanvasController::onMousePressedFreeCurve(){

    currentFreeLineItems.clear();
}

void CanvasController::onMouseMovedFreeCurve(QGraphicsLineItem *lineItem){

    currentFreeLineItems.push_back(lineItem);
}

void CanvasController::onMouseReleasedFreeCurve(){

    std::vector<GraphicsItem> diff = convertQLineItems(currentFreeLineItems);
    this->sendDiff(diff);
}


void CanvasController::onMouseReleasedSingleLine(QGraphicsLineItem* lineItem){

    GraphicsItem itemToSend(lineItem);
}


void CanvasController::onMouseReleasedEllipse(QGraphicsEllipseItem* ellipseItem){

    GraphicsItem itemToSend(ellipseItem);
}


void CanvasController::onMouseReleasedRectangle(QGraphicsRectItem* rectItem){
    GraphicsItem itemToSend(rectItem);

}

std::vector<GraphicsItem> CanvasController::convertQLineItems(const QVector<QGraphicsLineItem *> &lineItems) {

    std::vector<GraphicsItem> diffArray;
    for ( int i = 0; i < lineItems.size(); ++i) {
        GraphicsItem itemToConvert(lineItems[i]);
        diffArray.push_back(itemToConvert);
    }
    return diffArray;
}

CanvasController::~CanvasController(){

    delete socket;
    delete serializer;
    delete timer;
}