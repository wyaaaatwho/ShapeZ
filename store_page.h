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
    void display_coin(QPainter &painter);



private slots:

    void handle_increase_mine();
    void handle_money();
    void upgrade_hub();

signals:
    void changePage(int index);

private:
    QFont *coin_font; // font for displaying coin

    QPushButton *back_button;
    QPushButton *increase_mine;
    QPushButton *hub_big;
    QPushButton *money;
    QPixmap store_page_pic;
    QPixmap coin_icon;

    QTimer *timer;

};


#endif //SHAPEZ_STORE_PAGE_H
