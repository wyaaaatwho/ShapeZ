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




class game_page :public QWidget
{
    Q_OBJECT
public:
    game_page(QWidget *parent=nullptr);
    ~game_page();
    void paintEvent(QPaintEvent *event) override;

private slots:
    void handle_back_button();

private:
    QPushButton *store_button;
    QPushButton *help_button;
    QPushButton *back_button;
    QPushButton *cutter;
    QPushButton *miner;
    QPushButton *rope;
    QPushButton *trash_bin;
    QPixmap game_background;

};


#endif //SHAPEZ_GAME_PAGE_H
