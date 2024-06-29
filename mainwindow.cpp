#include "global.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "start_page.h"
#include "game_page.h"
#include "win_page.h"

game_page *MainWindow::currentGamePage ;
QStackedWidget *MainWindow::stacked_widget;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setWindowTitle("ShapeZ");
    this->setWindowIcon(QIcon(QPixmap("resource/icon.png")));

    stacked_widget = new QStackedWidget(this);
    stacked_widget->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Startpage *startPage = new Startpage(this);
    stacked_widget->addWidget(startPage);

    help_page *helpPage = new help_page(this);
    stacked_widget->addWidget(helpPage);

    store_page *storePage = new store_page(this);
    stacked_widget->addWidget(storePage);

    win_page *winPage = new win_page(this);
    stacked_widget->addWidget(winPage);

    currentGamePage= new game_page(this);
    stacked_widget->addWidget(currentGamePage);


    //set the music

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(1.0);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("resource/music.mp3"));

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
    player->play();



    stacked_widget->setCurrentIndex(0);

    connect(startPage, &Startpage::changePage, this, &MainWindow::setPage);
    connect(currentGamePage, &game_page::changePage, this, &MainWindow::setPage);
    connect(helpPage, &help_page::changePage, this, &MainWindow::setPage);
    connect(storePage, &store_page::changePage, this, &MainWindow::setPage);
    connect(winPage, &win_page::changePage, this, &MainWindow::setPage);



}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::stop_time()
{
    game_page::great_timer.stop();
}

void MainWindow::start_time()
{
    game_page::great_timer.start();
}

