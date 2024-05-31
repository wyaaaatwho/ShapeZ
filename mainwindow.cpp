#include "global.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "start_page.h"
#include "game_page.h"



MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(window_width_1, window_height_1);
    this->setWindowTitle("ShapeZ");



    auto start_page = new Startpage(this);
    this->setCentralWidget(start_page);
    start_page->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}



