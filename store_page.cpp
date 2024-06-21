//
// Created by 26711 on 2024/6/2.
//

#include "store_page.h"
#include "global.h"
#include "game_page.h"


store_page::store_page(QWidget *parent):QWidget(parent)
{
    resource_manager& vault = resource_manager::instance();
    //set store page
    this->setFixedSize(window_width_1, window_height_1);
    store_page_pic = vault.get_pic("back");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(store_page_pic));
    this->setPalette(palette);

    back_button = new QPushButton("Back", this);
    back_button = new QPushButton("Back", this);
    back_button->setIcon(vault.get_pic("back_button"));
    back_button->setGeometry(QRect(QPoint(0,0), QSize(80, 80)));
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
    connect(back_button, &QPushButton::clicked, [this](){emit changePage(1);});

    expand_map = new QPushButton("Expand Map", this);
    expand_map->setIcon(vault.get_pic("expand_map"));
    expand_map->setGeometry(QRect(QPoint(window_width_1/2-700, (window_height_1/2)-100), QSize(200, 200)));
    expand_map->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 20px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 20px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(expand_map, SIGNAL(clicked()), this, SLOT(handle_expand_map()));

    clear_barriers = new QPushButton("Clear Barriers", this);
    clear_barriers->setIcon(vault.get_pic("clear_barriers"));
    clear_barriers->setGeometry(QRect(QPoint(window_width_1/2-400, (window_height_1/2)-100), QSize(200, 200)));
    clear_barriers->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 20px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 20px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(clear_barriers, SIGNAL(clicked()), this, SLOT(handle_clear_barriers()));

    increase_mine = new QPushButton("Increase Mine", this);
    increase_mine->setIcon(vault.get_pic("increase_mine"));
    increase_mine->setGeometry(QRect(QPoint(window_width_1/2-100, (window_height_1/2)-100), QSize(200, 200)));
    increase_mine->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 20px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 20px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(increase_mine, SIGNAL(clicked()), this, SLOT(handle_increase_mine()));

    hub_big = new QPushButton("Bigger Hub", this);
    hub_big->setIcon(vault.get_pic("hub_big"));
    hub_big->setGeometry(QRect(QPoint(window_width_1/2+200, (window_height_1/2-100)), QSize(200, 200)));
    hub_big->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 20px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 20px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(hub_big, SIGNAL(clicked()), this, SLOT(handle_hub_big()));

    money = new QPushButton("More Money", this);
    money->setIcon(vault.get_pic("money"));
    money->setGeometry(QRect(QPoint(window_width_1/2+500, (window_height_1/2)-100), QSize(200, 200)));
    money->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 20px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 20px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(money, SIGNAL(clicked()), this, SLOT(handle_money()));

}

store_page::~store_page()
{
    /*if(back_button != nullptr) {
        delete back_button;
        back_button = nullptr;
    }
    if(expand_map != nullptr) {
        delete expand_map;
        expand_map = nullptr;
    }
    if(clear_barriers != nullptr) {
        delete clear_barriers;
        clear_barriers = nullptr;
    }
    if(increase_mine != nullptr) {
        delete increase_mine;
        increase_mine = nullptr;
    }
    if(hub_big != nullptr) {
        delete hub_big;
        hub_big = nullptr;
    }
    if(money != nullptr) {
        delete money;
        money = nullptr;
    }
*/
}

void store_page::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, store_page_pic);
}

