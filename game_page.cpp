//
// Created by 26711 on 2024/5/29.
//

#include "game_page.h"
#include "help_page.h"
#include "start_page.h"
#include "global.h"
#include "belt.h"
#include "mine.h"
#include <iostream>



game_page::game_page(QWidget *parent):QWidget(parent)
{

    resource_manager& vault = resource_manager::instance();
    setFixedSize(window_width_1,window_height_1);
    setWindowTitle("Shapez");
    game_background=vault.get_pic("game_background");

    setMouseTracking(true); // start tracking mouse

    timer = new QTimer(reinterpret_cast<QObject *>(this));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&game_page::update));
    timer->start(16); // 每秒大约60帧，16ms刷新一次（1000ms / 60帧）

    // Initialize the mine
    mine  mine_1(vault.instance().get_pic("mine_1"));


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
    draw_belt(painter);
    draw_mine(painter);
}


void game_page::handle_belt()
{
    want_place_belt=true;
    std::cout<<"want_place_belt:"<<want_place_belt<<std::endl;
}

void game_page::mouseMoveEvent(QMouseEvent *event)
{
    place_belt(event);
    delete_belt(event);
    update();
}

void game_page::mousePressEvent(QMouseEvent *event)
{

    delete_belt(event);
    update();
}


