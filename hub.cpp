//
// Created by 26711 on 2024/6/22.
//

#include "hub.h"
#include"global.h"
#include"game_page.h"

int hub::task1_num;
int hub::task2_num;
int hub::task1_progress;
int hub::task2_progress;
int hub::task1_type;
int hub::task2_type;
int hub::coins;
bool hub::task_finished;

hub::hub(int i,int j,int direction,int level,int speed,QPixmap hub_pic):item(i,j,direction,level,speed),hub_pic(hub_pic)
{
    size=2;
    game_level=1;
    task_finished=false;
    set_task();
}

hub::~hub()
{

}

void hub::draw_item(QPainter &painter)
{
    if(level==1)
    painter.drawPixmap(j*cube_size_1,i*cube_size_1,cube_size_1*size,cube_size_1*size,hub_pic);
    else if(level==2)
    {
        hub_pic = QPixmap("resource/hub_big.png");
        painter.drawPixmap(j*cube_size_1,i*cube_size_1,cube_size_1*size,cube_size_1*size,hub_pic);
    }



    // paint task
    task1_count = QString::number(task1_progress);
    task2_count = QString::number(task2_progress);
    painter.drawText(j * cube_size_1+cube_size_1/2, i * cube_size_1 +cube_size_1, task1);
    painter.drawText(j * cube_size_1+cube_size_1, i * cube_size_1 +cube_size_1, task2);
    painter.drawText(j * cube_size_1+cube_size_1/2, i * cube_size_1 +cube_size_1/3+cube_size_1, task1_count);
    painter.drawText(j * cube_size_1+cube_size_1, i * cube_size_1 +cube_size_1/3+cube_size_1, task2_count);
    painter.drawPixmap(j * cube_size_1+cube_size_1/2, i * cube_size_1 +cube_size_1/2, 30, 30, mineral_icon1);
    painter.drawPixmap(j * cube_size_1 +cube_size_1, i * cube_size_1 +cube_size_1/2,30, 30, mineral_icon2);
}

void hub::set_task()
{
    if(game_level==1)
    {

        task1_num=20;
        task2_num=10;
        task1_progress=0;
        task2_progress=0;

        task1_type=CIRCLE;
        task2_type=LEFT_HALF_CIRCLE;

        //set task display
        task1="X 20";
        task1_count = QString::number(task1_progress);
        mineral_icon1=QPixmap("resource/circle.png");

        task2="X 10";
        task2_count = QString::number(task2_progress);
        mineral_icon2=QPixmap("resource/left_circle.png");

    }
}

void game_page::set_hub()
{
    hub* new_hub = new hub(3,8,0,1,10,QPixmap("resource/hub.png"));
    item_list[std::make_pair(3,8)]=new_hub;
    for(int i=new_hub->i;i<new_hub->i+new_hub->size;i++)
    {
        for(int j=new_hub->j;j<new_hub->j+new_hub->size;j++)
        {
            map[i][j][0]=ITEM_HUB;
            map[i][j][1]=1;
            map[i][j][2]=0;

        }
    }
}

void hub:: finish_task()
{
    if(task1_progress>=task1_num && task2_progress>=task2_num)
    {
        task_finished=true;
    }
    if(task_finished)
    {
        game_level++;
        set_task();
    }
}

void hub::cargo_get_in(int type)
{
    if(type == task1_type)
    {
        task1_progress++;
    }
    else if(type == task2_type)
    {
        task2_progress++;
    }
    else
    {
        coins++;
    }
}

