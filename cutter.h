//
// Created by 26711 on 2024/6/22.
//

#ifndef SHAPEZ_CUTTER_H
#define SHAPEZ_CUTTER_H
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

class cutter : public item
{
public:
    int out1_i;int out2_i;int out1_j;int out2_j; // i,j of prev and next block
    int i_offset;int j_offset; // another part's i,j
    cutter(int i,int j,int direction,int level,int speed,QPixmap cutter_pic);
    ~cutter() override;
    void draw_item(QPainter &painter) override;
    void move_cargo() override;

    cargo *cargo_out2;

    QPixmap cutter_pic;

    static QTimer cutter_timer;

    bool free_to_use;

    bool out_1_ready;
    bool out_2_ready;
};


#endif //SHAPEZ_CUTTER_H
