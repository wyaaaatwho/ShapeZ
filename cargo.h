//
// Created by 26711 on 2024/6/22.
//

#ifndef SHAPEZ_CARGO_H
#define SHAPEZ_CARGO_H

#include <QHash>
#include <QPixmap>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QStackedWidget>
#include <QTimer>

#include <cmath>





class cargo : public QObject
{
    Q_OBJECT
public:

    cargo(int x, int y, int type, int speed, int direction, int state,QPixmap& cargo_pic);
    ~cargo();
    void move();
    void detect();
    void draw(QPainter &painter);

    signals:
        void cargo_into_hub(int type);


public:
    double x ;
    double y;
    double x0 ; double y0 ;
    int i;int j;
    int type;        //0:circle;1:square;2:left half circle;3:right half circle
    int speed;
    int direction;
    int state;
    int key;

    const double PI = 3.14159265358979323846;

// TURNING ANGLE
    double angle = 0.0;

// TURNING SPEED
    double turn_speed ;

    QPixmap cargo_pic;
    static QTimer move_timer;
    static  int cargo_count;
};


#endif //SHAPEZ_CARGO_H
