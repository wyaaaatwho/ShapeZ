//
// Created by 26711 on 2024/5/24.
//
//class to display image
#include "global.h"
#include "image_widget.h"
image_widget::image_widget(const QPixmap & pic, QWidget *parent): QWidget(parent)
{
    this->pic = pic;
}

void image_widget::paintEvent(QPaintEvent * event, int x, int y)
{
    //Q_UNSUSED(event); //make it like this first
    QPainter painter(this);
    painter.drawPixmap(x, y, pic);
}

image_widget::~image_widget()
{
    //delete pic;
}
