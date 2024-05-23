//
// Created by 26711 on 2024/5/23.
//
//all resources are managed here
#include "resource_manager.h"

resource_manager::resource_manager()
{
    my_resources["game_background"]=QPixmap(path+"game_background.png");
    if (my_resources["game_background"].isNull()) {
        qDebug() << "Failed to load image";
    }
}

resource_manager::~resource_manager()
{
    my_resources.clear(); //delete all resources and hash map
}

QPixmap resource_manager::get_pic(QString pic_name)
{
    return my_resources[pic_name];
}