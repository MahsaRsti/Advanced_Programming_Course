#include "hostage.hpp"
#include <string.h>

using namespace std;

hostage::hostage(string hostage_file_name,Point top_left_of_hostage,double _hostage_size_x,
                 double _hostage_size_y): top_left(top_left_of_hostage)
{
    hostage_name=hostage_file_name;
    hostage_size_x=_hostage_size_x;
    hostage_size_y=_hostage_size_y;
    dead=0;
}

void hostage::show_img(Window *win)
{
    win->draw_img(hostage_name,Rectangle(top_left,hostage_size_x,hostage_size_y));
}

void hostage::kill_hostage()
{
    dead=1;
}

int hostage::is_dead()
{
    return dead;
}

double hostage::x_for_getting_shot()
{
    return top_left.x+hostage_size_x/2;
}

double hostage::y_for_getting_shot()
{
    return top_left.y+hostage_size_y;
}