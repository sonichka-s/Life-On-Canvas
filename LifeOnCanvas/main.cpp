#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"
// add to frontend
#include "canvasController.h"
//


int main(int argc, char *argv[])
{
 
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Life on Canvas");// Установить заголовок окна

    //add to frontend
    CanvasController controller(w.scene);
    w.scene->setController(&controller);
    controller.initCanvas();
    //

    w.show();
    return a.exec();
}
