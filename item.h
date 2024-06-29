
//
// Created by 26711 on 2024/6/21.
//

#ifndef SHAPEZ_ITEM_H
#define SHAPEZ_ITEM_H
#include <QHash>
#include <QPixmap>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QStackedWidget>

#include "cargo.h"

class item : public QWidget
{
public :
    int i;
    int j;
    int type;
    int direction; //0:up 1:right 2:down 3:left
    int level;
    int speed;

    cargo * cargo_in ;
    cargo * cargo_out ;

    int in_i;
    int in_j;
    int out_i;
    int out_j;


    virtual void draw_item(QPainter &painter)=0;

    item(int i,int j,int direction,int level,int speed)
            : i(i), j(j), direction(direction), level(level), speed(speed) {}

    virtual ~item() = default;

    virtual void move_cargo() = 0;



};



#endif //SHAPEZ_ITEM_H
