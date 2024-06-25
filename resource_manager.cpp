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
    my_resources["mine_2"]=QPixmap("resource/mine_2.png");
    my_resources["miner_button"]=QPixmap("resource/miner_button.png");
    my_resources["miner_up"]=QPixmap("resource/miner_up.png");
    my_resources["miner_down"]=QPixmap("resource/miner_down.png");
    my_resources["miner_left"]=QPixmap("resource/miner_left.png");
    my_resources["miner_right"]=QPixmap("resource/miner_right.png");
    my_resources["trash_bin_button"]=QPixmap("resource/trash_bin_button.png");
    my_resources["trash_bin_up"]=QPixmap("resource/trash_bin_up.png");
    my_resources["trash_bin_down"]=QPixmap("resource/trash_bin_down.png");
    my_resources["trash_bin_left"]=QPixmap("resource/trash_bin_left.png");
    my_resources["trash_bin_right"]=QPixmap("resource/trash_bin_right.png");
    my_resources["cutter_button"]=QPixmap("resource/cutter_button.png");
    my_resources["cutter_up"]=QPixmap("resource/cutter_up.png");
    my_resources["cutter_down"]=QPixmap("resource/cutter_down.png");
    my_resources["cutter_left"]=QPixmap("resource/cutter_left.png");
    my_resources["cutter_right"]=QPixmap("resource/cutter_right.png");

    my_resources["circle"]=QPixmap("resource/circle.png");
    my_resources["square"]=QPixmap("resource/square.png");
    my_resources["left_circle"]=QPixmap("resource/left_circle.png");
    my_resources["right_circle"]=QPixmap("resource/right_circle.png");

}

resource_manager::~resource_manager()
{
    my_resources.clear(); //delete all resources and hash map
}

QPixmap resource_manager::get_pic(QString pic_name)
{
    return my_resources[pic_name];
}