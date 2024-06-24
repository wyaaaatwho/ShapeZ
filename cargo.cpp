//
// Created by 26711 on 2024/6/22.
//

#include "cargo.h"
#include "global.h"
#include "game_page.h"
#include "belt.h"
#include "hub.h"

QTimer cargo::move_timer;

int cargo::cargo_count = 0;

cargo::cargo(int x, int y, int type, int speed, int direction, int state,QPixmap& cargo_pic) : x(x), y(y), type(type), speed(speed), direction(direction), state(state), cargo_pic(cargo_pic)
{
    // Subtract half of the width and height from x and y to make them represent the center of the cargo
    this->x = x ;
    this->y = y ;

    connect(&move_timer, &QTimer::timeout, this, &cargo::detect);
    move_timer.start(16);
    i = this->y/cube_size_1; j = this->x/cube_size_1;
    x0 = this->x; y0 = this->y;
    cargo_count++;
    key = cargo_count;

    connect(this, &cargo::cargo_into_hub, game_page::item_list[std::make_pair(3,8)], &hub::cargo_get_in);
}

cargo::~cargo()
{

    //cargo_count--;
}

void cargo::detect()
{

    std::pair<int, int> key = std::make_pair(i, j);

    auto it = game_page::item_list.find(key);

    if(game_page::map[i][j][0]==ITEM_BELT&&game_page::map[i][j][3]==1&&game_page::item_list[key]->speed!=0
    &&(game_page::item_list[key]->cargo_in==nullptr||game_page::item_list[key]->cargo_in==this)) // move directly
    {
        state=CARGO_MOVING;
        speed = belt::belt_speed;
        if(direction!=game_page::map[i][j][2])
        {
            angle = 0; //change angle
            // renew x0 and y0
            x0 = x;
            y0 = y;
        }
        direction = game_page::map[i][j][2];

        game_page::item_list[key]->cargo_in = this;

    }
    else if(game_page::map[i][j][0]==ITEM_MINERANDMINE)  // start to move from a miner
    {
        speed = game_page::item_list[std::make_pair(i,j)]->speed;
        direction = game_page::item_list[std::make_pair(i,j)]->direction;
    }

    else if(game_page::map[i][j][0]==ITEM_TRASH_BIN)
    {
        auto it = game_page::cargo_list.find(this->key);
        if (it != game_page::cargo_list.end()) {
            game_page::cargo_list.erase(it);
        }
        delete this;
        return;  // ensure no further access to this object
    }

    else if(game_page::map[i][j][0]==ITEM_HUB)
    {
        emit cargo_into_hub(type);
        auto it = game_page::cargo_list.find(this->key);
        if (it != game_page::cargo_list.end()) {
            game_page::cargo_list.erase(it);
        }
        delete this;
        return;
    }

    else
    {
        state = CARGO_STOPPED;
    }


    if(state == CARGO_MOVING)
    {
        move();
    }
}

void cargo::move()
{
    if (direction ==DIR_UP) {
        y -= speed;
        i = y/cube_size_1;

    } else if (direction ==DIR_RIGHT) {
        x += speed;
        j = x/cube_size_1;

    } else if (direction ==DIR_DOWN) {
        y += speed;
        i = y/cube_size_1;

    } else if (direction == DIR_LEFT) {
        x -= speed;
        j = x/cube_size_1;

    }
    else{

        turn_speed = PI*speed/(2*cube_size_1);

        angle += turn_speed;

        switch (direction)
        {
            case DIR_UP_RIGHT:
                x  = x0 + (1- cos(angle))*(cube_size_1/2);
                y = y0 -sin(angle) *(cube_size_1/2);
                break;
            case DIR_DOWN_LEFT:
                x  = x0 - (1- cos(angle))*(cube_size_1/2);
                y = y0 +sin(angle) *(cube_size_1/2);
                break;
            case DIR_RIGHT_DOWN:
                x  = x0 +sin(angle) *(cube_size_1/2);
                y = y0 + (1- cos(angle))*(cube_size_1/2);
                break;
            case DIR_LEFT_UP:
                x  = x0 -sin(angle) *(cube_size_1/2);
                y = y0 - (1- cos(angle))*(cube_size_1/2);
                break;
            case DIR_UP_LEFT:
                x  = x0 - (1- cos(angle))*(cube_size_1/2);
                y = y0 -sin(angle) *(cube_size_1/2);
                break;
            case DIR_DOWN_RIGHT:
                x  = x0 + (1- cos(angle))*(cube_size_1/2);
                y = y0 +sin(angle) *(cube_size_1/2);
                break;
            case DIR_RIGHT_UP:
                x  = x0 +sin(angle) *(cube_size_1/2);
                y = y0 - (1- cos(angle))*(cube_size_1/2);
                break;
            case DIR_LEFT_DOWN:
                x  = x0 -sin(angle) *(cube_size_1/2);
                y = y0 + (1- cos(angle))*(cube_size_1/2);
                break;
        }

        // renew i and j
        i = y / cube_size_1;
        j = x / cube_size_1;

    }
}

void cargo::draw(QPainter &painter)
{
    painter.drawPixmap(x - CARGO_SIZE / 2, y - CARGO_SIZE / 2, CARGO_SIZE, CARGO_SIZE, cargo_pic);
}

