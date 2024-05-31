//
// Created by 26711 on 2024/5/24.
//

#ifndef SHAPEZ_IMAGE_WIDGET_H
#define SHAPEZ_IMAGE_WIDGET_H
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

class image_widget : public QWidget
{
    Q_OBJECT
public:
    explicit image_widget(const QPixmap & pic, QWidget *parent = nullptr);
    ~image_widget();
    void paintEvent(QPaintEvent *event, int x, int y);
    QPixmap pic;
};

#endif //SHAPEZ_IMAGE_WIDGET_H
