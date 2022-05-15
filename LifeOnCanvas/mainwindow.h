#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QScreen>
#include "mainscene.h"
#include "mainview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Коллекция имен стилей кисти, отсортированных в соответствии с Qt::PenStyle
    const QString pen_styles[6]= {"NoPen","SolidLine","DashLine",
                                  "DotLine","DashDotLine","DashDotDotLine"};
    // Коллекция имен стилей кисти, отсортированных в соответствии с Qt::BrushStyle
    const QString brush_styles[15] = {"NoBrush", "SolidPattern", "Dense1Pattern",
                                      "Dense2Pattern", "Dense3Pattern", "Dense4Pattern",
                                      "Dense5Pattern", "Dense6Pattern", "Dense7Pattern",
                                      "HorPattern", "VerPattern", "CrossPattern",
                                      "BDiagPattern", "FDiagPattern", "DiagCrossPattern"};

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionAbout_Me_triggered();     // Отображение информации “Обо мне”

    void on_actionAbout_QT_triggered();     // Отображение информации о Qt

    void on_actionLine_triggered();         // Установить для рисования прямой линии

    void on_actionRectangle_triggered();    // Установить для рисования прямоугольника

    void on_actionEllipse_triggered();      // Установить для рисования эллипса

    void on_actionPolygon_triggered();      // Установить для рисования полигонов

    void on_actionFree_triggered();         // Установить для рисования свободной кривой


    void on_actionEraser_triggered();       // Установить в режим ластика

    void on_actionCancel_triggered();       // Возврат к предыдущей операции


    void on_actionFont_triggered();         // Установка шрифта для рисования текста

    void on_actionLineWidth_triggered();    // Установите ширину линии кисти

    void on_actionLineColor_triggered();    // Установить цвет кисти

    void on_actionNoPen_triggered();        // Установите тип линии кисти на беспроводную полосу

    void on_actionSolidLine_triggered();    // Установите тип линии кисти на сплошную линию

    void on_actionDashLine_triggered();     // Установите тип линии кисти на пунктирную линию

    void on_actionDotLine_triggered();      // Установите тип линии кисти на точечную линию DotLine

    void on_actionDashDotLine_triggered();  // Установите тип линии кисти на пунктирную точечную линию DashDotLine

    void on_actionDashDotDotLine_triggered();// Пунктирная линия  DashDotDotLine

    void on_actionBrushColor_triggered(); // Установить цвет заливки

    void on_actionNoBrush_triggered();      // Установите для типа заливки значение без заливки

    void on_actionSolidPattern_triggered(); // Установите тип заливки на реальную заливку

    void on_actionDense1_triggered();      // Установите тип заливки плотным 1

    void on_actionDense2_triggered();      // Установите тип заливки плотным 2

    void on_actionDense3_triggered();       // Установите тип заливки плотным 3

    void on_actionDense4_triggered();       // Установите тип заливки плотным 4

    void on_actionDense5_triggered();       // Установите тип заливки плотным 5

    void on_actionDense6_triggered();       // Установите тип заливки плотным 6

    void on_actionDense7_triggered();       // Установите тип заливки плотным 7

    void on_actionHorizontal_triggered();   // Установите тип заливки на горизонтальный

    void on_actionVertical_triggered();    // Установите тип заливки на вертикальный

    void on_actionCross_triggered();        // Установите тип заливки на Пересечение

    void on_actionForward_triggered();      // Установите тип заполнения для переадресации диагностики

    void on_actionBackward_triggered();     //  Backward Diagnoal

    void on_actionDiagCross_triggered();    //Crossing Diagnoal

    void on_actionSave_As_triggered();     // Сохранить чертежную доску в виде рисунка

private:
    void init_action_groups();              // Инициализировать группировку кнопок действий
    void init_status_bar();               // Инициализировать нижнюю строку состояния
    void update_status_text();             // Обновите текстовую информацию в строке состояния

private:
    Ui::MainWindow *ui;

    // Использовать Graphics View Framework как чертежная архитектура
    MainScene *scene;   // QGraphicsScene Часть (сцена)
    MainView *view;     // QGraphicsView Часть (вид)
    QPen *pen;          // Основная щетка
    QBrush *brush;      // Основная кисть (кисть используется для заполнения внутренней области рисунка)

    // Сохраняйте соответствующую текстовую информацию в строке состояния в нижней части окна
    QLabel *status_text_pen_color;
    QLabel *status_text_pen_style;
    QLabel *status_text_pen_width;
    QLabel *status_text_brush_color;
    QLabel *status_text_brush_style;
};
#endif // MAINWINDOW_H
