//
// Created by 26711 on 2024/6/28.
//

#include "win_page.h"
#include "store_page.h"
#include "global.h"
#include "game_page.h"
#include "hub.h"
#include "cutter.h"
#include "belt.h"

bool win_page::already_miner;
bool win_page::already_cutter;
bool win_page::already_belt;

win_page::~win_page()
{
    delete miner_button;
    delete cutter_button;
    delete belt_button;
}

win_page::win_page(QWidget *parent):QWidget(parent)
{
    resource_manager& vault = resource_manager::instance();
    //set win page
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    win_page_pic = vault.get_pic("win_page_pic");

    miner_button = new QPushButton("Speed Up Miner", this);
    miner_button->setIcon(QPixmap("resource/miner_button.png"));
    miner_button->setGeometry(QRect(QPoint(500,500), QSize(200, 100)));
    setStyleSheet(("QPushButton {"
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

    connect(miner_button, &QPushButton::clicked, this, &win_page::speed_up_miner);

    cutter_button = new QPushButton("Speed Up Cutter", this);
    cutter_button->setIcon(QPixmap("resource/cutter_button.png"));
    cutter_button->setGeometry(QRect(QPoint(800,500), QSize(200, 100)));
    setStyleSheet(("QPushButton {"
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

    connect(cutter_button, &QPushButton::clicked, this, &win_page::speed_up_cutter);

    belt_button = new QPushButton("Speed Up Belt", this);
    belt_button->setIcon(QPixmap("resource/belt_button.png"));
    belt_button->setGeometry(QRect(QPoint(1100,500), QSize(200, 100)));
    setStyleSheet(("QPushButton {"
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

    connect(belt_button, &QPushButton::clicked, this, &win_page::speed_up_belt);

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
    connect(back_button, &QPushButton::clicked, [this](){emit changePage(0);});


    already_miner = false;
    already_cutter = false;
    already_belt = false;

}

void win_page::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, win_page_pic);

}

void win_page::speed_up_miner()
{
    if(!already_miner)
    {
        miner::interval /=2;
        already_miner = true;
        miner::miner_timer->start(miner::interval);
        emit changePage(4);
    }
}

void win_page::speed_up_cutter()
{
    if(!already_cutter)
    {
        cutter::interval /=2;
        already_cutter = true;
        cutter::cutter_timer.start(cutter::interval);
        emit changePage(4);
    }
}

void win_page::speed_up_belt()
{
    if(!already_belt)
    {
        belt::belt_speed *=2;
        already_belt = true;
        emit changePage(4);
    }
}


