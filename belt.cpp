#include "game_page.h"
#include "global.h"
#include "belt.h"

int belt::belt_speed = 2;

QTimer belt::belt_timer;

void game_page::placeBelt(QMouseEvent *event)
{
    //handle belt
    if(want_place_belt&&(event->buttons() & Qt::LeftButton)) // Check if left button is pressed
    {
        mouse_x=event->x();
        mouse_y=event->y();


        is_placing_belt=true;
        want_place_belt=false;


        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
    else if(is_placing_belt&&(event->buttons() & Qt::LeftButton))//Check if left button is pressed
    {
        int current_x = event->x();
        int current_y = event->y();

        int current_i = current_y / cube_size_1;
        int current_j = current_x / cube_size_1;

        int prev_i = mouse_y / cube_size_1;
        int prev_j = mouse_x / cube_size_1;

        /*if (current_i != prev_i || current_j != prev_j)*/
            if (current_i >= 0 && current_i < 10 && current_j >= 0 && current_j < 18)
            {
                if (map[current_i][current_j][0] == 0&&map[prev_i][prev_j][0]==ITEM_BELT)// if the current position is empty and the previous position is belt
                {
                    map[current_i][current_j][0] = ITEM_BELT;
                    map[current_i][current_j][3] = 0;
                    if(map[prev_i][prev_j][2]!=0)//if the previous belt has a direction
                    {
                        if (current_i - 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_DOWN;
                            if (map[prev_i][prev_j][2] == DIR_LEFT)
                                map[prev_i][prev_j][2] = DIR_LEFT_DOWN;
                            else if (map[prev_i][prev_j][2] == DIR_RIGHT)
                                map[prev_i][prev_j][2] = DIR_RIGHT_DOWN;
                        }
                        else if (current_i + 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_UP;
                            if (map[prev_i][prev_j][2] == DIR_LEFT)
                                map[prev_i][prev_j][2] = DIR_LEFT_UP;
                            else if (map[prev_i][prev_j][2] == DIR_RIGHT)
                                map[prev_i][prev_j][2] = DIR_RIGHT_UP;
                        }
                        else if (current_i == prev_i && current_j - 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_RIGHT;
                            if (map[prev_i][prev_j][2] == DIR_UP)
                                map[prev_i][prev_j][2] = DIR_UP_RIGHT;
                            else if (map[prev_i][prev_j][2] == DIR_DOWN)
                                map[prev_i][prev_j][2] = DIR_DOWN_RIGHT;
                        }
                        else if (current_i == prev_i && current_j + 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_LEFT;
                            if (map[prev_i][prev_j][2] == DIR_UP)
                                map[prev_i][prev_j][2] = DIR_UP_LEFT;
                            else if (map[prev_i][prev_j][2] == DIR_DOWN)
                                map[prev_i][prev_j][2] = DIR_DOWN_LEFT;
                        }
                    }
                    else if(map[prev_i][prev_j][2]==0)//if the previous belt has no direction
                    {
                        if (current_i - 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_DOWN;
                            map[prev_i][prev_j][2] = DIR_DOWN;
                        }
                        else if (current_i + 1 == prev_i && current_j == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_UP;
                            map[prev_i][prev_j][2] = DIR_UP;
                        }
                        else if (current_i == prev_i && current_j - 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_RIGHT;
                            map[prev_i][prev_j][2] = DIR_RIGHT;
                        }
                        else if (current_i == prev_i && current_j + 1 == prev_j)
                        {
                            map[current_i][current_j][2] = DIR_LEFT;
                            map[prev_i][prev_j][2] = DIR_LEFT;
                        }
                    }
                }
                else if(map[current_i][current_j][0] == 0&&map[prev_i][prev_j][0]==0)// if the current position is empty and the previous position is empty
                {
                    map[current_i][current_j][0] = ITEM_BELT;
                    map[current_i][current_j][3]=0;//set the current position to belt
                }
                else if(map[current_i][current_j][0] == ITEM_BELT) // if current has, call it back
                {
                    if(((map[current_i][current_j][2] ==DIR_DOWN)||(map[current_i][current_j][2] ==DIR_LEFT_DOWN)||(map[current_i][current_j][2] ==DIR_RIGHT_DOWN))&&map[current_i+1][current_j][0]==ITEM_BELT)
                    {
                        delete item_list[std::make_pair(current_i+1,current_j)];
                        item_list.remove(std::make_pair(current_i+1,current_j));
                        map[current_i+1][current_j][0] = 0;
                        map[current_i+1][current_j][1] = 0;
                        map[current_i+1][current_j][2] = 0;
                        map[current_i+1][current_j][3] = 0;

                    }
                    else if(((map[current_i][current_j][2] ==DIR_UP)||(map[current_i][current_j][2] ==DIR_LEFT_UP)||(map[current_i][current_j][2] ==DIR_RIGHT_UP))&&map[current_i-1][current_j][0]==ITEM_BELT)
                    {
                        delete item_list[std::make_pair(current_i-1,current_j)];
                        item_list.remove(std::make_pair(current_i-1,current_j));
                        map[current_i-1][current_j][0] = 0;
                        map[current_i-1][current_j][1] = 0;
                        map[current_i-1][current_j][2] = 0;
                        map[current_i-1][current_j][3] = 0;
                    }
                    else if(((map[current_i][current_j][2] ==DIR_RIGHT)||(map[current_i][current_j][2] ==DIR_UP_RIGHT)||(map[current_i][current_j][2] ==DIR_DOWN_RIGHT))&&map[current_i][current_j+1][0]==ITEM_BELT)
                    {
                        delete item_list[std::make_pair(current_i,current_j+1)];
                        item_list.remove(std::make_pair(current_i,current_j+1));
                        map[current_i][current_j+1][0] = 0;
                        map[current_i][current_j+1][1] = 0;
                        map[current_i][current_j+1][2] = 0;
                        map[current_i][current_j+1][3] = 0;
                    }
                    else if(((map[current_i][current_j][2] ==DIR_LEFT)||(map[current_i][current_j][2] ==DIR_UP_LEFT)||(map[current_i][current_j][2] ==DIR_DOWN_LEFT))&&map[current_i][current_j-1][0]==ITEM_BELT)
                    {
                        delete item_list[std::make_pair(current_i,current_j-1)];
                        item_list.remove(std::make_pair(current_i,current_j-1));
                        map[current_i][current_j-1][0] = 0;
                        map[current_i][current_j-1][1] = 0;
                        map[current_i][current_j-1][2] = 0;
                        map[current_i][current_j-1][3] = 0;
                    }
                }
            }
            mouse_x = current_x;
            mouse_y = current_y;
            pre_item_i = current_i;
            pre_item_j = current_j;

        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
    else if(is_placing_belt&&!(event->buttons() & Qt::LeftButton))
    {
        is_placing_belt=false;
        set_belt();
        std::cout<<"is :"<<is_placing_belt<<std::endl;
        std::cout<<"want: "<<want_place_belt<<std::endl;
    }
}

void game_page::draw_belt_blue(QPainter &painter) //draw blue belt
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 18; j++)
        {
            if(map[i][j][0] == ITEM_BELT&&map[i][j][3]==0&&is_placing_belt)
            {
                painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, resource_manager::instance().get_pic("belt_blue"));
            }
        }
    }
}


