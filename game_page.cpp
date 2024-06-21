//
// Created by 26711 on 2024/5/29.
//

#include "game_page.h"
#include "help_page.h"
#include "start_page.h"
#include "global.h"
#include "belt.h"
#include "mine.h"
#include "item.h"

#include <iostream>


QMap<std::pair<int,int>, item*> game_page::item_list;
bool game_page::is_placing_belt = false;
bool game_page::want_place_belt = false;

int game_page::map[16][24][4] = {0};


game_page::game_page(QWidget *parent):QWidget(parent)
{

    resource_manager& vault = resource_manager::instance();
    setFixedSize(window_width_1,window_height_1);
    setWindowTitle("Shapez");
    game_background=vault.get_pic("game_background");

    setMouseTracking(true); // start tracking mouse

    timer = new QTimer(reinterpret_cast<QObject *>(this));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&game_page::update));
    timer->start(16); // 60 fps

    // Initialize the mine
    //mine  mine_1(vault.instance().get_pic("mine_1"));


    /*store_button=new QPushButton(this);
    store_button->setGeometry(0,0,100,50);
    store_button->setIcon(vault.get_pic("store_button"));
    store_button->setIconSize(QSize(100,50));
    store_button->setFlat(true);
    help_button=new QPushButton(this);
    help_button->setGeometry(0,50,100,50);
    help_button->setIcon(vault.get_pic("help_button"));
    help_button->setIconSize(QSize(100,50));
    help_button->setFlat(true);
    cutter=new QPushButton(this);
    cutter->setGeometry(0,100,100,50);
    cutter->setIcon(vault.get_pic("cutter"));
    cutter->setIconSize(QSize(100,50));
    cutter->setFlat(true);
    miner=new QPushButton(this);
    miner->setGeometry(0,150,100,50);
    miner->setIcon(vault.get_pic("miner"));
    miner->setIconSize(QSize(100,50));
    miner->setFlat(true);
    rope=new QPushButton(this);
    rope->setGeometry(0,200,100,50);
    rope->setIcon(vault.get_pic("rope"));
    rope->setIconSize(QSize(100,50));
    rope->setFlat(true);
    trash_bin=new QPushButton(this);
    trash_bin->setGeometry(0,250,100,50);
    trash_bin->setIcon(vault.get_pic("trash_bin"));
    trash_bin->setIconSize(QSize(100,50));
    trash_bin->setFlat(true);*/

    back_button = new QPushButton("Back", this);
    back_button->setGeometry(QRect(QPoint(0,0), QSize(80, 80)));
    back_button->setIcon(vault.get_pic("back_button"));
    back_button->setStyleSheet(("QPushButton {"
                                "font-size: 16px;"
                                "border: 2px solid black; border-radius: 10px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 16px;"
                                "border: 2px solid blue;border-radius: 10px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(back_button, &QPushButton::clicked, [this]() { emit changePage(0); });

    store_button = new QPushButton("Store", this);
    store_button->setGeometry(QRect(QPoint(0,80), QSize(80, 80)));
    store_button->setIcon(vault.get_pic("store_button"));
    store_button->setStyleSheet(("QPushButton {"
                                 "font-size: 16px;"
                                 "border: 2px solid black; border-radius: 10px; "      // border style
                                 "background-color: lightgray;" // background color
                                 "padding: 5px;"                // padding
                                 "qproperty-iconSize: 24px 24px;" // icon size
                                 "}"
                                 "QPushButton:hover {"
                                 "font-size: 16px;"
                                 "border: 2px solid blue;border-radius: 10px;"      // hover style
                                 " background-color: lightblue;" // hover background
                                 "}"));
    connect(store_button, &QPushButton::clicked, [this]() { emit changePage(3); });

    belt_button = new QPushButton(this);
    belt_button->setGeometry(QRect(QPoint(window_width_1/2-160,window_height_1-80), QSize(80, 80)));
    belt_button->setIcon(vault.get_pic("belt_button"));
    belt_button->setStyleSheet(("QPushButton {"
                                 "font-size: 16px;"
                                 "border: 2px solid black; border-radius: 10px; "      // border style
                                 "background-color: lightgray;" // background color
                                 "padding: 5px;"                // padding
                                 "qproperty-iconSize: 60px 60px;" // icon size
                                 "}"
                                 "QPushButton:hover {"
                                "font-size: 16px;"
                                "border: 2px solid blue;border-radius: 10px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(belt_button, &QPushButton::clicked, this, &game_page::handle_belt);




}

game_page::~game_page()
{
    /*if (store_button != nullptr) {
        delete store_button;
        store_button = nullptr;
    }
    if (back_button != nullptr) {
        delete back_button;
        back_button = nullptr;
    }
    if (cutter != nullptr) {
        delete cutter;
        cutter = nullptr;
    }
    if (miner != nullptr) {
        delete miner;
        miner = nullptr;
    }
    if (rope != nullptr) {
        delete rope;
        rope = nullptr;
    }
    if (trash_bin != nullptr) {
        delete trash_bin;
        trash_bin = nullptr;
    }*/


}

void game_page::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(), game_background);
    for (auto i : item_list)
    {
        i->draw_item(painter); // draw every item
    }
    //update();
}


void game_page::handle_belt()
{
    want_place_belt=true;
    std::cout<<"want_place_belt:"<<want_place_belt<<std::endl;
}

void game_page::mouseMoveEvent(QMouseEvent *event)
{
    mouse_x = event->x();
    mouse_y = event->y();

    //handle belt
    if(want_place_belt&&(event->buttons() & Qt::LeftButton)) // Check if left button is pressed
    {
        mouse_x=event->x();
        mouse_y=event->y();

        is_placing_belt=true;
        want_place_belt=false;

        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
    else if(is_placing_belt&&(event->buttons() & Qt::LeftButton))//Check if left button is pressed
    {
        int current_x = event->x();
        int current_y = event->y();

        int current_i = current_y / cube_size_1;
        int current_j = current_x / cube_size_1;

        int prev_i = mouse_y / cube_size_1;
        int prev_j = mouse_x / cube_size_1;

        if (current_i != prev_i || current_j != prev_j)
        {
            if (map[current_i][current_j][0] == 0 && map[prev_i][prev_j][0] == ITEM_BELT)
            {
                map[current_i][current_j][0] = ITEM_BELT;
                map[current_i][current_j][3] = 0;
                if (map[prev_i][prev_j][2] != 0)//if the previous belt has a direction
                {
                    if (current_i - 1 == prev_i && current_j == prev_j) {
                        map[current_i][current_j][2] = DIR_DOWN;
                        if (map[prev_i][prev_j][2] == DIR_LEFT)
                            map[prev_i][prev_j][2] = DIR_LEFT_DOWN;
                        else if (map[prev_i][prev_j][2] == DIR_RIGHT)
                            map[prev_i][prev_j][2] = DIR_RIGHT_DOWN;
                    } else if (current_i + 1 == prev_i && current_j == prev_j) {
                        map[current_i][current_j][2] = DIR_UP;
                        if (map[prev_i][prev_j][2] == DIR_LEFT)
                            map[prev_i][prev_j][2] = DIR_LEFT_UP;
                        else if (map[prev_i][prev_j][2] == DIR_RIGHT)
                            map[prev_i][prev_j][2] = DIR_RIGHT_UP;
                    } else if (current_i == prev_i && current_j - 1 == prev_j) {
                        map[current_i][current_j][2] = DIR_RIGHT;
                        if (map[prev_i][prev_j][2] == DIR_UP)
                            map[prev_i][prev_j][2] = DIR_UP_RIGHT;
                        else if (map[prev_i][prev_j][2] == DIR_DOWN)
                            map[prev_i][prev_j][2] = DIR_DOWN_RIGHT;
                    } else if (current_i == prev_i && current_j + 1 == prev_j) {
                        map[current_i][current_j][2] = DIR_LEFT;
                        if (map[prev_i][prev_j][2] == DIR_UP)
                            map[prev_i][prev_j][2] = DIR_UP_LEFT;
                        else if (map[prev_i][prev_j][2] == DIR_DOWN)
                            map[prev_i][prev_j][2] = DIR_DOWN_LEFT;
                    }
                }
                else if (map[prev_i][prev_j][2] == 0)//if the previous belt has no direction
                {
                    if (current_i - 1 == prev_i && current_j == prev_j) {
                        map[current_i][current_j][2] = DIR_DOWN;
                        map[prev_i][prev_j][2] = DIR_DOWN;
                    } else if (current_i + 1 == prev_i && current_j == prev_j) {
                        map[current_i][current_j][2] = DIR_UP;
                        map[prev_i][prev_j][2] = DIR_UP;
                    } else if (current_i == prev_i && current_j - 1 == prev_j) {
                        map[current_i][current_j][2] = DIR_RIGHT;
                        map[prev_i][prev_j][2] = DIR_RIGHT;
                    } else if (current_i == prev_i && current_j + 1 == prev_j) {
                        map[current_i][current_j][2] = DIR_LEFT;
                        map[prev_i][prev_j][2] = DIR_LEFT;
                    }

                }
                belt *newBelt = new belt(current_i, current_j, map[current_i][current_j][2], 1, 1,
                                         resource_manager::instance().get_pic("belt_blue"));
                qDebug() << "Constructed new belt at (" << current_i << ", " << current_j << ")";
                item_list[std::make_pair(current_i, current_j)] = newBelt;
                item_count++;
                item_list[std::make_pair(prev_i, prev_j)]->direction = map[prev_i][prev_j][2];
            }
            else if (map[current_i][current_j][0] == 0 && map[prev_i][prev_j][0] ==0)// if the current position is empty and the previous position is empty
            {
                map[current_i][current_j][0] = ITEM_BELT;
                map[current_i][current_j][3] = 0;

                belt *newBelt = new belt(current_i, current_j, map[current_i][current_j][2], 1, 1,
                                         resource_manager::instance().get_pic("belt_blue"));
                qDebug() << "Constructed new belt at (" << current_i << ", " << current_j << ")";
                item_list[std::make_pair(current_i, current_j)] = newBelt;
                item_count++;
            }
            else if (map[current_i][current_j][0] == ITEM_BELT) // if current has, call it back
            {
                map[pre_item_i][pre_item_j][0] = 0;
                map[pre_item_i][pre_item_j][3] = 0;
                item_list.remove(std::make_pair(pre_item_i, pre_item_j));
            }
        }
        mouse_x = current_x;
        mouse_y = current_y;
        pre_item_i = current_i;
        pre_item_j = current_j;
    }
    else if(is_placing_belt&&!(event->buttons() & Qt::LeftButton))
    {
        is_placing_belt=false;

        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;

    }
    update();

 }

void game_page::mousePressEvent(QMouseEvent *event)
{
    mouse_x = event->x();
    mouse_y = event->y();
    int i = mouse_y / cube_size_1;
    int j = mouse_x / cube_size_1;
    if(event->buttons() &Qt::RightButton)
    {
        delete item_list[std::make_pair(i, j)];
        item_list.remove(std::make_pair(i, j));
        map[i][j][0] = 0;
        map[i][j][1] = 0;
        map[i][j][2] = 0;
        map[i][j][3] = 0;
    }
    update();
}


