//
// Created by 26711 on 2024/6/14.
//

#include "mine.h"
#include "global.h"
#include "game_page.h"

int mine::upgraded=0;

mine::mine(QPixmap pic,std::string name,int i,int j)
{
    mine_pic=pic;
    mine_name=name;
    this->i=i;
    this->j=j;
}

mine::~mine()
{

}

void mine::draw_mine(QPainter &painter)
{
    painter.drawPixmap(j*cube_size_1,i*cube_size_1,cube_size_1,cube_size_1,mine_pic);
}



void game_page::draw_mine(QPainter &painter)
{
    for (auto i : mine_list)
    {
        i->draw_mine(painter);
    }
}

void game_page::set_mine()
{
    //set mine 1
    if(map[6][2][0]!=ITEM_MINERANDMINE)
    map[6][2][0]=ITEM_MINE;
    if(map[6][3][0]!=ITEM_MINERANDMINE)
    map[6][3][0]=ITEM_MINE;
    if(map[7][2][0]!=ITEM_MINERANDMINE)
    map[7][2][0]=ITEM_MINE;
    if(map[7][3][0]!=ITEM_MINERANDMINE)
    map[7][3][0]=ITEM_MINE;
    if(map[7][4][0]!=ITEM_MINERANDMINE)
    map[7][4][0]=ITEM_MINE;
    mine *mine_1=new mine(resource_manager::instance().get_pic("mine_1"),"circle",6,2);
    mine_list[std::make_pair(6,2)]=mine_1;
    mine *mine_2=new mine(resource_manager::instance().get_pic("mine_1"),"circle",6,3);
    mine_list[std::make_pair(6,3)]=mine_2;
    mine *mine_3=new mine(resource_manager::instance().get_pic("mine_1"),"circle",7,2);
    mine_list[std::make_pair(7,2)]=mine_3;
    mine *mine_4=new mine(resource_manager::instance().get_pic("mine_1"),"circle",7,3);
    mine_list[std::make_pair(7,3)]=mine_4;
    mine *mine_5=new mine(resource_manager::instance().get_pic("mine_1"),"circle",7,4);
    mine_list[std::make_pair(7,4)]=mine_5;

    //set mine 2
    if(map[2][15][0]!=ITEM_MINERANDMINE)
    map[2][15][0]=ITEM_MINE;
    if(map[2][16][0]!=ITEM_MINERANDMINE)
    map[2][16][0]=ITEM_MINE;
    if(map[2][17][0]!=ITEM_MINERANDMINE)
    map[2][17][0]=ITEM_MINE;
    if(map[3][15][0]!=ITEM_MINERANDMINE)
    map[3][15][0]=ITEM_MINE;
    if(map[3][16][0]!=ITEM_MINERANDMINE)
    map[3][16][0]=ITEM_MINE;
    mine *mine_6=new mine(resource_manager::instance().get_pic("mine_2"),"square",2,15);
    mine_list[std::make_pair(2,15)]=mine_6;
    mine *mine_7=new mine(resource_manager::instance().get_pic("mine_2"),"square",2,16);
    mine_list[std::make_pair(2,16)]=mine_7;
    mine *mine_8=new mine(resource_manager::instance().get_pic("mine_2"),"square",2,17);
    mine_list[std::make_pair(2,17)]=mine_8;
    mine *mine_9=new mine(resource_manager::instance().get_pic("mine_2"),"square",3,15);
    mine_list[std::make_pair(3,15)]=mine_9;
    mine *mine_10=new mine(resource_manager::instance().get_pic("mine_2"),"square",3,16);
    mine_list[std::make_pair(3,16)]=mine_10;

    if(mine::upgraded==1) //upgrade mine when loading
    {
        if(map[3][3][0]!=ITEM_MINERANDMINE)
        map[3][3][0]=ITEM_MINE;
        if(map[3][4][0]!=ITEM_MINERANDMINE)
        map[3][4][0]=ITEM_MINE;
        if(map[4][3][0]!=ITEM_MINERANDMINE)
        map[4][3][0]=ITEM_MINE;
        if(map[4][4][0]!=ITEM_MINERANDMINE)
        map[4][3][0]=ITEM_MINE;

        mine *mine_11=new mine(resource_manager::instance().get_pic("mine_1"),"circle",3,3);
        mine_list[std::make_pair(3,3)]=mine_11;
        mine *mine_12=new mine(resource_manager::instance().get_pic("mine_2"),"square",3,4);
        mine_list[std::make_pair(3,4)]=mine_12;
        mine *mine_13=new mine(resource_manager::instance().get_pic("mine_2"),"square",4,3);
        mine_list[std::make_pair(4,3)]=mine_13;
        mine *mine_14=new mine(resource_manager::instance().get_pic("mine_1"),"circle",4,4);
        mine_list[std::make_pair(4,4)]=mine_14;

    }

}



// Created by 26711 on 2024/6/14.