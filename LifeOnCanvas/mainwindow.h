#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
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

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionAbout_Me_triggered();     // Отображение информации “Обо мне”

    void on_actionAbout_QT_triggered();     // Отображение информации о Qt

    void on_actionLine_triggered();         // Установить для рисования прямой линии

    void on_actionRectangle_triggered();    // Установить для рисования прямоугольника

    void on_actionEllipse_triggered();      // Установить для рисования эллипса

    void on_actionFree_triggered();         // Установить для рисования свободной кривой

    void on_actionEraser_triggered();       // Установить в режим ластика

    void on_actionCancel_triggered();       // Возврат к предыдущей операции

    void on_actionLineWidth_triggered();    // Установите ширину линии кисти

    void on_actionLineColor_triggered();    // Установить цвет кисти

    void on_actionNoPen_triggered();        // Установить тип линии кисти на беспроводную полосу

    void on_actionSolidLine_triggered();    // Установить тип линии кисти на сплошную линию

    void on_actionDashLine_triggered();     // Установить тип линии кисти на пунктирную линию

    void on_actionDotLine_triggered();      // Установить тип линии кисти на точечную линию DotLine

    void on_actionDashDotLine_triggered();  // Установить тип линии кисти на пунктирную точечную линию DashDotLine

    void on_actionDashDotDotLine_triggered();// Пунктирная линия  DashDotDotLine

private:
    void init_action_groups();              // Инициализировать группировку кнопок действий
    void init_status_bar();               // Инициализировать нижнюю строку состояния
    void update_status_text();             // Обновить текстовую информацию в строке состояния

private:
    Ui::MainWindow *ui;

    // Использовать Graphics View Framework как чертежная архитектура
    MainScene *scene;   // QGraphicsScene Часть (сцена)
    MainView *view;     // QGraphicsView Часть (вид)
    QPen *pen;          // Основная кисть
    QBrush *brush;      // Основная кисть (кисть используется для заполнения внутренней области рисунка)

    // Сохранить соответствующую текстовую информацию в строке состояния в нижней части окна
    QLabel *status_text_pen_color;
    QLabel *status_text_pen_style;
    QLabel *status_text_pen_width;
};
#endif // MAINWINDOW_H
