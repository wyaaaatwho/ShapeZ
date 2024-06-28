#include "mainwindow.h"
#include "start_page.h"
#include "game_page.h"
#include "help_page.h"
#include "global.h"
#include "hub.h"
#include "belt.h"
#include "cutter.h"
#include "trash_bin.h"
#include "transformer.h"
#include <iostream>


Startpage::Startpage(QWidget* parent):QWidget(parent)
{
    resource_manager& vault = resource_manager::instance();
    //set start page
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    start_page_pic = vault.get_pic("start_page");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(start_page_pic));
    this->setPalette(palette);

    //set all buttons on this page

    start_button = new QPushButton(this);
    QPixmap start_button_icon = vault.get_pic("start_button");
    QPixmap start_button_on_icon = vault.get_pic("start_button_on");
    start_button->setIcon(QIcon(start_button_icon));
    start_button->setIconSize(start_button_icon.size());
    start_button->setFixedSize(start_button_icon.size());
    start_button->setGeometry((WINDOW_WIDTH-start_button_icon.width())/2, (WINDOW_HEIGHT-start_button_icon.height())/2, start_button_icon.width(), start_button_icon.height());

    connect(start_button, SIGNAL(clicked()), this, SLOT(emit changePage(1)));
    connect(start_button, SIGNAL(toggled()), this, SLOT(on_start_button()));
    connect(start_button, &QPushButton::clicked, this, &Startpage::new_game);

    //set border free
    start_button->setStyleSheet("QPushButton { border: none; }");
    auto *iconSwitcher = new IconSwitcher(start_button, start_button_icon, start_button_on_icon);
    start_button->installEventFilter(iconSwitcher);

    continue_button = new QPushButton("Continue", this);
    QPixmap continue_button_icon = vault.get_pic("continue_button");
    continue_button->setIcon(QIcon(continue_button_icon));
    continue_button->setGeometry(QRect(QPoint(WINDOW_WIDTH/2-100, ((WINDOW_HEIGHT-start_button_icon.height())/2)+160), QSize(200, 60)));
    continue_button->setStyleSheet("QPushButton {"
                                   "font-size: 20px;"
                                   "border: 2px solid black; border-radius: 10px; "      // border style
                                   "background-color: lightgray;" // background color
                                   "padding: 5px;"                // padding
                                   "qproperty-iconSize: 24px 24px;" // icon size
                                   "}"
                                   "QPushButton:hover {"
                                   "font-size: 20px;"
                                   "border: 2px solid blue;border-radius: 10px;"      // hover style
                                   " background-color: lightblue;" // hover background
                                   "}");
    connect(continue_button, &QPushButton::clicked, this,&Startpage::on_continue_button);

    exit_button = new QPushButton("Exit", this);
    QPixmap exit_button_icon = vault.get_pic("exit_button");
    exit_button->setIcon(QIcon(exit_button_icon));
    exit_button->setGeometry(QRect(QPoint(WINDOW_WIDTH/2-100, ((WINDOW_HEIGHT-start_button_icon.height())/2)+250), QSize(200, 60)));
    exit_button->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 10px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 10px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(exit_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    help_button = new QPushButton("Help", this);
    QPixmap help_button_icon = vault.get_pic("help_button");
    help_button->setIcon(QIcon(help_button_icon));
    help_button->setGeometry(QRect(QPoint(WINDOW_WIDTH/2-100, ((WINDOW_HEIGHT-start_button_icon.height())/2)+350), QSize(200, 60)));
    help_button->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 10px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 10px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(help_button, &QPushButton::clicked, [this]() { emit changePage(1); });


}

Startpage::~Startpage()
{
    delete start_button;
    delete continue_button;
    delete exit_button;
    delete help_button;
}

//draw the start page
void Startpage::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(), start_page_pic);
}


void Startpage::on_start_button()
{
    start_button->setIcon(QIcon(QPixmap(":/start_button.png")));
}

void Startpage::leave_start_button()
{
    start_button->setIcon(QIcon(QPixmap(":/start_button_on.png")));
}

void Startpage::new_game()
{
    if (MainWindow::currentGamePage != nullptr)
        delete MainWindow::currentGamePage;
    MainWindow::currentGamePage = new game_page();
    MainWindow::stacked_widget->addWidget(MainWindow::currentGamePage);
    connect(MainWindow::currentGamePage, &game_page::changePage, this, &Startpage::changePage);
    emit changePage(4);
}