void game_page::set_belt() //set belt conceretely
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 18; j++)
        {
            if(map[i][j][0] == ITEM_BELT&&map[i][j][3]==0) {
                map[i][j][3] = 1;
                if (map[i][j][2] == DIR_DOWN)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_down"));
                else if (map[i][j][2] == DIR_UP)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_up"));
                else if (map[i][j][2] == DIR_LEFT)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_left"));
                else if (map[i][j][2] == DIR_RIGHT)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_right"));
                else if (map[i][j][2] == DIR_LEFT_UP)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_left_up"));
                else if (map[i][j][2] == DIR_LEFT_DOWN)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_left_down"));
                else if (map[i][j][2] == DIR_RIGHT_UP)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_right_up"));
                else if (map[i][j][2] == DIR_RIGHT_DOWN)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_right_down"));
                else if (map[i][j][2] == DIR_UP_LEFT)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_up_left"));
                else if (map[i][j][2] == DIR_UP_RIGHT)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_up_right"));
                else if (map[i][j][2] == DIR_DOWN_LEFT)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_down_left"));
                else if (map[i][j][2] == DIR_DOWN_RIGHT)
                    item_list[std::make_pair(i, j)] = new belt(i, j, map[i][j][2], map[i][j][1], 1,
                                                               resource_manager::instance().get_pic("belt_down_right"));
            }
        }
    }
}

belt::belt(int i, int j, int direction, int level, int speed, QPixmap belt_pix): item(i,j,direction,level,speed),belt_pix(belt_pix)
{
    this->type=ITEM_BELT;
    cargo_in = nullptr;
    cargo_out = nullptr;
    belt_timer.start(500);
    connect(&belt_timer, &QTimer::timeout, this, &belt::detect_cargo_stopped);

}

belt::~belt()
{
    std::cout << "belt deleted" << std::endl;
}

void belt::draw_item(QPainter &painter)
{
    painter.drawPixmap(j * cube_size_1, i * cube_size_1, cube_size_1, cube_size_1, belt_pix);
}

void belt::detect_cargo_stopped()
{
    if(cargo_in!=nullptr)
    {
        if(cargo_in->i!=i||cargo_in->j!=j)
        {
            if(cargo_in->state==CARGO_STOPPED)
            {
                speed=0;
            }
            else
            {
                speed = belt_speed;
                this->cargo_in=nullptr;
            }
        }
    }
}