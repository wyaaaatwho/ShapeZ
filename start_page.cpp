#include "global.h"

Start_page::start_page():QWidget(parent),resource_manager (vault)
{
    //set start page
    this->setFixedSize(1080, 800);
    QPixmap start_page_pic = vault.getpic("start_page");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(start_page_pic));
    
    //set all buttons on this page
    start_button = new QPushButton("Start", this);
    QPixmap start_button_icon = vault.get_pic("start_button");
    start_button->setIcon(QIcon(start_button_icon));
    start_button->setGeometry(QRect(QPoint(540, 200), QSize(200, 50)));
    connect(start_button, SIGNAL(clicked()), this, SLOT(start_game()));
    
    continue_button = new QPushButton("Continue", this);
    QPixmap continue_button_icon = vault.get_pic("continue_button");
    continue_button->setIcon(QIcon(continue_button_icon))
    continue_button->setGeometry(QRect(QPoint(540, 300), QSize(200, 50)));
    connect(continue_button, SIGNAL(clicked()), this, SLOT(continue_game()));
   
    exit_button = new QPushButton("Exit", this);
    QPixmap exit_button_icon = vault.get_pic("exit_button");
    exit_button->setIcon(QIcon(exit_button_icon));
    exit_button->setGeometry(QRect(QPoint(540, 400), QSize(200, 50)));
    connect(exit_button, SIGNAL(clicked()), this, SLOT(exit_game()));
    
    help_button = new QPushButton("Help", this);
    QPixmap help_button_icon = vault.get_pic("help_button");
    help_button->setIcon(QIcon(help_button_icon));
    help_button->setGeometry(QRect(QPoint(540, 500), QSize(200, 50)));
    connect(help_button, SIGNAL(clicked()), this, SLOT(help_game()));
    
}