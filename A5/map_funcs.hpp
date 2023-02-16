#ifndef GALEXY_MAP_H
#define GALEXY_MAP_H

#include <vector>
#include <string>

class enemy;
class hostage;

std::vector <std::vector<std::string>> take_input(std::string file_name);

std::vector <class enemy> enemies_of_round(std::vector<std::string> lines_of_round,
                                           double images_x,double images_y,std::string file);

class hostage hostage_of_round(std::vector<std::string> lines_of_round,
                               double images_x,double images_y,std::string file);

void process_game(std::string ship_file,std::string enemy_file,std::string hostage_file,
                 std::string map_file);

#endif