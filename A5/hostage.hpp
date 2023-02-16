#ifndef GALEXY_HOSTAGE_H
#define GALEXY_HOSTAGE_H

#include "rsdl.hpp"

class hostage
{
    public:
        hostage();
        hostage(std::string hostage_file_name,Point top_left_of_hostage,double _hostage_size_x,
        double _hostage_size_y);
        void show_img(Window* win);
        void kill_hostage();
        int is_dead();
        double x_for_getting_shot();
        double y_for_getting_shot();

    private:
        Point top_left;
        std::string hostage_name;
        double hostage_size_x;
        double hostage_size_y;
        int dead;

};
#endif