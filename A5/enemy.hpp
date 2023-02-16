#ifndef GALEXY_ENEMY_H
#define GALEXY_ENEMY_H

#include "rsdl.hpp"

class enemy
{
    public:
        enemy();
        enemy(std::string enemy_file_name,Point top_left_of_enemy,double _enemy_size_x,
              double _enemy_size_y);
        void update_shooting();
        void show_enemy(Window* win);
        void shooting(Window* win);
        void wait_for_next_shot();
        void manage_shooting_time();
        double x_of_collision();
        double y_of_collision();
        void go_and_die();
        int is_dead();
        double y_for_collision_to_ship();

    private:
        Point top_left;
        std::string enemy_file;
        double enemy_size_x;
        double enemy_size_y;
        double y_shot;
        int shooting_time;
        int dead;
};
#endif