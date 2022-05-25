#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
 
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Life on Canvas");   // Установить заголовок окна
    w.show();
    return a.exec();
}
