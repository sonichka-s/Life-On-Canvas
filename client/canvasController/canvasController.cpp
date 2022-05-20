
#include "canvasController.h"


CanvasController::CanvasController(QGraphicsScene* mainscene) {

    socket = new QTcpSocket(this);


}

void CanvasController::sendData() {

    socket->connectToHost("127.0.0.1", 8080);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));


}