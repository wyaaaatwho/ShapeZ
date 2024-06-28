//
// Created by 26711 on 2024/6/22.
//

#ifndef SHAPEZ_HUB_H
#define SHAPEZ_HUB_H

#include <QApplication>
#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QHash>
#include <QPalette>
#include <QPushButton>
#include <Qtimer>
#include <QDebug>
#include <QIcon>
#include <QWidget>
#include <iostream>
#include "item.h"
#include"global.h"
class hub: public item
{
public:
    hub(int i,int j,int direction,int level,int speed,QPixmap hub_pic);
    ~hub() override;
    void draw_item(QPainter &painter) override;
    //void set_hub(int i,int j);
    void set_task();
    //void upgrade_hub();
    void finish_task();

   // void move_cargo() override;

   void move_cargo() override;


    static int size;
    static int task1_num;
    static int task2_num;
    static int task1_progress;
    static int task2_progress;
    static int task1_type;
    static int task2_type;

    static int coins;
    static int coin_value ;// coins value

    static bool task_finished;


    QPixmap hub_pic;

    QString task1;
    QString task2;
    QString task1_count;
    QString task2_count;
    QPixmap mineral_icon1;
    QPixmap mineral_icon2;

    static hub* only_hub;

    static int game_level;

public slots:
    void get_cargo(int type);

};


#endif //SHAPEZ_HUB_H
