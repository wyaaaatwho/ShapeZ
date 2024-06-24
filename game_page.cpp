//
// Created by 26711 on 2024/5/29.
//

#include "game_page.h"
#include "help_page.h"
#include "start_page.h"
#include "global.h"
#include "belt.h"
#include "mine.h"
#include "miner.h"
#include "item.h"
#include "trash_bin.h"
#include "cutter.h"

#include <iostream>


QMap<std::pair<int,int>, item*> game_page::item_list;
QMap<std::pair<int,int>, mine*> game_page::mine_list;
QMap<int, cargo*> game_page::cargo_list;
bool game_page::is_placing_belt = false;
bool game_page::want_place_belt = false;
bool game_page::is_placing_miner = false;
bool game_page::is_placing_cutter = false;
bool game_page::is_placing_trash_bin = false;

int game_page::map[16][24][4] = {0};

item* game_page::item_to_place = nullptr;

game_page::game_page(QWidget *parent):QWidget(parent)
{

    resource_manager& vault = resource_manager::instance();
    setFixedSize(window_width_1,window_height_1);
    setWindowTitle("Shapez");
    game_background=vault.get_pic("game_background");

    setMouseTracking(true); // start tracking mouse

    timer = new QTimer(reinterpret_cast<QObject *>(this));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&game_page::update));
    connect(timer, &QTimer::timeout, this, &game_page::emit_signals);
    timer->start(16); // 60 fps

    // Initialize the mine
    set_mine();

    // initialize the buttons
    set_buttons();

    // initialize the hub

    set_hub();


}

game_page::~game_page()
{
    delete timer;
    timer = nullptr;
    delete back_button;
    back_button = nullptr;
    delete store_button;
    store_button = nullptr;
    delete belt_button;
    belt_button = nullptr;
    delete cutter_button;
    cutter_button = nullptr;
    delete miner_button;
    miner_button = nullptr;

    // Delete all items in item_list
    qDeleteAll(item_list);
    item_list.clear();

}

void game_page::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(), game_background);
    draw_mine(painter); //draw mine

    for (auto i : item_list)
    {
        if(i->type == ITEM_BELT)
        i->draw_item(painter); // draw every belt
    }
    for(auto i : cargo_list)
    {
        i->draw(painter);
    }
    for (auto i : item_list)
    {
        if(i->type != ITEM_BELT)
            i->draw_item(painter); // draw every other item
    }
    if(is_placing_belt) // draw blue belt
    {
        draw_belt_blue(painter);
    }
    if((is_placing_miner||is_placing_cutter||is_placing_trash_bin)&&item_to_place!=nullptr) // draw moving item
    {
        item_to_place->draw_item(painter);
    }
}

// button slots
void game_page::handle_belt()
{
    if(is_placing_miner==false&&is_placing_cutter==false&&is_placing_trash_bin==false&&is_placing_belt==false&&want_place_belt==false)
    want_place_belt=true;
    std::cout<<"want_place_belt:"<<want_place_belt<<std::endl;
}
void game_page::handle_miner()
{
    if(is_placing_miner==false&&is_placing_cutter==false&&is_placing_trash_bin==false&&is_placing_belt==false&&want_place_belt==false)
    is_placing_miner=true;
    std::cout<<"is_placing_miner:"<<is_placing_miner<<std::endl;
}
void game_page::handle_cutter()
{
    if(is_placing_miner==false&&is_placing_cutter==false&&is_placing_trash_bin==false&&is_placing_belt==false&&want_place_belt==false)
    is_placing_cutter=true;
    std::cout<<"is_placing_cutter:"<<is_placing_cutter<<std::endl;
}
void game_page::handle_trash_bin()
{
    if(is_placing_miner==false&&is_placing_cutter==false&&is_placing_trash_bin==false&&is_placing_belt==false&&want_place_belt==false)
    is_placing_trash_bin=true;
    std::cout<<"is_placing_trash_bin:"<<is_placing_trash_bin<<std::endl;
}

