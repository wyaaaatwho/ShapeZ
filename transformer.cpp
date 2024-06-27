//
// Created by 26711 on 2024/6/25.
//

#include "transformer.h"
#include "game_page.h"
#include "global.h"
#include "cargo.h"

transformer::transformer(int i,int j,int direction,int level,int speed,QPixmap transformer_pic):item(i,j,direction,level,speed),transformer_pic(transformer_pic)
{
    this->type = ITEM_TRANSFORMER;
    connect(&game_page::great_timer, &QTimer::timeout, this, &transformer::move_cargo);

    cargo_in = nullptr;
    cargo_out = nullptr;

    if(direction == DIR_UP)
    {
        in_i = i/cube_size_1+1;
        in_j = j/cube_size_1;
        out_i = i/cube_size_1-1;
        out_j = j/cube_size_1;
    }
    else if(direction == DIR_DOWN)
    {
        in_i = i/cube_size_1-1;
        in_j = j/cube_size_1;
        out_i = i/cube_size_1+1;
        out_j = j/cube_size_1;
    }
    else if(direction == DIR_LEFT)
    {
        in_i = i/cube_size_1;
        in_j = j/cube_size_1+1;
        out_i = i/cube_size_1;
        out_j = j/cube_size_1-1;
    }
    else if(direction == DIR_RIGHT)
    {
        in_i = i/cube_size_1;
        in_j = j/cube_size_1 - 1;
        out_i = i/cube_size_1;
        out_j = j/cube_size_1 + 1;
    }
}


transformer::~transformer()
{
    if(cargo_in!=nullptr)
    {
        game_page::cargo_list.remove(cargo_in->key);
        delete cargo_in;
    }
    cargo_out = nullptr;
}

void transformer::draw_item(QPainter &painter)
{
    if(direction == DIR_UP)
    {
        transformer_pic = QPixmap("resource/transformer_up.png");
    }
    else if(direction == DIR_RIGHT)
    {
        transformer_pic = QPixmap("resource/transformer_right.png");
    }
    else if(direction == DIR_DOWN)
    {
        transformer_pic = QPixmap("resource/transformer_down.png");
    }
    else if(direction == DIR_LEFT)
    {
        transformer_pic = QPixmap("resource/transformer_left.png");
    }
    painter.drawPixmap(j , i, cube_size_1, cube_size_1, transformer_pic);
}

void transformer::move_cargo()
{
    if(cargo_in != nullptr&&cargo_out==nullptr)
    {
        QPixmap pic;
        if(cargo_in->type==CIRCLE)
        {
            pic = QPixmap("resource/square.png");// "resource/square.png"
            cargo *new_cargo = new cargo(j,i,SQUARE,cargo_in->speed,cargo_in->direction,cargo_in->state,pic);
            game_page::cargo_list[cargo::cargo_count] = new_cargo;
            game_page::cargo_list.remove(cargo_in->key);
            delete cargo_in;
            cargo_in = nullptr;
            cargo_in = new_cargo;
            cargo_out = cargo_in;
            if(direction == DIR_UP)
            {
                new_cargo->x+=40;
            }

            else if(direction == DIR_RIGHT)
            {
                new_cargo->x+=80;
                new_cargo->y+=40;
            }
            else if(direction == DIR_DOWN)
            {
                new_cargo->x+=40;
                new_cargo->y+=80;
            }
            else if(direction == DIR_LEFT)
            {

                new_cargo->y+=40;
            }
        }
        else if(cargo_in->type==SQUARE)
        {
            pic = QPixmap("resource/circle.png");// "resource/circle.png"
            cargo *new_cargo = new cargo(j,i,CIRCLE,cargo_in->speed,cargo_in->direction,cargo_in->state,pic);
            game_page::cargo_list[cargo::cargo_count] = new_cargo;
            game_page::cargo_list.remove(cargo_in->key);
            delete cargo_in;
            cargo_in = nullptr;
            cargo_in = new_cargo;
            cargo_out = cargo_in;
            if(direction == DIR_UP)
            {
                new_cargo->x+=40;
            }

            else if(direction == DIR_RIGHT)
            {
                new_cargo->x+=80;
                new_cargo->y+=40;
            }
            else if(direction == DIR_DOWN)
            {
                new_cargo->x+=40;
                new_cargo->y+=80;
            }
            else if(direction == DIR_LEFT)
            {
                new_cargo->y+=40;
            }
        }

    }

    if(cargo_out != nullptr)
    {
        if(game_page::map[out_i][out_j][0]==ITEM_BELT&&game_page::map[out_i][out_j][3]==1)
        {
            if(game_page::item_list[std::make_pair(out_i,out_j)]->cargo_in==nullptr
               &&(game_page::item_list[std::make_pair(out_i,out_j)]->in_i==this->i/cube_size_1
                  &&game_page::item_list[std::make_pair(out_i,out_j)]->in_j==this->j/cube_size_1))
            {
                game_page::item_list[std::make_pair(out_i,out_j)]->cargo_in = cargo_out;

                cargo_in->angle = 0;

                cargo_in =nullptr;
                cargo_out = nullptr;
            }
        }
    }
}