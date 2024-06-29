//
// Created by 26711 on 2024/6/28.
//

#ifndef SHAPEZ_WIN_PAGE_H
#define SHAPEZ_WIN_PAGE_H

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
class win_page :public QWidget
{
    Q_OBJECT

public:
    win_page(QWidget *parent=nullptr);
    ~win_page();
    void paintEvent(QPaintEvent *event) override;

    static bool already_miner;
    static bool already_cutter;
    static bool already_belt;

    QPushButton *miner_button;
    QPushButton *cutter_button;
    QPushButton *belt_button;
    QPushButton *back_button;

    QPixmap win_page_pic;

public slots:
    void speed_up_miner();
    void speed_up_cutter();
    void speed_up_belt();

signals:
    void changePage(int index);
};


#endif //SHAPEZ_WIN_PAGE_H
