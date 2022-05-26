#include <iostream>

#include "canvasController.h"

#include <nlohmann/json.hpp>
#include <QTimer>



CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QTcpSocket(this);
    timer = new QTimer(this);


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

void CanvasController::sendDiff(const std::vector<GraphicsItem> &diffArr) {

    std::string stringToSend = Serializer::serializeDiff(diffArr, CanvasId);
    QString toSend = QString::fromUtf8(stringToSend.c_str());


    socket->write(toSend.toUtf8());

    if (!socket->waitForReadyRead()){

        qDebug() << "connection is lost";
    }
}

void CanvasController::sendRegularRequest() {

    nlohmann::json jsonToSend;
    jsonToSend["Type"] = "Get";
    jsonToSend["CanvasId"] = CanvasId;

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
            QPen pen;
            pen.color().setRed(graphicsItem.color.r);
            pen.color().setGreen(graphicsItem.color.g);
            pen.color().setBlue(graphicsItem.color.b);
            pen.color().setAlpha(graphicsItem.color.a);
            pen.setWidth(graphicsItem.width);
            lineItem->setPen(pen);

           // mainScene->addItemToVector(lineItem);
            mainScene->addItem(lineItem);
        } else if (graphicsItem.itemType == 'E'){
            QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
            ellipseItem->setRect(graphicsItem.x1, graphicsItem.y1,
                                 graphicsItem.x2, graphicsItem.y2);

            QPen pen;
            pen.color().setRed(graphicsItem.color.r);
            pen.color().setGreen(graphicsItem.color.g);
            pen.color().setBlue(graphicsItem.color.b);
            pen.color().setAlpha(graphicsItem.color.a);
            pen.setWidth(graphicsItem.width);
            ellipseItem->setPen(pen);

            // mainScene->addItemToVector(lineItem);
            mainScene->addItem(ellipseItem);
        } else if (graphicsItem.itemType == 'R'){
            QGraphicsRectItem* rectItem = new QGraphicsRectItem();
            rectItem->setRect(graphicsItem.x1, graphicsItem.y1,
                              graphicsItem.x2, graphicsItem.y2);
            QPen pen;
            pen.color().setRed(graphicsItem.color.r);
            pen.color().setGreen(graphicsItem.color.g);
            pen.color().setBlue(graphicsItem.color.b);
            pen.color().setAlpha(graphicsItem.color.a);
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