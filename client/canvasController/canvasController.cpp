#include <iostream>

#include "canvasController.h"

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <QTimer>


CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QWebSocket(nullptr);
    timer = new QTimer(this);


    //connect network signals
    //connect(socket, SIGNAL(readyRead()),
      //      this, SLOT(onReadyRead()));

    connect(socket, SIGNAL(textMessageReceived(const QString &)),
                           this, SLOT(onResponseReceived(const QString & )));

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
    socket->open(QUrl("ws://192.168.1.10:8080"));

//    boost::asio::io_context ioc;
//
//    WebSocketSession* ws = new WebSocketSession(ioc);


//
//    if(socket->bytesToWrite()){
//
//        this->setTimer(timer);
//
//        qDebug() << "Connected!";
//    } else {
//
//        qDebug() << "Not connected!";
//    }

}

void CanvasController::setTimer(QTimer* timer) {

    timer->start(100);
}

void CanvasController::sendDiff(const std::vector<GraphicsItem> &diffArr) {

    std::string stringToSend = Serializer::serializeDiff(diffArr, CanvasId);

    QString qToSend = QString::fromUtf8(stringToSend.c_str());
//    std::string toSend = qToSend.toStdString();
    QByteArray data = qToSend.toUtf8();

    socket->sendTextMessage(qToSend);

    const char* bytes = data.constData();
    int bytesWritten = 0;
//    while (bytesWritten < data.size()) {
//        bytesWritten += socket->write(bytes + bytesWritten);
//    }

//    if (!socket->waitForReadyRead()){
//
//        qDebug() << "connection is lost";
//    }
}

void CanvasController::sendRegularRequest() {

    nlohmann::json jsonToSend;
    jsonToSend["Type"] = "Get";
    jsonToSend["CanvasId"] = CanvasId;

    QString toSend = QString::fromUtf8(jsonToSend.dump().c_str());

//   socket->write(toSend.toUtf8());
//
//   if (!socket->waitForReadyRead()){
//        qDebug() << "connection is lost";
//   }
}

void CanvasController::onReadyRead(){

//    qDebug() << "Reading: " << socket->bytesAvailable();
//
//    QByteArray response = socket->readAll();
//    QString responseStr = QString(response);
//
//    emit responseReceived(responseStr);
}

void CanvasController:: onResponseReceived(const QString &responseStr) {

    std::string responseToParse = responseStr.toStdString();

    CanvasId = Serializer::parseId(responseToParse);

    std::vector<GraphicsItem> itemsToDisplay;
    Serializer::parseDiff(responseToParse, itemsToDisplay);

    displayItems(itemsToDisplay);


}

void CanvasController::onMousePressedFreeCurve(){

    currentFreeLineItems.clear();
}

void CanvasController::onMouseMovedFreeCurve(QGraphicsLineItem *lineItem){

    currentFreeLineItems.push_back(lineItem);
}

void CanvasController::onMouseReleasedFreeCurve(){
    std::vector<GraphicsItem> diff = convertQLineItems(currentFreeLineItems);
    sendDiff(diff);
}


void CanvasController::onMouseReleasedSingleLine(QGraphicsLineItem* lineItem){
    GraphicsItem itemToSend(lineItem);
    std::vector<GraphicsItem> diff {itemToSend};
    sendDiff(diff);
}


void CanvasController::onMouseReleasedEllipse(QGraphicsEllipseItem* ellipseItem){
    GraphicsItem itemToSend(ellipseItem);
    std::vector<GraphicsItem> diff {itemToSend};
    sendDiff(diff);
}


void CanvasController::onMouseReleasedRectangle(QGraphicsRectItem* rectItem){
    GraphicsItem itemToSend(rectItem);
    std::vector<GraphicsItem> diff {itemToSend};
    sendDiff(diff);
}

void CanvasController::displayItems(const std::vector<GraphicsItem> &itemsToDisplay) {
    for (auto graphicsItem: itemsToDisplay){
        if (graphicsItem.itemType == 'L'){
            QGraphicsLineItem *lineItem = new QGraphicsLineItem();
            lineItem->setLine(graphicsItem.x1, graphicsItem.y1,
                              graphicsItem.x2, graphicsItem.y2);

            QColor color(graphicsItem.color.r, graphicsItem.color.g, graphicsItem.color.b, graphicsItem.color.a);
            QPen pen;
            pen.setColor(color);
            pen.setWidth(graphicsItem.width);
            lineItem->setPen(pen);

           // mainScene->addItemToVector(lineItem);
            mainScene->addItem(lineItem);
        } else if (graphicsItem.itemType == 'E'){
            QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
            ellipseItem->setRect(graphicsItem.x1, graphicsItem.y1,
                                 graphicsItem.x2 - graphicsItem.x1, graphicsItem.y2 - graphicsItem.y1);

            QColor color(graphicsItem.color.r, graphicsItem.color.g, graphicsItem.color.b, graphicsItem.color.a);
            QPen pen;
            pen.setColor(color);
            pen.setWidth(graphicsItem.width);
            ellipseItem->setPen(pen);

            // mainScene->addItemToVector(lineItem);
            mainScene->addItem(ellipseItem);
        } else if (graphicsItem.itemType == 'R'){
            QGraphicsRectItem* rectItem = new QGraphicsRectItem();
            rectItem->setRect(graphicsItem.x1, graphicsItem.y1,
                              graphicsItem.x2 - graphicsItem.x1, graphicsItem.y2 - graphicsItem.y1);

            QColor color(graphicsItem.color.r, graphicsItem.color.g, graphicsItem.color.b, graphicsItem.color.a);
            QPen pen;
            pen.setColor(color);
            pen.setWidth(graphicsItem.width);
            rectItem->setPen(pen);

            // mainScene->addItemToVector(lineItem);
            mainScene->addItem(rectItem);
        }
    }
}

std::vector<GraphicsItem> CanvasController::convertQLineItems(const QVector<QGraphicsLineItem *> &lineItems) {

    std::vector<GraphicsItem> diffArray;
    for (auto lineItem : lineItems) {
        GraphicsItem itemToConvert(lineItem);
        diffArray.push_back(itemToConvert);
    }
    return diffArray;
}

CanvasController::~CanvasController(){

    delete socket;
    delete timer;
}