// emit signals to start to mine
void game_page::emit_signals()
{
    for(auto i:item_list)
    {
        if(i->type==ITEM_MINER)
        {
            miner *miner1 = dynamic_cast<miner*>(i);
            if(miner1->start_mining==false)
            {
                if(miner1->direction==DIR_UP&&map[miner1->i/ cube_size_1-1][miner1->j/ cube_size_1][0]==ITEM_BELT&&
                map[miner1->i/ cube_size_1-1][miner1->j/ cube_size_1][3]==1&&
                (map[miner1->i/ cube_size_1-1][miner1->j/ cube_size_1][2]==DIR_UP
                ||map[miner1->i/ cube_size_1-1][miner1->j/ cube_size_1][2]==DIR_UP_RIGHT||
                map[miner1->i/ cube_size_1-1][miner1->j/ cube_size_1][2]==DIR_UP_LEFT))
                {
                    miner1->start_mining_slot();
                }
                else if (miner1->direction==DIR_RIGHT&&map[miner1->i/ cube_size_1][miner1->j/ cube_size_1+1][0]==ITEM_BELT
                    &&map[miner1->i/ cube_size_1][miner1->j/ cube_size_1+1][3]==1
                &&(map[miner1->i/ cube_size_1][miner1->j/ cube_size_1+1][2]==DIR_RIGHT
                ||map[miner1->i/ cube_size_1][miner1->j/ cube_size_1+1][2]==DIR_RIGHT_UP
                ||map[miner1->i/ cube_size_1][miner1->j/ cube_size_1+1][2]==DIR_RIGHT_DOWN))
                {
                    miner1->start_mining_slot();
                }
                else if (miner1->direction==DIR_DOWN&&map[miner1->i/ cube_size_1+1][miner1->j/ cube_size_1][0]==ITEM_BELT
                &&map[miner1->i/ cube_size_1+1][miner1->j/ cube_size_1][3]==1
                &&(map[miner1->i/ cube_size_1+1][miner1->j/ cube_size_1][2]==DIR_DOWN
                ||map[miner1->i/ cube_size_1+1][miner1->j/ cube_size_1][2]==DIR_DOWN_RIGHT
                ||map[miner1->i/ cube_size_1+1][miner1->j/ cube_size_1][2]==DIR_DOWN_LEFT))
                {
                    miner1->start_mining_slot();
                }
                else if (miner1->direction==DIR_LEFT&&map[miner1->i/ cube_size_1][miner1->j/ cube_size_1-1][0]==ITEM_BELT
                &&map[miner1->i/ cube_size_1][miner1->j/ cube_size_1-1][3]==1
                &&(map[miner1->i/ cube_size_1][miner1->j/ cube_size_1-1][2]==DIR_LEFT
                ||map[miner1->i/ cube_size_1][miner1->j/ cube_size_1-1][2]==DIR_LEFT_DOWN
                ||map[miner1->i/ cube_size_1][miner1->j/ cube_size_1-1][2]==DIR_LEFT_UP))
                {
                    miner1->start_mining_slot();
                }
            }
            else
            {
                if(miner1->direction==DIR_UP&&map[miner1->i/ cube_size_1-1][miner1->j/ cube_size_1][0]!=ITEM_BELT)
                {
                    miner1->stop_mining_slot();
                }
                else if (miner1->direction==DIR_RIGHT&&map[miner1->i/ cube_size_1][miner1->j/ cube_size_1+1][0]!=ITEM_BELT)
                {
                    miner1->stop_mining_slot();
                }
                else if (miner1->direction==DIR_DOWN&&map[miner1->i/ cube_size_1+1][miner1->j/ cube_size_1][0]!=ITEM_BELT)
                {
                    miner1->stop_mining_slot();
                }
                else if (miner1->direction==DIR_LEFT&&map[miner1->i/ cube_size_1][miner1->j/ cube_size_1-1][0]!=ITEM_BELT)
                {
                    miner1->stop_mining_slot();
                }
            }
        }
    }
}

