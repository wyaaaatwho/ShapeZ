//
// Created by 26711 on 2024/6/2.
//

#ifndef SHAPEZ_STORE_PAGE_H
#define SHAPEZ_STORE_PAGE_H
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


class store_page :public QWidget{
    Q_OBJECT

public:
    store_page(QWidget *parent=nullptr);
    ~store_page();
    void paintEvent(QPaintEvent *event) override;



private slots:

    /*void handle_expand_map();
    void handle_clear_barriers();
    void handle_increase_mine();
    void handle_hub_big();
    void handle_money();*/

signals:
    void changePage(int index);

private:
    QPushButton *back_button;
    QPushButton *expand_map;
    QPushButton *clear_barriers;
    QPushButton *increase_mine;
    QPushButton *hub_big;
    QPushButton *money;
    QPixmap store_page_pic;

};


#endif //SHAPEZ_STORE_PAGE_H
