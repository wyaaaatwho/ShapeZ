//
// Created by 26711 on 2024/6/10.
//

#include "game_page.h"
#include "global.h"
#include "belt.h"

void place_belt(QMouseEvent *event)
{
    //handle belt
    if(want_place_belt&&(event->buttons() & Qt::LeftButton)) // Check if left button is pressed
    {
        mouse_x=event->x();
        mouse_y=event->y();


        is_placing_belt=true;
        want_place_belt=false;


        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
    else if(is_placing_belt&&(event->buttons() & Qt::LeftButton))//Check if left button is pressed
    {
        int current_x = event->x();
        int current_y = event->y();

        int current_i = current_y / cube_size_1;
        int current_j = current_x / cube_size_1;

        int prev_i = mouse_y / cube_size_1;
        int prev_j = mouse_x / cube_size_1;

        if (current_i != prev_i || current_j != prev_j)
        {
            if (current_i >= 0 && current_i < 10 && current_j >= 0 && current_j < 18)
            {
                if (map[current_i][current_j][0] == 0&&map[prev_i][prev_j][0]==ITEM_BELT)
                {
                    map[current_i][current_j][0] = ITEM_BELT;
                    map[current_i][current_j][3] = 0;
                    if(map[prev_i][prev_j][2]!=0)//if the previous belt has a direction
                    {
                        if (current_i - 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_DOWN;
                            if (map[prev_i][prev_j][2] == DIR_LEFT)
                                map[prev_i][prev_j][2] = DIR_LEFT_DOWN;
                            else if (map[prev_i][prev_j][2] == DIR_RIGHT)
                                map[prev_i][prev_j][2] = DIR_RIGHT_DOWN;
                        }
                        else if (current_i + 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_UP;
                            if (map[prev_i][prev_j][2] == DIR_LEFT)
                                map[prev_i][prev_j][2] = DIR_LEFT_UP;
                            else if (map[prev_i][prev_j][2] == DIR_RIGHT)
                                map[prev_i][prev_j][2] = DIR_RIGHT_UP;
                        }
                        else if (current_i == prev_i && current_j - 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_RIGHT;
                            if (map[prev_i][prev_j][2] == DIR_UP)
                                map[prev_i][prev_j][2] = DIR_UP_RIGHT;
                            else if (map[prev_i][prev_j][2] == DIR_DOWN)
                                map[prev_i][prev_j][2] = DIR_DOWN_RIGHT;
                        }
                        else if (current_i == prev_i && current_j + 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_LEFT;
                            if (map[prev_i][prev_j][2] == DIR_UP)
                                map[prev_i][prev_j][2] = DIR_UP_LEFT;
                            else if (map[prev_i][prev_j][2] == DIR_DOWN)
                                map[prev_i][prev_j][2] = DIR_DOWN_LEFT;
                        }
                    }
                    else if(map[prev_i][prev_j][2]==0)//if the previous belt has no direction
                    {
                        if (current_i - 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_DOWN;
                            map[prev_i][prev_j][2] = DIR_DOWN;
                        }
                        else if (current_i + 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_UP;
                            map[prev_i][prev_j][2] = DIR_UP;
                        }
                        else if (current_i == prev_i && current_j - 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_RIGHT;
                            map[prev_i][prev_j][2] = DIR_RIGHT;
                        }
                        else if (current_i == prev_i && current_j + 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_LEFT;
                            map[prev_i][prev_j][2] = DIR_LEFT;
                        }
                    }
                }
                else if(map[current_i][current_j][0] == 0&&map[prev_i][prev_j][0]==0)// if the current position is empty and the previous position is empty
                {
                    map[current_i][current_j][0] = ITEM_BELT;
                    map[current_i][current_j][3] = 0;//set the current position to belt
                }
                else if(map[current_i][current_j][0] == ITEM_BELT) // if current has, call it back
                {
                    map[pre_item_i][pre_item_j][0]=0;
                    map[pre_item_i][pre_item_j][3]=0;
                }
            }
            mouse_x = current_x;
            mouse_y = current_y;
            pre_item_i = current_i;
            pre_item_j = current_j;
        }

        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
    else if(is_placing_belt&&!(event->buttons() & Qt::LeftButton))
    {
        is_placing_belt=false;

        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
}

void delete_belt(QMouseEvent *event)
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

void game_page::draw_belt(QPainter &painter)
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