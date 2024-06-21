//
// Created by 26711 on 2024/5/23.
//
//all header files are included here
//all macro are defined here

#ifndef SHAPEZ_GLOBAL_H
#define SHAPEZ_GLOBAL_H


#define window_width_1 1440
#define window_height_1 800
#define cube_size_1 80
#define stopped 0
#define started 1
#define paused 2
#define game_over 3
#define DIR_UP    1
#define DIR_LEFT  2
#define DIR_DOWN  3
#define DIR_RIGHT 4
#define DIR_UP_LEFT    5
#define DIR_UP_RIGHT  6
#define DIR_DOWN_LEFT  7
#define DIR_DOWN_RIGHT 8
#define DIR_LEFT_UP 9
#define DIR_LEFT_DOWN 10
#define DIR_RIGHT_UP 11
#define DIR_RIGHT_DOWN 12


#define ITEM_BELT   1
#define ITEM_MINER  2
#define ITEM_BIN    3
#define ITEM_CUTTER 4
#define ITEM_HUB 5
#define ITEM_MINE 6
#include <QHash>
#include <QPixmap>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QStackedWidget>
#include "game_page.h"
#include "store_page.h"
#include "help_page.h"
#include "start_page.h"



class resource_manager
{
    private:
        QHash<QString, QPixmap> my_resources;
public:
    static resource_manager& instance()
    {
        static resource_manager _instance;
        return _instance;
    }
    ~resource_manager();
    QPixmap get_pic(QString pic_name);
    resource_manager();
    resource_manager(const resource_manager&) = delete;
    resource_manager& operator=(const resource_manager&) = delete;
};








#endif //SHAPEZ_GLOBAL_H
