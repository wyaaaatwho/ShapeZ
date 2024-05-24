#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, resource_manager &vault): QMainWindow(parent), ui(new Ui::MainWindow), resource_manager(vault)
{
    ui->setupUi(this);
    this->resize(1080, 800);
    this->setWindowTitle("ShapeZ");
    start_page = new start_page(resource_manager, this);
    this->setCentralWidget(start_page);
    start_page->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}



