//
// Created by 26711 on 2024/6/11.
//

#ifndef SHAPEZ_BELT_H
#define SHAPEZ_BELT_H
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

class belt :public item
{
public:
    belt(int i,int j,int direction,int level,int speed,QPixmap belt_pix);
    ~belt() override;
    void draw_item(QPainter &painter) override;
    //void place_item(QMouseEvent *event);
    //void delete_item(QMouseEvent *event);
    //void upgrade_item();

    bool paint_flag = false;
    QPixmap belt_pix;
};


#endif //SHAPEZ_BELT_H


