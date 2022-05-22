#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Окно, настройки видового экрана
    scene = new MainScene();
    view = new MainView(scene);
    
    /* Установить вид в качестве центрального элемента управления окна.
    Центральный элемент управления - это макет, то есть вид будет автоматически 
    изменять размер при изменении размера окна. */
    setCentralWidget(view);         
    view->setMinimumSize(630, 420); // Минимальный размер
    
    /* Когда сцена выходит за пределы поля зрения вида, 
    область отображения выравнивается по верхней левой области сцены */
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);   
    view->setRenderHint(QPainter::Antialiasing);
    
    /* Инициализировать размер окна, примечание: в дополнение к центральной области
    все окно также содержит такие области, как панель меню, панель инструментов
     и строка состояния. */
    this->resize(800, 600);     

   // Инициализация  кистей
    pen = new QPen();
    scene->setPen(pen);
    brush = new QBrush(*(new QColor("black")), Qt::NoBrush);
    scene->setBrush(brush);

    init_action_groups();
    init_status_bar();

   // Просто добавить начальный текст
    QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem();
    textItem->setText(QString("Life on Canvas"));
    textItem->setFont(QFont("Times", 12, QFont::Normal));
    textItem->setPos(QPoint(20, 20));
    textItem->setPen(*pen);
    textItem->setBrush(*(new QBrush(*(new QColor("black")), Qt::SolidPattern)));
    scene->addItem(textItem);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event); // Объявляем неиспользуемые переменные, чтобы избежать предупреждений компилятора
   /* Если сцена близка к размеру представления, будет активирована 
    полоса прокрутки. после попытки вычесть эти два числа она просто будет удалена. */
    scene->setSceneRect(0, 0, view->width()-2, view->height()-8);   
    scene->setRect(QRect(0, 0, view->width(), view->height()));   // Обновить прямоугольную область чертежа, которую необходимо обновить
}

void MainWindow::init_action_groups()
{
    // Группировка гарантирует, что в группе одновременно можно нажать только одну кнопку
    /*Все режимы рисования объединены в одну группу, режим по умолчанию 
    не установлен  */
    QActionGroup *typeGroup = new QActionGroup(this); 
    typeGroup->addAction(ui->actionLine);
    typeGroup->addAction(ui->actionRectangle);
    typeGroup->addAction(ui->actionEllipse);
    typeGroup->addAction(ui->actionPolygon);
    typeGroup->addAction(ui->actionFree);
    typeGroup->addAction(ui->actionEraser);

   /* Все типы линий кисти объединяются в одну группу, а 
    сплошная линия устанавливается в качестве типа линии по умолчанию */
    QActionGroup *lineStyleGroup = new QActionGroup(this);
    lineStyleGroup->addAction(ui->actionSolidLine);
    lineStyleGroup->addAction(ui->actionDashLine);
    lineStyleGroup->addAction(ui->actionDotLine);
    lineStyleGroup->addAction(ui->actionDashDotLine);
    lineStyleGroup->addAction(ui->actionDashDotDotLine);
    lineStyleGroup->addAction(ui->actionNoPen);
    ui->actionSolidLine->setChecked(true);
}

void MainWindow::init_status_bar()
{
    // Настройка текста и инициализация строки состояния под главным окном
    status_text_pen_color = new QLabel((QString)"Line Color: " + pen->color().name());
    status_text_pen_color->setMinimumWidth(150);
    ui->statusbar->addPermanentWidget(status_text_pen_color);

    status_text_pen_style = new QLabel((QString)"Style: " +
                                       pen_styles[QString::number(pen->style()).toInt()]);
    status_text_pen_style->setMinimumWidth(170);
    ui->statusbar->addPermanentWidget(status_text_pen_style);

    status_text_pen_width = new QLabel((QString)"Width: " +
                                       QString::number(pen->widthF()) + "px");
    status_text_pen_width->setMinimumWidth(120);
    ui->statusbar->addPermanentWidget(status_text_pen_width);

    status_text_brush_color = new QLabel((QString)"Brush Color: " + brush->color().name());
    status_text_brush_color->setMinimumWidth(150);
    ui->statusbar->addPermanentWidget(status_text_brush_color);

    status_text_brush_style = new QLabel((QString)"Style: " +
                                         brush_styles[QString::number(brush->style()).toInt()]);
    status_text_brush_style->setMinimumWidth(170);
    ui->statusbar->addPermanentWidget(status_text_brush_style);
}

