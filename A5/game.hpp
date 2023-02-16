#ifndef GALEXY_GAME_H
#define GALEXY_GAME_H

#include <vector>
#include "rsdl.hpp"
#include "enemy.hpp"

class ship;
class gunshot;
class hostage;

class game
{
    public:
        game();
        void take_ship(class ship *_ship,class gunshot *_ship_shot);
        void take_enemies(std::vector <class enemy> _enemies);
        void take_hostage(class hostage *_hostage);
        int run();
        int get_y();
        int get_x();

    private:
        void process_events();
        void draw_screen();
        void update_objects();

        void handle_ship();
        void handle_enemy();
        void handle_hostage();
        int is_ship_or_hostage_dead();
        int are_enemies_dead();
        void ship_shooting();

        int if_game_running;
        int start_shooting;

        Window win;
        class gunshot *shot;
        class ship *ship;
        class hostage *hostage;
        std::vector <class enemy> enemies;
};
#endif