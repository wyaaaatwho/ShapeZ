//
// Created by 26711 on 2024/6/21.
//

#include "miner.h"
#include "item.h"
#include "global.h"
#include "cargo.h"
#include <QObject>

QTimer *miner::timer;

miner::miner(int i, int j, int direction, int level, int speed, QPixmap miner_pic) : item(i, j, direction, level, speed), miner_pic(miner_pic)
{
        this->type=ITEM_MINER;
        start_mining = false;

        timer = new QTimer(reinterpret_cast<QObject *>(this));
        connect(timer, &QTimer::timeout, this, &miner::generate_cargo);

        interval = 3/speed*1000;
        timer->start(interval);

        cargo_in = nullptr;
        cargo_out = nullptr;

}

miner::~miner()
{
}

void miner::draw_item(QPainter &painter)
{
    if(direction == DIR_UP)
    {
        miner_pic = QPixmap("resource/miner_up.png");
    }
    else if(direction == DIR_RIGHT)
    {
        miner_pic = QPixmap("resource/miner_right.png");
    }
    else if(direction == DIR_DOWN)
    {
        miner_pic = QPixmap("resource/miner_down.png");
    }
    else if(direction == DIR_LEFT)
    {
        miner_pic = QPixmap("resource/miner_left.png");
    }
    painter.drawPixmap(j , i, cube_size_1, cube_size_1, miner_pic);
}

void miner::start_mining_slot()
{
    start_mining = true;
    std::cout<<"start mining"<<std::endl; // "start mining"
}
void miner::stop_mining_slot()
{
    start_mining = false;
    std::cout<<"stop mining"<<std::endl; // "stop mining"
}

void miner:: generate_cargo()
{
    if(start_mining)
    {
        QPixmap pic;
        int cargo_type = 0;
        //set the cargo's pic
        if(game_page::mine_list[std::make_pair(i/cube_size_1,j/cube_size_1)]->mine_name == "circle") // "circle"
        {
            pic = QPixmap("resource/circle.png");
            cargo_type= CIRCLE;
        }
        else
        {
            pic = QPixmap("resource/square.png");// "resource/square.png"
            cargo_type = SQUARE;
        }

        cargo* new_cargo = new cargo(j,i,cargo_type,speed,direction,CARGO_MOVING,pic);

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

        game_page::cargo_list[cargo::cargo_count] = new_cargo;
    }
}