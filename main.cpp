#include "global.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    resource_manager resource_vault;
    MainWindow w(resource_vault.get_pic("game_background"));
    w.show();
    return a.exec();
}