void game_page::mouseMoveEvent(QMouseEvent *event)
{
    //handle belt
    placeBelt(event);

    // TO PLACE ITEMS
    place_item(event);

    delete_item(event);

    update();

 }

void game_page::mousePressEvent(QMouseEvent *event)
{
    delete_item(event);
    set_item(event);
    update();
}

void game_page::keyPressEvent(QKeyEvent *event)
{

    if(is_placing_miner||is_placing_cutter||is_placing_trash_bin)
    rotate_item(event);

    update();
}

void game_page::delete_item(QMouseEvent *event)
{
    mouse_x = event->x();
    mouse_y = event->y();
    int i = mouse_y / cube_size_1;
    int j = mouse_x / cube_size_1;

    if((event->buttons() &Qt::RightButton)&&map[i][j][0]!=0&&map[i][j][0]!=ITEM_MINE&&map[i][j][0]!=ITEM_HUB&&map[i][j][0]!=ITEM_MINERANDMINE&&map[i][j][0]!=ITEM_CUTTER)
    {
        if(item_list[std::make_pair(i, j)]->cargo_in!=nullptr)
        {
            cargo_list.remove(item_list[std::make_pair(i, j)]->cargo_in->key);
        }
        delete item_list[std::make_pair(i, j)];
        item_list.remove(std::make_pair(i, j));
        map[i][j][0] = 0;
        map[i][j][1] = 0;
        map[i][j][2] = 0;
        map[i][j][3] = 0;
    }
    if((event->buttons() &Qt::RightButton)&&map[i][j][0]==ITEM_MINERANDMINE)
    {
        delete item_list[std::make_pair(i, j)];
        item_list.remove(std::make_pair(i, j));
        map[i][j][0] = ITEM_MINE;
        map[i][j][1] = 0;
        map[i][j][2] = 0;
        map[i][j][3] = 0;
    }
    // delete cutter
    if((event->buttons() &Qt::RightButton)&&map[i][j][0]==ITEM_CUTTER)
    {
        if (map[i][j][2]==DIR_DOWN||map[i][j][2]==DIR_UP)
        {

            if(item_list.contains(std::make_pair(i,j))&&item_list[std::make_pair(i,j)]->type==ITEM_CUTTER)
            {
                delete item_list[std::make_pair(i,j)];
                item_list.remove(std::make_pair(i,j));
                map[i][j][0]=0;
                map[i][j][1]=0;
                map[i][j][2]=0;
                map[i][j][3]=0;
                map[i][j+1][0]=0;
                map[i][j+1][1]=0;
                map[i][j+1][2]=0;
                map[i][j+1][3]=0;
            }
            else if(item_list.contains(std::make_pair(i,j-1))&&item_list[std::make_pair(i,j-1)]->type==ITEM_CUTTER)
            {
                delete item_list[std::make_pair(i,j-1)];
                item_list.remove(std::make_pair(i,j-1));
                map[i][j][0]=0;
                map[i][j][1]=0;
                map[i][j][2]=0;
                map[i][j][3]=0;
                map[i][j-1][0]=0;
                map[i][j-1][1]=0;
                map[i][j-1][2]=0;
                map[i][j-1][3]=0;

            }
        }
        else
        {
            if(item_list.contains(std::make_pair(i,j))&&item_list[std::make_pair(i,j)]->type==ITEM_CUTTER)
            {
                delete item_list[std::make_pair(i,j)];
                item_list.remove(std::make_pair(i,j));
                map[i][j][0]=0;
                map[i][j][1]=0;
                map[i][j][2]=0;
                map[i][j][3]=0;
                map[i+1][j][0]=0;
                map[i+1][j][1]=0;
                map[i+1][j][2]=0;
                map[i+1][j][3]=0;
            }
            else if(item_list.contains(std::make_pair(i-1,j))&&item_list[std::make_pair(i-1,j)]->type==ITEM_CUTTER)
            {
                delete item_list[std::make_pair(i-1,j)];
                item_list.remove(std::make_pair(i-1,j));
                map[i][j][0]=0;
                map[i][j][1]=0;
                map[i][j][2]=0;
                map[i][j][3]=0;
                map[i-1][j][0]=0;
                map[i-1][j][1]=0;
                map[i-1][j][2]=0;
                map[i-1][j][3]=0;
            }
        }
    }
}

