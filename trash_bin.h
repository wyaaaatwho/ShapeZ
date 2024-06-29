//
// Created by 26711 on 2024/6/22.
//

#ifndef SHAPEZ_TRASH_BIN_H
#define SHAPEZ_TRASH_BIN_H
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

class trash_bin :public item
{
public:
    trash_bin(int i,int j,int direction,int level,int speed,QPixmap trash_bin_pic);
    ~trash_bin() override;
    void draw_item(QPainter &painter) override;

    void move_cargo() override;

    QPixmap trash_bin_pic;

};


#endif //SHAPEZ_TRASH_BIN_H
