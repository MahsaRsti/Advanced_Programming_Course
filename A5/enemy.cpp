#include "enemy.hpp"
#include <string.h>
#include <vector>

using namespace std;

const int SHOT_RADIUS=5;
const int GAME_SIZE_Y=480;
const int SHOT_DELAY=40;
const int SHOT_MOVE=5;

enemy::enemy(string enemy_file_name,Point top_left_of_enemy,double _enemy_size_x,
             double _enemy_size_y) :top_left(top_left_of_enemy)
{
    enemy_file=enemy_file_name;
    enemy_size_x=_enemy_size_x;
    enemy_size_y=_enemy_size_y;
    y_shot=top_left.y+enemy_size_y;
    shooting_time=0;
    dead=0;
}

void enemy::update_shooting()
{
    y_shot +=enemy_size_y/SHOT_MOVE;
}

void enemy::show_enemy(Window* win)
{
    win->draw_img(enemy_file,Rectangle(top_left,enemy_size_x,enemy_size_y));
}

void enemy::shooting(Window* win)
{
    win->fill_circle(Point(top_left.x+enemy_size_x/2,y_shot),SHOT_RADIUS,RED);
}

double enemy::x_of_collision()
{
    return top_left.x+enemy_size_x/2;
}

double enemy::y_of_collision()
{
    return top_left.y+enemy_size_y;
}

double enemy::y_for_collision_to_ship()
{
    return y_shot;
}

void enemy::go_and_die()
{
    dead=1;
}

int enemy::is_dead()
{
    return dead;
}

void enemy::wait_for_next_shot()
{
    if (y_shot >= GAME_SIZE_Y)
    {
        if (shooting_time>=SHOT_DELAY)
        {
            y_shot=top_left.y+enemy_size_y;
            shooting_time=0;
        }
    }
}

void enemy::manage_shooting_time()
{
    shooting_time++;
}