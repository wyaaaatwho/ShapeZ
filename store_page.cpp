//
// Created by 26711 on 2024/6/2.
//

#include "store_page.h"
#include "global.h"
#include "game_page.h"
#include "hub.h"


store_page::store_page(QWidget *parent):QWidget(parent)
{
    resource_manager& vault = resource_manager::instance();
    //set store page
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    store_page_pic = vault.get_pic("back");

    coin_icon = vault.get_pic("coin"); // coin icon
    coin_icon=vault.get_pic("coin_icon");
    coin_font = new QFont("Arial", 30);
    coin_font->setBold(true);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(store_page_pic));
    this->setPalette(palette);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){this->update();});
    timer->start(16); //use timer to update the page

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
    connect(back_button, &QPushButton::clicked, [this](){emit changePage(4);});

    // to increase the mine
    increase_mine = new QPushButton("Increase Mine", this);
    increase_mine->setIcon(vault.get_pic("increase_mine"));
    increase_mine->setGeometry(QRect(QPoint(WINDOW_WIDTH/2-600, (WINDOW_HEIGHT/2)-100), QSize(200, 200)));
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
    connect(increase_mine, &QPushButton::clicked, this, &store_page::handle_increase_mine);

    //to make the hub bigger
    hub_big = new QPushButton("Bigger Hub", this);
    hub_big->setIcon(vault.get_pic("hub_big"));
    hub_big->setGeometry(QRect(QPoint(WINDOW_WIDTH/2-100, (WINDOW_HEIGHT/2-100)), QSize(200, 200)));
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
    connect(hub_big,&QPushButton::clicked, this, &store_page::upgrade_hub);

    // to get more money
    money = new QPushButton("More Money", this);
    money->setIcon(vault.get_pic("money"));
    money->setGeometry(QRect(QPoint(WINDOW_WIDTH/2+400, (WINDOW_HEIGHT/2)-100), QSize(200, 200)));
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
    connect(money, &QPushButton::clicked, this,&store_page::handle_money);

}

store_page::~store_page()
{
    delete coin_font;

}

void store_page::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, store_page_pic);
    display_coin(painter);
}


void store_page::display_coin(QPainter &painter) // display the coin
{
    painter.drawPixmap(WINDOW_WIDTH-200, 20, 40, 40, coin_icon);
    QFont originalFont = painter.font();

    painter.setFont(*coin_font);

    painter.drawText(WINDOW_WIDTH - 140, 55, QString::number(hub::coins));

    painter.setFont(originalFont);
}

void store_page::handle_increase_mine() // increase the mine
{
    if(hub::coins >= 400&&mine::upgraded==0)
    {
        hub::coins -= 400;
        mine::upgraded += 1;


        if(game_page::map[3][3][0]!=0)
        {
            auto key = std::make_pair(3, 3);
            if(game_page::item_list.contains(key))
            {
                auto item = game_page::item_list[key];
                delete item;
                game_page::item_list.remove(key);
            }
        }
        game_page::map[3][3][0]=ITEM_MINE;

        if(game_page::map[3][4][0]!=0)
        {

            auto key = std::make_pair(3, 4);
            if(game_page::item_list.contains(key))
            {
                auto item = game_page::item_list[key];
                delete item;
                game_page::item_list.remove(key);
            }
        }game_page::map[3][4][0]=ITEM_MINE;

        if(game_page::map[4][3][0]!=0)
        {

            auto key = std::make_pair(4, 3);
            if(game_page::item_list.contains(key))
            {
                auto item = game_page::item_list[key];
                delete item;
                game_page::item_list.remove(key);
            }
        }game_page::map[4][3][0]=ITEM_MINE;

        if(game_page::map[4][4][0]!=0)
        {

            auto key = std::make_pair(4, 4);
            if(game_page::item_list.contains(key))
            {
                auto item = game_page::item_list[key];
                delete item;
                game_page::item_list.remove(key);
            }
        }game_page::map[4][4][0]=ITEM_MINE;

        mine *mine_11=new mine(resource_manager::instance().get_pic("mine_1"),"circle",3,3);
        game_page::mine_list[std::make_pair(3,3)]=mine_11;
        mine *mine_12=new mine(resource_manager::instance().get_pic("mine_2"),"square",3,4);
        game_page::mine_list[std::make_pair(3,4)]=mine_12;
        mine *mine_13=new mine(resource_manager::instance().get_pic("mine_2"),"square",4,3);
        game_page::mine_list[std::make_pair(4,3)]=mine_13;
        mine *mine_14=new mine(resource_manager::instance().get_pic("mine_1"),"circle",4,4);
        game_page::mine_list[std::make_pair(4,4)]=mine_14;

    }
}

void store_page::handle_money() // get more money
{
    if(hub::coins >= 400)
    {
        hub::coin_value += 10;
        hub::coins -= 400;

    }
}

void store_page::upgrade_hub()  // upgrade the hub
{
    if(hub::coins>=400&&hub::size==2)
    {
        delete game_page::item_list[std::make_pair(3, 8)];
        game_page::item_list.remove(std::make_pair(3, 8));

        hub::only_hub = nullptr;

        hub::size = 4;

        hub::only_hub= new hub(3, 7, 0, 2, 1, QPixmap("resource/hub_big.png"));

        for (int i = 3; i < 3 + hub::size; i++)
        {
            for (int j = 7; j<7 + hub::size; j++)
            {
                if (game_page::map[i][j][0] != 0&&game_page::map[i][j][0]!=ITEM_HUB)
                {
                    auto key = std::make_pair(i, j);
                    if (game_page::item_list.contains(key))
                    {
                        auto item = game_page::item_list[key];
                        delete item;
                        game_page::item_list.remove(key);
                    }
                }
                game_page::map[i][j][0] = ITEM_HUB;
                game_page::map[i][j][1] = 2;
                game_page::map[i][j][2] = 0;
            }
        }

        game_page::item_list[std::make_pair(3, 7)] = hub::only_hub;

        hub::coins-=400;


    }

}


