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

}

resource_manager::~resource_manager()
{
    my_resources.clear(); //delete all resources and hash map
}

QPixmap resource_manager::get_pic(QString pic_name)
{
    return my_resources[pic_name];
}