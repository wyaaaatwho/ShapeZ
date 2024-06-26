//
// Created by 26711 on 2024/5/30.
//
#include "global.h"
#include "help_page.h"
#include "start_page.h"

help_page::help_page(QWidget *parent):QWidget(parent)
{
    resource_manager& vault = resource_manager::instance();
    //set start page
    this->setFixedSize(window_width_1, window_height_1);
    help_page_pic = vault.get_pic("help_page");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(help_page_pic));
    this->setPalette(palette);

    back_button = new QPushButton("Back", this);
    back_button->setGeometry(QRect(QPoint(window_width_1/2-100, (window_height_1/2)+200), QSize(200, 60)));
    back_button->setStyleSheet(("QPushButton {"
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
    connect(back_button, SIGNAL(clicked()), this, SLOT(handle_back_button()));

    help_text = new QTextEdit(this);
    help_text->setGeometry(QRect(QPoint(window_width_1/2-500, ((window_height_1/2)-240)), QSize(1000, 400)));
    help_text->setStyleSheet(("QTextEdit {"
                             "font-size: 20px;"
                             "border: 2px solid black; border-radius: 10px; "      // border style
                             "background-color: lightgray;" // background color
                             "padding: 5px;"                // padding
                             "}"));

    // using html to format the text: Hail to the Front-End!
    QString text = "<div style='text-align: center;'>"
                   "<h1 style='font-size: 24px; font-weight: bold;'>关于本作</h1>"
                   "</div>"
                   "<p>这里是shapez，一个来自wyaaaattwho的异形工厂</p>"
                   "<p><strong>基本操作:</strong></p>"
                   "<ul>"
                   "<li>使用键盘W A S D控制建筑方向，鼠标右键撤销已放置的建筑。</li>"
                   "</ul>"
                   "<p><strong>共有四种建筑：</strong></p>"
                   "<ul>"
                   "<li><strong>开采器：</strong>放置在矿地上后可开采出物品。请注意输出物品的方向。</li>"
                   "<li><strong>传送带：</strong>运送物品。请注意运送物品的方向。</li>"
                   "<li><strong>切割机：</strong>将物品纵向切开并分别输出。如果只需要其中一半的物品，那么需要使用垃圾桶清除另一半物品，否则切割机会停止工作。</li>"
                   "<li><strong>垃圾桶：</strong>可以从所有四个方向上输入物品并永久清除它们。</li>"
                   "</ul>"
                   "<p><strong>获胜条件:</strong> 每个关卡需收集一定数量的物品，通过四个关卡即可获胜。</p>"
                   "<p>每个关卡结束后，可以升级开采器、传送带或切割机中的一个建筑。请注意，升级效果仅在当前关卡有效。</p>"
                   "<p>通过消耗金币，可以在商店中全局强化交付中心的大小、开采物所在地块的数量等。</p>"
                   "<p>游戏可自动存档。</p>"
                   "<p>感谢游玩！</p>"
                   "<p>更多内容请关注我的Github主页<a href=\"https://github.com/wyaaaatwho\">https://github.com/wyaaaatwho</a></p>"
                   "<p>或者关注我的博客网站<a href=\"https://blog.wyaaaattwho.xyz\">https://blog.wyaaaattwho.xyz</a></p>";
    help_text->setHtml(text);
}

void help_page::handle_back_button()
{
    auto * start = new Startpage(this->parentWidget());
    start->show();
    this->close();
}

help_page::~help_page()
{
    delete back_button;
    delete help_text;
}

void help_page::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, help_page_pic);
}
