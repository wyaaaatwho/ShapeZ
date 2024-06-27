//
// Created by 26711 on 2024/6/22.
//

#include "cutter.h"
QTimer cutter::cutter_timer;
int cutter::interval ;

cutter::cutter(int i, int j, int direction, int level, int speed, QPixmap cutter_pic)
                    :item(i,j,direction,level,speed),cutter_pic(cutter_pic)
                    {
                        if(direction == DIR_UP)
                        {
                            in_i = i+cube_size_1;
                            in_j = j;
                            out1_i = i-cube_size_1;
                            out1_j = j;
                            out2_i = i-cube_size_1;
                            out2_j = j+cube_size_1;

                            i_offset= i;
                            j_offset= j+cube_size_1;
                        }
                        else if(direction == DIR_RIGHT)
                        {
                            in_i = i;
                            in_j = j-cube_size_1;
                            out1_i = i;
                            out1_j = j+cube_size_1;
                            out2_i = i+cube_size_1;
                            out2_j = j+cube_size_1;

                            i_offset= i+cube_size_1;
                            j_offset= j;
                        }
                        else if(direction == DIR_DOWN)
                        {
                            in_i = i-cube_size_1;
                            in_j = j+cube_size_1;
                            out1_i = i+cube_size_1;
                            out1_j = j+cube_size_1;
                            out2_i = i+cube_size_1;
                            out2_j = j;

                            i_offset= i;
                            j_offset= j+cube_size_1;
                        }
                        else if(direction == DIR_LEFT)
                        {
                            in_i = i+cube_size_1;
                            in_j = j+cube_size_1;
                            out1_i = i+cube_size_1;
                            out1_j = j-cube_size_1;
                            out2_i = i;
                            out2_j = j-cube_size_1;

                            i_offset= i+cube_size_1;
                            j_offset = j;
                        }

                        this->type =ITEM_CUTTER;

                        cargo_in = nullptr;
                        cargo_out = nullptr;
                        cargo_out2=nullptr;

                        free_to_use = true;
                        out_1_ready = false;
                        out_2_ready = false;

                        connect(&cutter_timer, &QTimer::timeout, this, &cutter::move_cargo);
                        interval = 1/speed*1000;
                        cutter_timer.start(interval);

                        connect(&game_page::great_timer, &QTimer::timeout, this, &cutter::update_state);

                    }

cutter::~cutter()
{
    if(cargo_in!=nullptr)
    {
        game_page::cargo_list.remove(cargo_in->key);
        delete cargo_in;
    }
    if(cargo_out!=nullptr)
    {
        game_page::cargo_list.remove(cargo_out->key);
        delete cargo_out;
    }
    if(cargo_out2!=nullptr)
    {
        game_page::cargo_list.remove(cargo_out2->key);
        delete cargo_out2;
    }
    cargo_in=nullptr;
    cargo_out = nullptr;
    cargo_out2 = nullptr;
}

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

