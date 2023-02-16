#include "ship.hpp"
#include "game.hpp"
#include <string.h>

using namespace std;

const char UP='w';
const char DOWN='s';
const char LEFT='a';
const char RIGHT='d';
const char SHOOT=' ';

ship::ship(string ship_file_name,Point top_left_of_image,double _img_size_x,double _img_size_y,
           game *game) :top_left(top_left_of_image)
{
    ship_name=ship_file_name;
    image_x=0;
    image_y=0;
    Game=game;
    img_size_x=_img_size_x;
    img_size_y=_img_size_y;
    shotgun=0;
    dead=0;
}

void ship::update()
{
    top_left.x +=image_x;
    top_left.y +=image_y;

    if(reach_width_limit()==1)
        top_left.x -=img_size_x;
    else if(reach_width_limit()==-1)
        top_left.x +=img_size_x;

    if(reach_height_limit()==1)
        top_left.y -=img_size_y;
    else if(reach_height_limit()==-1)
        top_left.y +=img_size_y;
}

void ship::show_img(Window *win)
{
    win->draw_img(ship_name,Rectangle(top_left,img_size_x,img_size_y));
}

double ship::y_for_update_shoot()
{
    return img_size_y;
}

int ship::if_ship_shoot()
{
    return shotgun;
}

double ship::x_for_shoot()
{
   return top_left.x+img_size_x/2;
}

double ship::y_for_shoot()
{
    return top_left.y;
}

int ship::turn_off_shooting(double shot_y)
{
    if(shot_y<=0)
    {
        shotgun=0;
        return 1;
    }
    return 0;
}

void ship::kill_ship()
{
    dead=1;
}

int ship::is_dead()
{
    return dead;
}

void ship::handle_key_press(char key)
{
    switch(key) {
        case RIGHT:
            image_x = img_size_x;
            break;
        case LEFT:
            image_x = -img_size_x;
            break;
        case UP:
            image_y= -img_size_y;
            break;
        case DOWN:
            image_y= img_size_y;
            break;
        case SHOOT:
            shotgun=1;
            break;
    }
}

void ship::handle_key_release(char key)
{
    switch(key)
    {
        case RIGHT:
            image_x=0;
            break;
        case LEFT:
            image_x =0;
            break;
        case UP:
            image_y=0;
            break;
        case DOWN:
            image_y=0;
            break;
    }
}
int ship::reach_width_limit()
{
    if (top_left.x>=Game->get_x())
        return 1;
    else if (top_left.x<=-img_size_x)
        return -1;
    else
        return 0;
}

int ship::reach_height_limit()
{
    if (top_left.y>Game->get_y()-img_size_y)
        return 1;
    else if (top_left.y<=-img_size_y)
        return -1;
    else
        return 0;
}