void MainWindow::update_status_text()
{
    // Обновить строку строки состояния, информация строки состояния, связанная с каждой строкой, автоматически обновит содержимое
    status_text_pen_color->setText((QString)"Line Color: " + pen->color().name());
    status_text_pen_style->setText((QString)"Style: " +
                                    pen_styles[QString::number(pen->style()).toInt()]);
    status_text_pen_width->setText((QString)"Width: " +
                                    QString::number(pen->widthF()) + "px");
    status_text_brush_color->setText((QString)"Brush Color: " + brush->color().name());
    status_text_brush_style->setText((QString)"Style: " +
                                     brush_styles[QString::number(brush->style()).toInt()]);
}

void MainWindow::on_actionAbout_Me_triggered()
{
    QMessageBox::about(this, "About Me", QString("<h2>Life on Canvas</h2>")+
                                         "<p>Онлайн-доска для рисования<p>" +
                                         "<a href=\"https://github.com/IbragimDzaurov\">" +
                                         "https://github.com/IbragimDzaurov</a>"
                       );
}

void MainWindow::on_actionAbout_QT_triggered()
{
    QMessageBox::aboutQt(this, "About QT");
}

void MainWindow::on_actionLine_triggered()
{
   // Установить текущий режим рисования
    scene->setType(QString("Line"));
    // Обновить строку состояния
    update_status_text();
}

void MainWindow::on_actionRectangle_triggered()
{
    scene->setType(QString("Rectangle"));
    update_status_text();
}

void MainWindow::on_actionEllipse_triggered()
{
    scene->setType(QString("Ellipse"));
    update_status_text();
}

void MainWindow::on_actionPolygon_triggered()
{
    scene->setType(QString("Polygon"));
    update_status_text();
}

void MainWindow::on_actionFree_triggered()
{
    scene->setType(QString("Free"));
    update_status_text();
}



void MainWindow::on_actionEraser_triggered()
{
    scene->setType(QString("Eraser"));
    update_status_text();
}

void MainWindow::on_actionCancel_triggered()
{
    scene->deleteOne();
}



void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, scene->getFont(), this);
    if (ok) {
        scene->setFont(font);
    }
}

void MainWindow::on_actionLineWidth_triggered()
{
    bool ok;
    QString width_text = QInputDialog::getText(this,
                                               "Set Pen Width",
                                               "Enter Width (pixel): ",
                                               QLineEdit::Normal,
                                               QString::number(pen->widthF()),
                                               &ok);
    if(ok && !width_text.isEmpty())
    {
        pen->setWidthF(width_text.toDouble());
    }
    update_status_text();
}

void MainWindow::on_actionLineColor_triggered()
{
    QColor line_color = QColorDialog::getColor(pen->color(), this);
    if(line_color.isValid())
    {
        pen->setColor(line_color);
        update_status_text();
    }
}

void MainWindow::on_actionNoPen_triggered()
{
    pen->setStyle(Qt::NoPen);
    update_status_text();
}

void MainWindow::on_actionSolidLine_triggered()
{
    pen->setStyle(Qt::SolidLine);
    update_status_text();
}

void MainWindow::on_actionDashLine_triggered()
{
    pen->setStyle(Qt::DashLine);
    update_status_text();
}

void MainWindow::on_actionDotLine_triggered()
{
    pen->setStyle(Qt::DotLine);
    update_status_text();
}

void MainWindow::on_actionDashDotLine_triggered()
{
    pen->setStyle(Qt::DashDotLine);
    update_status_text();
}

void MainWindow::on_actionDashDotDotLine_triggered()
{
    pen->setStyle(Qt::DashDotDotLine);
    update_status_text();
}



void MainWindow::on_actionSave_As_triggered()
{
    QString file_path = QFileDialog::getSaveFileName(this,
                                                     "Save As",
                                                     "untitled.png",
                                                     "Images (*.png *.bmp *.jpg)");
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(view->winId()).save(file_path);
}
