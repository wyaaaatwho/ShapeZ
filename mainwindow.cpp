#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(const QPixmap &pic,QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1080, 800);
    this->setWindowTitle("ShapeZ");

    QPalette palette;
    palette.setBrush(QPalette::Window, pic);
    this->setPalette(palette); // set background image in the window

}

MainWindow::~MainWindow()
{
    delete ui;

}
