#include "gunshot.hpp"
#include <string.h>

using namespace std;

const int SHOT_RADIUS=5;
const int SHOT_MOVE=5;

gunshot::gunshot()
{
    point_x=0;
    point_y=0;
}
void gunshot::get_x_y(double x,double y)
{
    point_x=x;
    point_y=y;

}
void gunshot::draw_shoot(Window *win){
   win->fill_circle(Point(point_x,point_y),SHOT_RADIUS,YELLOW);
}
void gunshot::update_shoot(double y_update)
{
    point_y -=y_update/SHOT_MOVE;
}
double gunshot::current_point_y()
{
    return point_y;
}
double gunshot::current_point_x()
{
    return point_x;
}