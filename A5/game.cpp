#include "rsdl.hpp"
#include "game.hpp"
#include "ship.hpp"
#include "gunshot.hpp"
#include "hostage.hpp"

using namespace std;

const int LOST=0;
const int WIN=1;
const int DUMMY=2;

game::game()
{
    if_game_running = 1;
    start_shooting=1;
}

void game::take_ship(class ship *_ship,class gunshot *_ship_shot)
{
        ship=_ship;
        shot=_ship_shot;
}

void game::take_enemies(vector <class enemy> _enemies)
{
    enemies=_enemies;
}

void game::take_hostage(class hostage *_hostage)
{
    hostage=_hostage;
}

int game::get_y()
{
    return win.get_height();
}

int game::get_x()
{
    return win.get_width();
}

int game::is_ship_or_hostage_dead()
{
    if (ship->is_dead() || hostage->is_dead()) 
        return 1;
    else
        return 0;
}

int game::are_enemies_dead()
{
    int enemy_status;
    for(int enemy_count=0;enemy_count<enemies.size();enemy_count++)
        {
            if(enemies[enemy_count].is_dead())
                enemy_status=0;
            else
            {
                enemy_status=1;
                break;
            }
        }
        if(enemy_status==0)
        {
            win.clear();
            return 1;
        }
        else
            return 0;
}

void game::ship_shooting()
{
    if (ship->if_ship_shoot() && start_shooting==1)
    {
            shot->get_x_y(ship->x_for_shoot(),ship->y_for_shoot());
            start_shooting=0;
    }
}

int game::run()
{
    while(if_game_running) 
    {
        process_events();
        ship_shooting();
        update_objects();
        draw_screen();
        if(is_ship_or_hostage_dead()) 
            return LOST;
        if(are_enemies_dead())
            return WIN;
        delay(100);
    }
    return DUMMY;
}

void game::process_events() 
{
    while(win.has_pending_event()) 
    {
        Event event = win.poll_for_event();
        switch (event.get_type()) 
        {
            case Event::QUIT:
                if_game_running = 0; 
                break;
            case Event::KEY_PRESS:
                ship->handle_key_press(event.get_pressed_key());
                break;
            case Event::KEY_RELEASE:
                ship->handle_key_release(event.get_pressed_key());
                break;
        }
    }
}

void game::handle_enemy()
{
    for(int enemy_count=0;enemy_count<enemies.size();enemy_count++)
    {
        if(shot->current_point_x()==enemies[enemy_count].x_of_collision() &&
           shot->current_point_y()<=enemies[enemy_count].y_of_collision() && 
           enemies[enemy_count].is_dead()==0)
                enemies[enemy_count].go_and_die();
        else if(enemies[enemy_count].is_dead()==0)
        {
            enemies[enemy_count].show_enemy(&win);
            enemies[enemy_count].shooting(&win);
        }
    }
}

void game::handle_hostage() 
{
    if(shot->current_point_x()==hostage->x_for_getting_shot() &&
    shot->current_point_y()<=hostage->y_for_getting_shot())
        hostage->kill_hostage();
    else if(hostage->is_dead()==0)
        hostage->show_img(&win);
}

void game::handle_ship() 
{
    for(int enemy_count=0;enemy_count<enemies.size();enemy_count++)
    {
        if(ship->x_for_shoot()==enemies[enemy_count].x_of_collision() &&
           ship->y_for_shoot()<=enemies[enemy_count].y_for_collision_to_ship() &&
           enemies[enemy_count].y_for_collision_to_ship()<=ship->y_for_shoot()+
           ship->y_for_update_shoot() && enemies[enemy_count].y_for_collision_to_ship()<=480 && 
           enemies[enemy_count].is_dead()==0)
                ship->kill_ship();

        else if(ship->is_dead()==0)
        {
                ship->show_img(&win);
                if(ship->if_ship_shoot())
                    shot->draw_shoot(&win);
        }
    }
}

void game::draw_screen()
{
    win.clear();
    this->handle_ship();
    this->handle_enemy();
    this->handle_hostage();
    win.update_screen();
}

void game::update_objects() 
{
    ship->update(); 
    if(ship->if_ship_shoot())
    {
        shot->update_shoot(ship->y_for_update_shoot());
        if(ship->turn_off_shooting(shot->current_point_y()))
            start_shooting=1;  
    }
    for(int enemy_count=0;enemy_count<enemies.size();enemy_count++)
    {
        enemies[enemy_count].update_shooting();
        enemies[enemy_count].manage_shooting_time();
        enemies[enemy_count].wait_for_next_shot();
    }
}