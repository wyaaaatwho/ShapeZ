//
// Created by 26711 on 2024/6/10.
//

#include "game_page.h"
#include "global.h"
#include "belt.h"

void belt::place_item(QMouseEvent *event)
{

}

void belt:: delete_item(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton)
    {
        int current_x = event->x();
        int current_y = event->y();

        int current_i = current_y / cube_size_1;
        int current_j = current_x / cube_size_1;

        if (current_i >= 0 && current_i < 10 && current_j >= 0 && current_j < 18)
        {
            if (map[current_i][current_j][0] == ITEM_BELT)
            {
                map[current_i][current_j][0] = 0;
                map[current_i][current_j][2] = 0;
                map[current_i][current_j][3] = 0;
            }
        }
    }
}

void belt::draw_item(QPainter &painter)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 18; j++)
        {
            if(map[i][j][0] == ITEM_BELT&&map[i][j][3]==0&&is_placing_belt)
            {
                painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_blue"));
            }
            if(map[i][j][0] == ITEM_BELT&&(map[i][j][3]==1||!is_placing_belt))
            {
                if(map[i][j][2] == DIR_UP)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_up"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_DOWN)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_down"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_LEFT)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_left"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_RIGHT)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_right"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_LEFT_UP)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_left_up"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_LEFT_DOWN)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_left_down"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_RIGHT_UP)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_right_up"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_RIGHT_DOWN)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_right_down"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_UP_LEFT)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_up_left"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_UP_RIGHT)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_up_right"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_DOWN_LEFT)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_down_left"));
                    map[i][j][3]=1;
                }
                else if(map[i][j][2] == DIR_DOWN_RIGHT)
                {
                    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_down_right"));
                    map[i][j][3]=1;
                }
            }
        }
    }
}