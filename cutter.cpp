//
// Created by 26711 on 2024/6/22.
//

#include "cutter.h"

cutter::cutter(int i, int j, int direction, int level, int speed, QPixmap cutter_pic)
                    :item(i,j,direction,level,speed),cutter_pic(cutter_pic)
                    {
                        if(direction == DIR_UP)
                        {
                            out1_i = i;
                            out1_j = j;
                            out2_i = i;
                            out2_j = j+1;
                        }
                        else if(direction == DIR_RIGHT)
                        {
                            out1_i = i;
                            out1_j = j;
                            out2_i = i+1;
                            out2_j = j;
                        }
                        else if(direction == DIR_DOWN)
                        {
                            out1_i = i;
                            out1_j = j+1;
                            out2_i = i;
                            out2_j = j;
                        }
                        else if(direction == DIR_LEFT)
                        {
                            out1_i = i+1;
                            out1_j = j;
                            out2_i = i;
                            out2_j = j;
                        }

                        this->type =ITEM_CUTTER;
                    }

cutter::~cutter(){}

void cutter::draw_item(QPainter &painter)
{
    if(direction == DIR_UP)
    {
        cutter_pic = QPixmap("resource/cutter_up.png");
        painter.drawPixmap(j , i, cube_size_1*2, cube_size_1, cutter_pic);
    }
    else if(direction == DIR_RIGHT)
    {
        cutter_pic = QPixmap("resource/cutter_right.png");
        painter.drawPixmap(j , i, cube_size_1, cube_size_1*2, cutter_pic);
    }
    else if(direction == DIR_DOWN)
    {
        cutter_pic = QPixmap("resource/cutter_down.png");
        painter.drawPixmap(j , i, cube_size_1*2, cube_size_1, cutter_pic);
    }
    else if(direction == DIR_LEFT)
    {
        cutter_pic = QPixmap("resource/cutter_left.png");
        painter.drawPixmap(j , i, cube_size_1, cube_size_1*2, cutter_pic);
    }

}