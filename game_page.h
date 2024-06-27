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
#include "mine.h"
#include "global.h"
#include "miner.h"
#include"cargo.h"


class game_page :public QWidget
{
    Q_OBJECT
public:
    game_page(QWidget *parent=nullptr);
    ~game_page();

    void paintEvent(QPaintEvent *event) override;
    //void draw_belt(QPainter &painter);
    void draw_mine(QPainter &painter);


    static QMap <std::pair<int,int>,item*>item_list;
    static QMap <std::pair<int,int>,mine*>mine_list;
    static QMap <int,cargo*>cargo_list;

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

    static bool is_placing_miner;
    static bool is_placing_cutter;
    static bool is_placing_trash_bin;
    static bool is_placing_transformer;

    static item *item_to_place;

    static QTimer great_timer; // 大时钟


    signals:
        void changePage(int index);


public slots:
        void handle_belt();
        void handle_miner();
        void handle_cutter();
        void handle_trash_bin();
        void handle_transformer();

protected:
    //void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;



    void delete_item(QMouseEvent *event);

    void set_buttons();
    void set_belt();void placeBelt(QMouseEvent *event);void draw_belt_blue(QPainter &painter);
    void set_mine(); //set two mines
    void set_hub();

    //place an item
    void place_item(QMouseEvent *event);
    void rotate_item(QKeyEvent *event);
    void set_item(QMouseEvent *event);




private:
    QPushButton *store_button;
    QPushButton *back_button;
    QPushButton *cutter_button;
    QPushButton *miner_button;
    QPushButton *belt_button;
    QPushButton *trash_bin_button;
    QPushButton *transformer_button;
    QPixmap game_background;
    QPixmap cutter_pic;
    QPixmap miner_pic;
    QPixmap belt_pic;
    QPixmap trash_bin_pic;


};



#endif //SHAPEZ_GAME_PAGE_H
