//
// Created by 26711 on 2024/5/24.
//

#ifndef SHAPEZ_IMAGE_WIDGET_H
#define SHAPEZ_IMAGE_WIDGET_H
#include "global.h"

class image_widget : public QWidget
{
    Q_OBJECT
public:
    explicit image_widget(const QPixmap & pic, QWidget *parent = nullptr);
    ~image_widget();
    void paintEvent(QPaintEvent *event, int x, int y) override;
    QPixmap pic;
};

#endif //SHAPEZ_IMAGE_WIDGET_H
