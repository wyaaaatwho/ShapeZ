#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, resource_manager &vault);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *button;
};
#endif // MAINWINDOW_H
