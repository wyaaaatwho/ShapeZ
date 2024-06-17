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

    stacked_widget = new QStackedWidget(this);
    stacked_widget->setGeometry(0, 0, window_width_1, window_height_1);

    Startpage *startPage = new Startpage(this);
    stacked_widget->addWidget(startPage);
    game_page *gamePage = new game_page(this);
    stacked_widget->addWidget(gamePage);
    help_page *helpPage = new help_page(this);
    stacked_widget->addWidget(helpPage);
    store_page *storePage = new store_page(this);
    stacked_widget->addWidget(storePage);

    stacked_widget->setCurrentIndex(0);

    connect(startPage, &Startpage::changePage, this, &MainWindow::setPage);
    connect(gamePage, &game_page::changePage, this, &MainWindow::setPage);
    connect(helpPage, &help_page::changePage, this, &MainWindow::setPage);
    connect(storePage, &store_page::changePage, this, &MainWindow::setPage);



}

MainWindow::~MainWindow()
{
    delete ui;

}