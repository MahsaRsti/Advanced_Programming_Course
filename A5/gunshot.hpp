#ifndef GALEXY_GUNSHOT_H
#define GALEXY_GUNSHOT_H

#include "rsdl.hpp"

class gunshot
{
    public:
        gunshot();
        void draw_shoot(Window *win);
        void update_shoot(double y_update);
        void get_x_y(double x,double y);
        double current_point_y();
        double current_point_x();

    private:
        double point_x;
        double point_y;
        
};

#endif
