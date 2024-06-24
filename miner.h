//
// Created by 26711 on 2024/6/21.
//

#ifndef SHAPEZ_MINER_H
#define SHAPEZ_MINER_H

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
class miner:public item
{
Q_OBJECT
public:
    miner (int i,int j,int direction,int level,int speed,QPixmap miner_pic);
    ~miner() override;
    void draw_item(QPainter &painter) override;

    void generate_cargo();

    bool start_mining;
    int interval;
    QPixmap miner_pic;
    static QTimer *timer;

    void start_mining_slot();
    void stop_mining_slot();


};


#endif //SHAPEZ_MINER_H
