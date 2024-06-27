//
// Created by 26711 on 2024/6/25.
//

#ifndef SHAPEZ_TRANSFORMER_H
#define SHAPEZ_TRANSFORMER_H
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
#include <QMap>
#include <iostream>
#include "item.h"

class transformer :public item
{
public:
    transformer(int i,int j,int direction,int level,int speed,QPixmap transformer_pic);
    ~transformer() override;
    void draw_item(QPainter &painter) override;
    void move_cargo() override;
    QPixmap transformer_pic;
};


#endif //SHAPEZ_TRANSFORMER_H
