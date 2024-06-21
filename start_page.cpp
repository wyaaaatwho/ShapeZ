#include "start_page.h"
#include "game_page.h"
#include "help_page.h"
#include "global.h"
#include <iostream>


Startpage::Startpage(QWidget* parent):QWidget(parent)
{
    resource_manager& vault = resource_manager::instance();
    //set start page
    this->setFixedSize(window_width_1, window_height_1);
    start_page_pic = vault.get_pic("start_page");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(start_page_pic));
    this->setPalette(palette);
    //set all buttons on this page

    start_button = new QPushButton(this);
    QPixmap start_button_icon = vault.get_pic("start_button");
    QPixmap start_button_on_icon = vault.get_pic("start_button_on");
    start_button->setIcon(QIcon(start_button_icon));
    start_button->setIconSize(start_button_icon.size());
    start_button->setFixedSize(start_button_icon.size());
    start_button->setGeometry((window_width_1-start_button_icon.width())/2, (window_height_1-start_button_icon.height())/2, start_button_icon.width(), start_button_icon.height());

    connect(start_button, SIGNAL(clicked()), this, SLOT(emit changePage(1)));
    connect(start_button, SIGNAL(toggled()), this, SLOT(on_start_button()));
    connect(start_button, &QPushButton::clicked, [this]() { emit changePage(1); });
    //set border free
    start_button->setStyleSheet("QPushButton { border: none; }");
    auto *iconSwitcher = new IconSwitcher(start_button, start_button_icon, start_button_on_icon);
    start_button->installEventFilter(iconSwitcher);

    continue_button = new QPushButton("Continue", this);
    QPixmap continue_button_icon = vault.get_pic("continue_button");
    continue_button->setIcon(QIcon(continue_button_icon));
    continue_button->setGeometry(QRect(QPoint(window_width_1/2-100, ((window_height_1-start_button_icon.height())/2)+160), QSize(200, 60)));
    continue_button->setStyleSheet("QPushButton {"
                                   "font-size: 20px;"
                                   "border: 2px solid black; border-radius: 10px; "      // border style
                                   "background-color: lightgray;" // background color
                                   "padding: 5px;"                // padding
                                   "qproperty-iconSize: 24px 24px;" // icon size
                                   "}"
                                   "QPushButton:hover {"
                                   "font-size: 20px;"
                                   "border: 2px solid blue;border-radius: 10px;"      // hover style
                                   " background-color: lightblue;" // hover background
                                   "}");
    //connect(continue_button, SIGNAL(clicked()), this, SLOT(load_game()));

    exit_button = new QPushButton("Exit", this);
    QPixmap exit_button_icon = vault.get_pic("exit_button");
    exit_button->setIcon(QIcon(exit_button_icon));
    exit_button->setGeometry(QRect(QPoint(window_width_1/2-100, ((window_height_1-start_button_icon.height())/2)+250), QSize(200, 60)));
    exit_button->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 10px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 10px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(exit_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    help_button = new QPushButton("Help", this);
    QPixmap help_button_icon = vault.get_pic("help_button");
    help_button->setIcon(QIcon(help_button_icon));
    help_button->setGeometry(QRect(QPoint(window_width_1/2-100, ((window_height_1-start_button_icon.height())/2)+350), QSize(200, 60)));
    help_button->setStyleSheet(("QPushButton {"
                                "font-size: 20px;"
                                "border: 2px solid black; border-radius: 10px; "      // border style
                                "background-color: lightgray;" // background color
                                "padding: 5px;"                // padding
                                "qproperty-iconSize: 24px 24px;" // icon size
                                "}"
                                "QPushButton:hover {"
                                "font-size: 20px;"
                                "border: 2px solid blue;border-radius: 10px;"      // hover style
                                " background-color: lightblue;" // hover background
                                "}"));
    connect(help_button, &QPushButton::clicked, [this]() { emit changePage(2); });


}

Startpage::~Startpage()
{
    /*if(start_button!=nullptr)
        delete start_button;
    if(continue_button!=nullptr)
        delete continue_button;
    if(exit_button!=nullptr)
        delete exit_button;
    if(help_button!=nullptr)
        delete help_button;*/

}

//draw the start page
void Startpage::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(), start_page_pic);
}


void Startpage::on_start_button()
{
    start_button->setIcon(QIcon(QPixmap(":/start_button.png")));
}

void Startpage::leave_start_button()
{
    start_button->setIcon(QIcon(QPixmap(":/start_button_on.png")));
}

