//
// Created by 26711 on 2024/6/10.
//

#include "game_page.h"
#include "global.h"
#include "belt.h"

belt::belt(int i,int j,int direction,int level,int speed,QPixmap belt_pix)
{
    this->type = ITEM_BELT;
    this->level = level;
    this->speed = speed;
    this->direction = direction;
    this->i = i;
    this->j = j;
    this->belt_pix = belt_pix;
    std::cout<<"belt created"<<std::endl;
}

belt::~belt()
{
    //delete this;
}



void belt::draw_item(QPainter &painter)
{
    painter.drawPixmap(j*cube_size_1,i*cube_size_1,cube_size_1,cube_size_1,belt_pix);
}