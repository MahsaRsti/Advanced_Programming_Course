#ifndef GALEXY_SHIP_H
#define GALEXY_SHIP_H

#include "rsdl.hpp"

class game;

class ship
{
    public:
        ship();
        ship(std::string ship_file_name,Point top_left_of_image,double _img_size_x,
             double _img_size_y,game *game);
        void update();
        void show_img(Window* win);
        void handle_key_press(char key);
        void handle_key_release(char key);
        int if_ship_shoot();
        double x_for_shoot();
        double y_for_shoot();
        int turn_off_shooting(double shot_y);
        double y_for_update_shoot();
        void kill_ship();
        int is_dead();

    private:
        int reach_width_limit();
        int reach_height_limit();
        int shotgun;
        std::string ship_name;
        Point top_left;
        double image_x;
        double image_y;
        double img_size_x;
        double img_size_y;
        game *Game;
        int dead;
};
#endif