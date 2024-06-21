
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

class item
{
public :
    int i;
    int j;
    int type;
    int direction;
    int level;
    int speed;

    virtual void draw_item(QPainter &painter)=0;
    //virtual void place_item(QMouseEvent *event)=0;
    //virtual void delete_item(QMouseEvent *event)=0;
    //virtual void upgrade_item()=0;

    virtual ~item() = default;

};



#endif //SHAPEZ_ITEM_H
