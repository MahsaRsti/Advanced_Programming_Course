#include "map_funcs.hpp"
#include <string>

using namespace std;

const string SHIP_ADRR="./assets/SHIP.png";
const string ENEMY_ADRR="./assets/ENEMY.jpg";
const string HOSTAGE_ADRR="./assets/HOSTAGE.jpeg";

int main(int argc, char* argv[])
{
    process_game(SHIP_ADRR,ENEMY_ADRR,HOSTAGE_ADRR,argv[1]);
    return 0;
}