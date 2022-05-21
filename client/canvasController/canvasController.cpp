
#include "canvasController.h"
#include <nlohmann/json.hpp>
#include <QJsonObject>

CanvasController::CanvasController(QGraphicsScene* mainScene_): CanvasId ( 0 ), mainScene( mainScene_){

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this, SIGNAL(receivedToRender(nlohmann::json)), this, SLOT(onReceivedMesage(nlohmann::json)));

    serializer = new Serializer();
}

unsigned int CanvasController::initCanvas() {

    socket->connectToHost(QHostAddress("127.0.0.1"), 8080);



}

unsigned int CanvasController::getCanvasById(int canvasID) {



}



void CanvasController::sendDiff() {



}


void CanvasController::onReadyRead(){


    const auto message = socket->readAll();
    nlohmann::json inJson = message;

    emit receivedToRender(inJson);

}

void CanvasController::onReceivedMesage(nlohmann::json inJson) {
    std::string type = inJson["Type"].get<std::string>();

   if (type == "Put") {
       serializer->parseCanvas(inJson.dump(), )
   } else if ( type == "Init" ) {

   }

}

void CanvasController::connected() {



}

void CanvasController::disconnected(){



}
void CanvasController::mousePressed(QMouseEvent *event){



}

CanvasController::~CanvasController(){
    delete socket;
    delete serializer;
}