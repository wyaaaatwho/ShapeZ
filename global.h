//
// Created by 26711 on 2024/5/23.
//
//all header files are included here
//all macro are defined here

#ifndef SHAPEZ_GLOBAL_H
#define SHAPEZ_GLOBAL_H


#define window_width_1 1440
#define window_height_1 800
#define cube_size 80
#define started 1
#define stopped 0
#define paused 2
#define game_over 3

#include <QHash>
#include <QPixmap>

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

private:
    resource_manager();
    resource_manager(const resource_manager&) = delete;
    resource_manager& operator=(const resource_manager&) = delete;
};


#endif //SHAPEZ_GLOBAL_H
