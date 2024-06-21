#ifndef SHAPEZ_START_PAGE_H
#define SHAPEZ_START_PAGE_H

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




class Startpage:public QWidget
{
    Q_OBJECT

public:
    Startpage(QWidget *parent=nullptr);
    ~Startpage();
    void paintEvent(QPaintEvent *event) override;
    // use a static function to get the instance of the class,USING shared ptr to avoid memory leak



private slots:

    void on_start_button();
    void leave_start_button();
    //void handle_continue_button();
signals:
    void changePage(int index);

private:
    QPushButton *start_button;
    QPushButton *continue_button;
    QPushButton *exit_button;
    QPushButton *help_button;
    QPixmap start_page_pic;
};


class IconSwitcher : public QObject {
Q_OBJECT

public:
    IconSwitcher(QPushButton *button, const QIcon &defaultIcon, const QIcon &hoverIcon)
            : QObject(button), m_button(button), m_defaultIcon(defaultIcon), m_hoverIcon(hoverIcon) {
        m_button->setIcon(m_defaultIcon);
        m_button->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == m_button) {
            if (event->type() == QEvent::Enter) {
                m_button->setIcon(m_hoverIcon);
            } else if (event->type() == QEvent::Leave) {
                m_button->setIcon(m_defaultIcon);
            }
        }

        return QObject::eventFilter(obj, event);
    }

private:
    QPushButton *m_button;
    QIcon m_defaultIcon;
    QIcon m_hoverIcon;
};

#endif //SHAPEZ_START_PAGE_H