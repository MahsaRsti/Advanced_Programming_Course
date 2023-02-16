#include "game.hpp"
#include "ship.hpp"
#include "gunshot.hpp"
#include "enemy.hpp"
#include "hostage.hpp"
#include "map_funcs.hpp"
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

const int ROW=0; 
const int COLLUMN=1; 
const int ROUND=2; 
const char ENEMY='E';
const char HOSTAGE='H';
const double GAME_X=640;
const double GAME_Y=480;
const string WINNING_MESSAGE="You Won!";
const string LOOSING_GAME_MESSAGE="You Lost! Game Over!";

vector <vector<string>> take_input(string file_name)
{
    vector <vector<string>> game_lines;
    vector <string> m_n_l;
    vector <string> round_lines;
    ifstream input_txt(file_name);
    string line;
    for(int nums=0; nums<3;nums++)
    {
        getline(input_txt,line);
        m_n_l.push_back(line);
    }
    game_lines.push_back(m_n_l);

    for(int round_num=0;round_num<stoi(m_n_l[ROUND]);round_num++)
    {
        for(int rows=0;rows<stoi(m_n_l[ROW]);rows++)
        {
            getline(input_txt,line);
            round_lines.push_back(line);
        }
        game_lines.push_back(round_lines);
        round_lines.clear();
        getline(input_txt,line);
    }
    input_txt.close();
    return game_lines;
}

vector <class enemy> enemies_of_round(vector<string> lines_of_round,
                                      double images_x,double images_y,string file)
{
    vector <enemy> enemies;
    for (int round_line=0;round_line<lines_of_round.size();round_line++)
    {
        for (int line_char=0;line_char<lines_of_round[round_line].size();line_char++)
        {
            if(lines_of_round[round_line][line_char]==ENEMY)
            {
                enemy current_enemy(file,Point(line_char*images_x,round_line*images_y),
                                    images_x,images_y);
                enemies.push_back(current_enemy);
            }    
        }
    }
    return enemies;
}

class hostage hostage_of_round(vector<string> lines_of_round,
                               double images_x,double images_y,string file)
{
    hostage dummy(file,Point(0,0),50,50);
    for (int round_line=0;round_line<lines_of_round.size();round_line++)
    {
        for (int line_char=0;line_char<lines_of_round[round_line].size();line_char++)
        {
            if(lines_of_round[round_line][line_char]==HOSTAGE)
            {
                hostage _current_hostage(file,Point(line_char*images_x,
                                                        round_line*images_y),images_x,images_y);
                return _current_hostage;

            }
        }
    }
    return dummy;
}

void process_game(string ship_file,string enemy_file,string hostage_file,string map_file)
{
    vector <vector<string>> lines_of_game=take_input(map_file);
    double images_x=GAME_X/stoi(lines_of_game[0][COLLUMN]);
    double images_y=GAME_Y/stoi(lines_of_game[0][ROW]);
    game _game;
    int situation;
    
    for(int round_num=1;round_num<=stoi(lines_of_game[0][ROUND]);round_num++)
    {
        ship _ship(ship_file,Point(GAME_X/2,GAME_Y-images_y),images_x,images_y,&_game);
        gunshot ship_shot;
        _game.take_ship(&_ship,&ship_shot);

        vector <enemy> enemies=enemies_of_round(lines_of_game[round_num],
                                                images_x,images_y,enemy_file);

        hostage _hostage=hostage_of_round(lines_of_game[round_num],
                                          images_x,images_y,hostage_file);
        _game.take_enemies(enemies);
        _game.take_hostage(&_hostage);

        situation=_game.run();
        if(situation==0)
        {
            cout<<LOOSING_GAME_MESSAGE<<'\n';
            break;
        }    
    }
    if(situation==1)
        cout<<WINNING_MESSAGE<<'\n';
    delay(2000);
}
