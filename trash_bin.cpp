//
// Created by 26711 on 2024/6/22.
//

#include "trash_bin.h"

trash_bin::trash_bin(int i, int j, int direction, int level, int speed, QPixmap trash_bin_pic)
                    :item(i,j,direction,level,speed),trash_bin_pic(trash_bin_pic)
                    {
                        this->type =ITEM_TRASH_BIN;
                    }

trash_bin::~trash_bin(){}

void trash_bin::draw_item(QPainter &painter)
{
    if(direction == DIR_UP)
    {
        trash_bin_pic = QPixmap("resource/trash_bin_up.png");
    }
    else if(direction == DIR_RIGHT)
    {
        trash_bin_pic = QPixmap("resource/trash_bin_right.png");
    }
    else if(direction == DIR_DOWN)
    {
        trash_bin_pic = QPixmap("resource/trash_bin_down.png");
    }
    else if(direction == DIR_LEFT)
    {
        trash_bin_pic = QPixmap("resource/trash_bin_left.png");
    }
    painter.drawPixmap(j , i, cube_size_1, cube_size_1, trash_bin_pic);
}