//
// Created by 26711 on 2024/5/30.
//

#ifndef SHAPEZ_HELP_PAGE_H
#define SHAPEZ_HELP_PAGE_H
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
#include <QTextEdit>
#include <QVBoxLayout>


class help_page :public QWidget
{
    Q_OBJECT
public:
    help_page(QWidget *parent=nullptr);
    ~help_page();


    void paintEvent(QPaintEvent *event) override;

signals:
    void changePage(int index);
private:
    QPushButton *back_button;
    QPixmap help_page_pic;
    QTextEdit *help_text;
};


#endif //SHAPEZ_HELP_PAGE_H