void Startpage::load_map_from_file()
{

    QFile file("data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // read the map from the file
        for (int i = 0; i < WINDOW_HEIGHT/cube_size_1; ++i) {
            for (int j = 0; j < WINDOW_WIDTH/cube_size_1; ++j) {
                for (int k = 0; k < 4; ++k) {
                    in >> game_page::map[i][j][k];
                }
            }
        }

        //read game_level from the file
        in >> hub::game_level;
        in >> hub::size;

        //read coins from the file
        in >> hub::coins;
        in >> hub::coin_value;

        // read the upgrades from the file
        in >> belt::belt_speed;

        // read the miners from the file

        //read cutter from the file
        in >> cutter::cutter_speed;

        //read mine from the file
        in >> mine::upgraded;


        file.close();
        qDebug() << "Map read from data.txt.";
    } else {
        qDebug() << "Failed to read map.";
    }
}

void Startpage::on_continue_button()
{
    if (MainWindow::currentGamePage != nullptr)
        delete MainWindow::currentGamePage;

    load_map_from_file(); // load the map from the file



  //  load page
    for (int i = 0; i < WINDOW_HEIGHT / cube_size_1; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH / cube_size_1; j++)
        {
            if (game_page::map[i][j][0] == ITEM_BELT) {
                game_page::map[i][j][3] = 1;
                if (game_page::map[i][j][2] == DIR_DOWN)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_down"));
                else if (game_page::map[i][j][2] == DIR_UP)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_up"));
                else if (game_page::map[i][j][2] == DIR_LEFT)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_left"));
                else if (game_page::map[i][j][2] == DIR_RIGHT)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_right"));
                else if (game_page::map[i][j][2] == DIR_LEFT_UP)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_left_up"));
                else if (game_page::map[i][j][2] == DIR_LEFT_DOWN)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_left_down"));
                else if (game_page::map[i][j][2] == DIR_RIGHT_UP)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_right_up"));
                else if (game_page::map[i][j][2] == DIR_RIGHT_DOWN)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_right_down"));
                else if (game_page::map[i][j][2] == DIR_UP_LEFT)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_up_left"));
                else if (game_page::map[i][j][2] == DIR_UP_RIGHT)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_up_right"));
                else if (game_page::map[i][j][2] == DIR_DOWN_LEFT)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_down_left"));
                else if (game_page::map[i][j][2] == DIR_DOWN_RIGHT)
                    game_page::item_list[std::make_pair(i, j)] = new belt(i, j, game_page::map[i][j][2],
                                                                          game_page::map[i][j][1], 1,
                                                                          resource_manager::instance().get_pic(
                                                                                  "belt_down_right"));
            }
            else if (game_page::map[i][j][0] == ITEM_CUTTER && game_page::map[i][j][1] == 1)
            {
                cutter *new_cutter = new cutter(i*cube_size_1, j*cube_size_1, game_page::map[i][j][2], game_page::map[i][j][1],
                                                cutter::cutter_speed, QPixmap(":/cutter_up.png"));
                game_page::item_list[std::make_pair(i, j)] = new_cutter;

            }
            else if(game_page::map[i][j][0] == ITEM_TRASH_BIN)
            {
                trash_bin *new_trash_bin = new trash_bin(i*cube_size_1, j*cube_size_1, game_page::map[i][j][2], game_page::map[i][j][1], 1,
                                                         QPixmap(":/trash_bin_up.png"));
                game_page::item_list[std::make_pair(i, j)] = new_trash_bin;
            }
            else if (game_page::map[i][j][0] == ITEM_TRANSFORMER)
            {
                transformer *new_transformer = new transformer(i*cube_size_1, j*cube_size_1, game_page::map[i][j][2], game_page::map[i][j][1], 1,
                                                             QPixmap(":/transformer_up.png"));
                game_page::item_list[std::make_pair(i, j)] = new_transformer;
            }
             else if (game_page::map[i][j][0] == ITEM_MINERANDMINE)
            {
                miner *new_miner = new miner(i*cube_size_1, j*cube_size_1, game_page::map[i][j][2], game_page::map[i][j][1], 1,
                                             QPixmap(":/miner_up.png"));
                game_page::item_list[std::make_pair(i, j)] = new_miner;
            }
        }

        MainWindow::currentGamePage = new game_page(); //new game page
        MainWindow::stacked_widget->addWidget(MainWindow::currentGamePage);
        connect(MainWindow::currentGamePage, &game_page::changePage, this, &Startpage::changePage);
        emit changePage(4);
    }
}

