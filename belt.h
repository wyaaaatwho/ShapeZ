//
// Created by 26711 on 2024/6/11.
//

#ifndef SHAPEZ_BELT_H
#define SHAPEZ_BELT_H

#endif //SHAPEZ_BELT_H
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
    belt(int i,int j,int direction);
    ~belt();
    void draw_item(QPainter &painter);
    void place_item(QMouseEvent *event);
    void delete_item(QMouseEvent *event);
    void upgrade_item();
};

