//
// Created by 26711 on 2024/5/23.
//
//all header files are included here
//all macro are defined here

#ifndef SHAPEZ_GLOBAL_H
#define SHAPEZ_GLOBAL_H

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
#include "mainwindow.h"
#include "resource_manager.h"
#include "image_widget.h"
#include "start_page.h"


#define window_width 1080
#define window_height 800
#define cube_size 40
#define started 1
#define stopped 0
#define paused 2
#define game_over 3

QString path=":/resource/";

#endif //SHAPEZ_GLOBAL_H
