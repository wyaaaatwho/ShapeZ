//
// Created by 26711 on 2024/5/29.
//

#include "game_page.h"
#include "help_page.h"
#include "start_page.h"
#include "global.h"



game_page::game_page(QWidget *parent):QWidget(parent)
{

    resource_manager& vault = resource_manager::instance();
    setFixedSize(window_width_1,window_height_1);
    setWindowTitle("Shapez");
    game_background=vault.get_pic("game_background");

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
    back_button->setStyleSheet(("QPushButton {"
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
    connect(back_button, SIGNAL(clicked()), this, SLOT(handle_back_button()));


}

game_page::~game_page()
{
    delete store_button;
    delete help_button;
    delete back_button;
    delete cutter;
    delete miner;
    delete rope;
    delete trash_bin;
}

void game_page::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(), game_background);
}

void game_page::handle_back_button()
{
    auto * start = new Startpage(this->parentWidget());
    start->show();
    this->close();
}
