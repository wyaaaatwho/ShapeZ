//
// Created by 26711 on 2024/6/14.
//

#ifndef SHAPEZ_MINE_H
#define SHAPEZ_MINE_H

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

#include <string>


class mine
{
public:
    mine(QPixmap pic,std::string name,int i,int j);
    ~mine();
    void upgrade_mine();
    void draw_mine(QPainter &painter);

    QPixmap mine_pic;
    std::string mine_name;
    int i;
    int j;


};



#endif //SHAPEZ_MINE_H
