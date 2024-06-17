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

class mine
{
public:
    mine(QPixmap pic);
    ~mine();
    void upgrade_mine();
    void initialize_mine();


    QPixmap mine_pic;

};



#endif //SHAPEZ_MINE_H
