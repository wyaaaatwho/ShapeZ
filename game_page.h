//
// Created by 26711 on 2024/5/29.
//

#ifndef SHAPEZ_GAME_PAGE_H
#define SHAPEZ_GAME_PAGE_H

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

#include "item.h"




class game_page :public QWidget
{
    Q_OBJECT
public:
    game_page(QWidget *parent=nullptr);
    ~game_page();

    void paintEvent(QPaintEvent *event) override;
    //void draw_belt(QPainter &painter);
    void draw_mine(QPainter &painter);


    static QMap <std::pair<int,int>,item*> item_list;
    static int map[16][24][4]; // 0: item type 1: item level 2: item direction 3: item paint_flag
    int mouse_x;
    int mouse_y;
    int pre_item_i;
    int pre_item_j;
    int item_count;


    int game_map_width;
    int game_map_height;
    int cube_size;

    static bool is_placing_belt;
    static bool want_place_belt;


    signals:
        void changePage(int index);

public slots:
        void handle_belt();

protected:
    //void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;




private:
    QPushButton *store_button;
    QPushButton *back_button;
    QPushButton *cutter;
    QPushButton *miner;
    QPushButton *belt_button;
    QPushButton *trash_bin;
    QPixmap game_background;
    QPixmap cutter_pic;
    QPixmap miner_pic;
    QPixmap belt_pic;
    QPixmap trash_bin_pic;
    QTimer *timer;

    void mousePressEvent(QMouseEvent *event);
};



#endif //SHAPEZ_GAME_PAGE_H
