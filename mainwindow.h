#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "game_page.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void stop_time();//stop timer when not playing the game
    void start_time();//start timer when playing the game

    static QStackedWidget *stacked_widget;
    static game_page *currentGamePage;

    static int game_state;

private:
    Ui::MainWindow *ui;
    QPushButton *button;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;


public slots:
    void setPage(int index) {

        stacked_widget->setCurrentIndex(index);
        if(index==4)
            start_time();
        else
            stop_time();
    }

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status)
    {
        if (status == QMediaPlayer::EndOfMedia) {
            player->play();
        }
    };



};
#endif // MAINWINDOW_H
