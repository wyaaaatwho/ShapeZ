//
// Created by 26711 on 2024/5/23.
//
//all resources are managed here
#include "global.h"
#include <iostream>
#include <QHash>
#include <QPixmap>


resource_manager::resource_manager()
{
    my_resources["start_page"]=QPixmap("resource/start_page.png");
    my_resources["game_background"]=QPixmap("resource/game_background.png");
    my_resources["start_button"]=QPixmap("resource/start_button.png");
    my_resources["start_button_on"]=QPixmap("resource/start_button_on.png");
    my_resources["back_button"]=QPixmap("resource/back_button.png");
    my_resources["clear_barriers"]=QPixmap("resource/clear_barriers.png");
    my_resources["expand_map"]=QPixmap("resource/expand_map.png");
    my_resources["store_button"]=QPixmap("resource/store_button.png");
    my_resources["hub_big"]=QPixmap("resource/hub_big.png");
    my_resources["hub"]=QPixmap("resource/hub.png");
    my_resources["increase_mine"]=QPixmap("resource/increase_mine.png");
    my_resources["money"]=QPixmap("resource/money.png");
    my_resources["back"]=QPixmap("resource/back.png");
    my_resources["belt_button"]=QPixmap("resource/belt_button.png");
    my_resources["belt_right"]=QPixmap("resource/belt_right.png");
    my_resources["belt_left"]=QPixmap("resource/belt_left.png");
    my_resources["belt_up"]=QPixmap("resource/belt_up.png");
    my_resources["belt_down"]=QPixmap("resource/belt_down.png");
    my_resources["belt_up_left"]=QPixmap("resource/belt_up_left.png");
    my_resources["belt_up_right"]=QPixmap("resource/belt_up_right.png");
    my_resources["belt_down_left"]=QPixmap("resource/belt_down_left.png");
    my_resources["belt_down_right"]=QPixmap("resource/belt_down_right.png");
    my_resources["belt_left_up"]=QPixmap("resource/belt_left_up.png");
    my_resources["belt_left_down"]=QPixmap("resource/belt_left_down.png");
    my_resources["belt_right_up"]=QPixmap("resource/belt_right_up.png");
    my_resources["belt_right_down"]=QPixmap("resource/belt_right_down.png");
    my_resources["belt_blue"]=QPixmap("resource/belt_blue.png");
    my_resources["mine_1"]=QPixmap("resource/mine_1.png");


}

resource_manager::~resource_manager()
{
    my_resources.clear(); //delete all resources and hash map
}

QPixmap resource_manager::get_pic(QString pic_name)
{
    return my_resources[pic_name];
}