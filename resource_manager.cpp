//
// Created by 26711 on 2024/5/23.
//
//all resources are managed here
#include "resource_manager.h"

resource_manager::resource_manager()
{
    my_resources["start_page"]=QPixmap(path+"start_page.png");
    my_resources["game_background"]=QPixmap(path+"game_background.png");
    /*if (my_resources["game_background"].isNull()) {
        qDebug() << "Failed to load image";
    }*/
    my_resources["start_button"]=QPixmap(path+"start_button.png");
    my_resources["continue_button"]=QPixmap(path+"continue_button.png");
    my_resources["exit_button"]=QPixmap(path+"exit_button.png");
    my_resources["help_button"]=QPixmap(path+"help_button.png");
    my_resources["pause_button"]=QPixmap(path+"pause_button.png");
    my_resources["resume_button"]=QPixmap(path+"resume_button.png");

}

resource_manager::~resource_manager()
{
    my_resources.clear(); //delete all resources and hash map
}

QPixmap resource_manager::get_pic(QString pic_name)
{
    return my_resources[pic_name];
}