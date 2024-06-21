//
// Created by 26711 on 2024/6/14.
//

#include "mine.h"
#include "global.h"
#include "game_page.h"

mine::mine(QPixmap pic)
{
    mine_pic=pic;
    this->initialize_mine();
}

mine::~mine()
{

}

void mine::upgrade_mine()
{
    /*for (int i=0;i<window_width_1/cube_size_1;i++)
    {
        for (int j=0;j<window_height_1/cube_size_1;j++)
        {
            if (map[i][j][0]==ITEM_MINE)
            {
                if (map[i+1][j][0]!=ITEM_MINE)
                {
                    map[i+1][j][0]=ITEM_MINE;
                }
                if (map[i-1][j][0]!=ITEM_MINE)
                {
                    map[i-1][j][0]=ITEM_MINE;
                }
                if (map[i][j+1][0]!=ITEM_MINE)
                {
                    map[i][j+1][0]=ITEM_MINE;
                }
                if (map[i][j-1][0]!=ITEM_MINE)
                {
                    map[i][j-1][0]=ITEM_MINE;
                }
            }
        }
    }*/
}

void mine::initialize_mine()
{
    /*map[4][6][0]=ITEM_MINE;
    map[4][7][0]=ITEM_MINE;
    map[4][8][0]=ITEM_MINE;
    map[5][6][0]=ITEM_MINE;
    map[5][7][0]=ITEM_MINE;*/
}

void game_page::draw_mine(QPainter &painter)
{
    /*for (int i=0;i<window_width_1/cube_size_1;i++)
    {
        for (int j=0;j<window_height_1/cube_size_1;j++)
        {
            if (map[i][j][0]==ITEM_MINE)
            {
                painter.drawPixmap(i*cube_size_1,j*cube_size_1,cube_size_1,cube_size_1,resource_manager::instance().get_pic("mine_1"));
            }
        }
    }*/
}

// Created by 26711 on 2024/6/14.