void game_page::place_item(QMouseEvent *event)
{

    if(is_placing_miner&&item_to_place==nullptr)
    {
        item_to_place = new miner(mouse_x , mouse_y , DIR_UP, 1, 1, resource_manager::instance().get_pic("miner_up"));
    }
    if(is_placing_trash_bin&&item_to_place==nullptr)
    {
        item_to_place = new trash_bin(mouse_x , mouse_y , DIR_DOWN, 1, 1, resource_manager::instance().get_pic("trash_bin_up"));
    }
    if(is_placing_cutter&&item_to_place==nullptr)
    {
        item_to_place = new cutter(mouse_y , mouse_x , DIR_UP, 1, 1, resource_manager::instance().get_pic("cutter_up"));
    }
    if(item_to_place==nullptr)
        return;
    item_to_place->i = event->y()-cube_size_1/2;
    item_to_place->j = event->x()-cube_size_1/2;

}

void game_page::rotate_item(QKeyEvent *event)
{
    if(item_to_place==nullptr)
        return;
    if (event->key() == Qt::Key_W)
    {
        item_to_place->direction =DIR_UP;
    }
    if (event->key() == Qt::Key_D)
    {
        item_to_place->direction =DIR_RIGHT;
    }
    if (event->key() == Qt::Key_S)
    {
        item_to_place->direction =DIR_DOWN;
    }
    if (event->key() == Qt::Key_A)
    {
        item_to_place->direction =DIR_LEFT;
    }
}

void game_page::set_item(QMouseEvent *event)
{
    if(item_to_place==nullptr)
        return;
    //set miner
    if (is_placing_miner && (event->buttons() & Qt::LeftButton))
    {
        if(map[event->y()/ cube_size_1][event->x()/ cube_size_1][0]!=ITEM_MINE)
            return;
        miner * new_miner = new miner((event->y()/ cube_size_1)*cube_size_1, (event->x()/ cube_size_1)*cube_size_1, item_to_place->direction, item_to_place->level, item_to_place->speed, resource_manager::instance().get_pic("miner_up"));
        item_to_place = nullptr;
        item_list[std::make_pair(new_miner->i/ cube_size_1, new_miner->j/ cube_size_1)] = new_miner;
        is_placing_miner = false;
        map[new_miner->i/ cube_size_1][new_miner->j/ cube_size_1][0] = ITEM_MINERANDMINE;
        map[new_miner->i/ cube_size_1][new_miner->j/ cube_size_1][2] = new_miner->direction;
        map[new_miner->i/ cube_size_1][new_miner->j/ cube_size_1][1] = new_miner->level;
    }
    //set bin
    if(is_placing_trash_bin && (event->buttons() & Qt::LeftButton))
    {
        if(map[event->y()/ cube_size_1][event->x()/ cube_size_1][0]!=0)
            return;
        trash_bin * new_trash_bin = new trash_bin((event->y()/ cube_size_1)*cube_size_1, (event->x()/ cube_size_1)*cube_size_1, item_to_place->direction, item_to_place->level, item_to_place->speed, resource_manager::instance().get_pic("trash_bin_up"));
        item_to_place = nullptr;
        item_list[std::make_pair(new_trash_bin->i/ cube_size_1, new_trash_bin->j/ cube_size_1)] = new_trash_bin;
        is_placing_trash_bin = false;
        map[new_trash_bin->i/ cube_size_1][new_trash_bin->j/ cube_size_1][0] = ITEM_TRASH_BIN;
        map[new_trash_bin->i/ cube_size_1][new_trash_bin->j/ cube_size_1][2] = new_trash_bin->direction;
        map[new_trash_bin->i/ cube_size_1][new_trash_bin->j/ cube_size_1][1] = new_trash_bin->level;
    }
    // set cutter
    if(is_placing_cutter && (event->buttons() & Qt::LeftButton))
    {
        if(map[event->y()/ cube_size_1][event->x()/ cube_size_1][0]!=0
        ||((item_to_place->direction==DIR_UP||item_to_place->direction==DIR_DOWN)&&map[event->y()/ cube_size_1][event->x()/ cube_size_1+1][0]!=0)
        ||((item_to_place->direction==DIR_RIGHT||item_to_place->direction==DIR_LEFT)&&map[event->y()/ cube_size_1+1][event->x()/ cube_size_1][0]!=0))
            return;
        cutter * new_cutter = new cutter((event->y()/ cube_size_1)*cube_size_1, (event->x()/ cube_size_1)*cube_size_1, item_to_place->direction, item_to_place->level, item_to_place->speed, resource_manager::instance().get_pic("cutter_up"));
        item_to_place = nullptr;
        item_list[std::make_pair(new_cutter->i/ cube_size_1, new_cutter->j/ cube_size_1)] = new_cutter;
        is_placing_cutter = false;
        if(new_cutter->direction ==DIR_UP||new_cutter->direction==DIR_DOWN)
        {
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1][0] = ITEM_CUTTER;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1][2] = new_cutter->direction;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1][1] = new_cutter->level;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1+1][0] = ITEM_CUTTER;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1+1][2] =new_cutter->direction;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1+1][1] = new_cutter->level;
        }
        else if(new_cutter->direction==DIR_LEFT||new_cutter->direction==DIR_RIGHT)
        {
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1][0] = ITEM_CUTTER;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1][2] =new_cutter->direction;
            map[new_cutter->i/ cube_size_1][new_cutter->j/ cube_size_1][1] = new_cutter->level;
            map[new_cutter->i/ cube_size_1+1][new_cutter->j/ cube_size_1][0] = ITEM_CUTTER;
            map[new_cutter->i/ cube_size_1+1][new_cutter->j/ cube_size_1][2] =new_cutter->direction;
            map[new_cutter->i/ cube_size_1+1][new_cutter->j/ cube_size_1][1] = new_cutter->level;
        }
    }
}

