#include "global.h"

#ifndef SHAPEZ_START_PAGE_H
#define SHAPEZ_START_PAGE_H

class start_page:public Qwidget
{
    Q_OBJECT
    public:
        start_page(resource_manager &vault,QWidget *parent = nullptr);
        ~start_page();
    private:   
        QPushButton *start_button;
        QPushButton *continue_button;
        QPushButton *exit_button;
        QPushButton *help_button;
}


#endif //SHAPEZ_START_PAGE_H