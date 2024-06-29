//
// Created by 26711 on 2024/6/22.
//

#include "trash_bin.h"
#include "game_page.h"



trash_bin::trash_bin(int i, int j, int direction, int level, int speed, QPixmap trash_bin_pic)
                    :item(i,j,direction,level,speed),trash_bin_pic(trash_bin_pic)
                    {
                        this->type =ITEM_TRASH_BIN;
                        connect(&game_page::great_timer, &QTimer::timeout, this, &trash_bin::move_cargo);

                        cargo_in = nullptr;
                        cargo_out = nullptr;
                    }

trash_bin::~trash_bin()
{
    if(cargo_in!=nullptr)
    {
        game_page::cargo_list.remove(cargo_in->key);
        delete cargo_in;
    }
    cargo_out = nullptr;
}

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

void trash_bin::move_cargo()
{
    if(cargo_in != nullptr)
    {
        game_page::cargo_list.remove(cargo_in->key);
        delete cargo_in;
        cargo_in = nullptr;
    }
}