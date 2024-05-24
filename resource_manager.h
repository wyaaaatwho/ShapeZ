//
// Created by 26711 on 2024/5/23.
//

#ifndef SHAPEZ_RESOURCE_MANAGER_H
#define SHAPEZ_RESOURCE_MANAGER_H
#include "global.h"

class resource_manager
{
private:
    
    QHash<QString, QPixmap> my_resources;
public:
    resource_manager();
    ~resource_manager();
    QPixmap get_pic(QString pic_name);

};

#endif //SHAPEZ_RESOURCE_MANAGER_H
