#include "global.h"
#include "mainwindow.h"

int game_state = stopped;
int window_width = window_width_1;
int window_height= window_height_1 ;
int cube_size = cube_size_1;
int map[10][18][4] = {0};
bool is_placing_belt = false;
bool want_place_belt = false;
int mouse_x = -1;
int mouse_y = -1;
int pre_item_i = 0;
int pre_item_j = 0;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