void cutter::move_cargo()
{
    if(cargo_in != nullptr)
    {
        game_page::cargo_list.remove(cargo_in->key);
        delete cargo_in;
        cargo_in = nullptr;
        // set the cutted cargo
        QPixmap pic1 = resource_manager::instance().get_pic("left_circle");
        QPixmap pic2 = resource_manager::instance().get_pic("right_circle");


        cargo_out = new cargo(out1_j, out1_i, LEFT_HALF_CIRCLE, 1, direction, CARGO_MOVING, pic1);
        game_page::cargo_list[cargo::cargo_count] = cargo_out;

        // set the cargo's position
        if(direction == DIR_UP)
        {
            cargo_out->x+=40;
            cargo_out->y+=80;
        }

        else if(direction == DIR_RIGHT)
        {
            cargo_out->y+=40;
        }
        else if(direction == DIR_DOWN)
        {
            cargo_out->x+=40;
        }
        else if(direction == DIR_LEFT)
        {
            cargo_out->x+=80;
            cargo_out->y+=40;
        }

        cargo_out2 = new cargo(out2_j, out2_i, RIGHT_HALF_CIRCLE, 1, direction, CARGO_MOVING, pic2);
        game_page::cargo_list[cargo::cargo_count] = cargo_out2;

        if(direction == DIR_UP)
        {
            cargo_out2->x+=40;
            cargo_out2->y+=80;
        }

        else if(direction == DIR_RIGHT)
        {
            cargo_out2->y+=40;
        }
        else if(direction == DIR_DOWN)
        {
            cargo_out2->x+=40;
        }
        else if(direction == DIR_LEFT)
        {
            cargo_out2->x+=80;
            cargo_out2->y+=40;
        }

        //free_to_use =false;
    }

    // check if out 1 ready
    if(cargo_out!=nullptr&&out_1_ready==false)
    {
        if(game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][0]==ITEM_TRASH_BIN&&
        game_page::item_list[std::make_pair(out1_i/cube_size_1,out1_j/cube_size_1)]->cargo_in == nullptr)
        {
            out_1_ready = true;
        }
        else if(game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][0]==ITEM_BELT
        &&game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][3]==1&&
        game_page::item_list[std::make_pair(out1_i/cube_size_1,out1_j/cube_size_1)]->cargo_in == nullptr)
        {
            if (direction == DIR_UP)
            {
                if(game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_UP||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_UP_RIGHT||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_UP_LEFT)
                {
                    out_1_ready = true;
                }
            }
            else if(direction == DIR_RIGHT)
            {
                if(game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_RIGHT||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_RIGHT_UP||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_RIGHT_DOWN)
                {
                    out_1_ready = true;
                }
            }
            else if(direction == DIR_DOWN)
            {
                if(game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_DOWN||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_DOWN_RIGHT||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_DOWN_LEFT)
                {
                    out_1_ready = true;
                }
            }
            else if(direction == DIR_LEFT)
            {
                if(game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_LEFT||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_LEFT_UP||
                game_page::map[out1_i/cube_size_1][out1_j/cube_size_1][2]==DIR_LEFT_UP)
                {
                    out_1_ready = true;
                }
            }
        }
    }
    //check if out2 ready
    if(cargo_out!=nullptr&&out_2_ready==false)
    {
        if(game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][0]==ITEM_TRASH_BIN&&
           game_page::item_list[std::make_pair(out2_i/cube_size_1,out2_j/cube_size_1)]->cargo_in == nullptr)
        {
            out_2_ready = true;
        }
        else if(game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][0]==ITEM_BELT&&
                game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][3]==1&&
        game_page::item_list[std::make_pair(out2_i/cube_size_1,out2_j/cube_size_1)]->cargo_in == nullptr)
        {
            if (direction == DIR_UP)
            {
                if(game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_UP||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_UP_RIGHT||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_UP_LEFT)
                {
                    out_2_ready = true;
                }
            }
            else if(direction == DIR_RIGHT)
            {
                if(game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_RIGHT||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_RIGHT_UP||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_RIGHT_DOWN)
                {
                    out_2_ready = true;
                }
            }
            else if(direction == DIR_DOWN)
            {
                if(game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_DOWN||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_DOWN_RIGHT||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_DOWN_LEFT)
                {
                    out_2_ready = true;
                }
            }
            else if(direction == DIR_LEFT)
            {
                if(game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_LEFT||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_LEFT_UP||
                   game_page::map[out2_i/cube_size_1][out2_j/cube_size_1][2]==DIR_LEFT_DOWN)
                {
                    out_2_ready = true;
                }
            }
        }
    }

    if(out_1_ready&&out_2_ready)
    {
        game_page::item_list[std::make_pair(out1_i/cube_size_1,out1_j/cube_size_1)]->cargo_in = cargo_out;
        game_page::item_list[std::make_pair(out2_i/cube_size_1,out2_j/cube_size_1)]->cargo_in = cargo_out2;

        cargo_out = nullptr;
        cargo_out2 = nullptr;
        //cargo_in = nullptr;

        out_1_ready = false;
        out_2_ready = false;
        //free_to_use = true;
    }
}

void cutter::update_state()
{
    if(cargo_in!=nullptr||cargo_out!=nullptr||cargo_out2!=nullptr)
    {
        free_to_use = false;
    }
    else
    {
        free_to_use = true;
    }
}