void game_page::set_buttons()
{
    back_button = new QPushButton("Back", this);
    back_button->setGeometry(QRect(QPoint(0, 0), QSize(80, 80)));
    back_button->setIcon(QPixmap("resource/back_button.png"));
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
    store_button->setGeometry(QRect(QPoint(0, 80), QSize(80, 80)));
    store_button->setIcon(QPixmap("resource/store_button"));
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
    belt_button->setGeometry(QRect(QPoint(window_width_1 / 2 - 160, window_height_1 - 80), QSize(80, 80)));
    belt_button->setIcon(QPixmap("resource/belt_button"));
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

    cutter_button = new QPushButton(this);
    cutter_button->setGeometry(QRect(QPoint(window_width_1 / 2 - 80, window_height_1 - 80), QSize(80, 80)));
    cutter_button->setIcon(QPixmap("resource/cutter_button"));
    cutter_button->setStyleSheet(("QPushButton {"
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
    connect(cutter_button, &QPushButton::clicked, this, &game_page::handle_cutter);

    miner_button = new QPushButton(this);
    miner_button->setGeometry(QRect(QPoint(window_width_1 / 2, window_height_1 - 80), QSize(80, 80)));
    miner_button->setIcon(QPixmap("resource/miner_button"));
    miner_button->setStyleSheet(("QPushButton {"
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
    connect(miner_button, &QPushButton::clicked, this, &game_page::handle_miner);

    trash_bin_button = new QPushButton(this);
    trash_bin_button->setGeometry(QRect(QPoint(window_width_1 / 2 + 80, window_height_1 - 80), QSize(80, 80)));
    trash_bin_button->setIcon(QPixmap("resource/trash_bin_button.png"));
    trash_bin_button->setStyleSheet(("QPushButton {"
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
    connect(trash_bin_button, &QPushButton::clicked, this, &game_page::handle_trash_bin);


}

