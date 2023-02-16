#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

const char SPLIT_DELIMITER=' ';
const int COMMAND_NAME=0;

const int HEAVY_PRICE=3000;
const int HEAVY_DECREASE_HEALTH=45;
const int HEAVY_INCREASE_MONEY=100;

const int PISTOL_PRICE=400;
const int PISTOL_DECREASE_HEALTH=20;
const int PISTOL_INCREASE_MONEY=200;

const int KNIFE_DECREASE_HEALTH=35;
const int KNIFE_INCREASE_MONEY=500;

const int WON_PRIZE=2700;
const int LOST_PRIZE=2400;

const int PLUS=1;
const int MINUS=-1;
const int NEW_ROUND=1;

struct players_for_score
{
    string name;
    int kills_num;
    int dies_num;
    string role;
};

class player 
{
    public:
        player(string Name, string Role);
        void get_money();
        void get_health();
        bool equal_user_name(string User_Name);
        void disable_attack();
        void enable_attack();
        void buy_weapon(string weapon_name,int if_start);
        int weapon_existence(string weapon);
        bool have_enough_money(string weapon);
        void update_money(int money, int plus_minus);
        void update_health(int health,int new_round);
        int how_much_money(string weapon,string status);
        int how_much_health(string weapon);
        int shoot(string weapon,int if_start,player attacked);
        int if_afk();
        int if_dead();
        string player_role();
        string player_name();
        void die();
        void live();
        void add_dies();
        void add_kills();
        int kills_number();
        int dies_number();
        void update_weapons(string weapon,string status);

    private:
        string user_name;
        string role;

        int health;
        int money;

        int knife;
        int heavy;
        int pistol;

        int can_attack;
        int dead;
        int dies;
        int kills;

};

player::player(string Name, string Role)
{
    user_name=Name;
    role=Role;
    knife=1;
    heavy=0;
    pistol=0;
    money=1000;
    can_attack=1;
    dead=0;
    dies=0;
    kills=0;
}

void player::get_money()
{
    cout<<money<<'\n';
}

void player::get_health()
{
    cout<<health<<'\n';
}

bool player::equal_user_name(string User_Name)
{
    if(user_name==User_Name)
        return true;
    else
        return false;
}

void player::disable_attack()
{
    can_attack=0;
}

void player::enable_attack()
{
    can_attack=1;
}

int player::if_afk()
{
    return can_attack;
}

int player::if_dead()
{
    return dead;
}

void player::die()
{
    dead=1;
}

void player::live()
{
    dead=0;
}

void player::add_dies()
{
    dies++;
}

void player::add_kills()
{
    kills++;
}

int player::dies_number() 
{
    return dies;
}

int player::kills_number() 
{
    return kills;
}

string player::player_role()
{
    return role;
}

string player::player_name() 
{
    return user_name;
}

int player::weapon_existence(string weapon)
{
    if (weapon=="heavy")
        return heavy;
    else if (weapon=="pistol")
        return pistol;
    else if (weapon=="knife")
        return knife;
    else
        return 0;
}

bool player::have_enough_money(string weapon)
{
    if(weapon=="heavy")
    {
        if(money>=HEAVY_PRICE)
            return true;
    }
    else if(weapon=="pistol")
    {
        if(money>=PISTOL_PRICE)
            return true;
    }
    return false;
}

void player::update_money(int new_money,int plus_minus)
{
    if(plus_minus==PLUS)
        money=money+new_money;
    else if(plus_minus==MINUS)
        money=money-new_money;
    if(money>=10000)
        money=10000;
}

void player::update_health(int new_health, int new_round)
{
    if(new_round==NEW_ROUND)
        health=new_health;
    else
    {
        health =health-new_health;
        if(health<=0)
        {
            health=0;
            die();
        }
    }
}

int player::how_much_money(string weapon,string status)
{
    if (status=="buy")
    {
        if(weapon=="heavy")
            return HEAVY_PRICE;
        else if(weapon=="pistol")
            return PISTOL_PRICE;
        else
            return -1;
    }
    else if (status=="shoot")
    {
        if(weapon=="heavy")
            return HEAVY_INCREASE_MONEY;
        else if(weapon=="pistol")
            return PISTOL_INCREASE_MONEY;
        else if(weapon=="knife")
            return KNIFE_INCREASE_MONEY;
        else
            return -1;
    } 
    else
        return -1;  
}

int player::how_much_health(string weapon)
{
    if(weapon=="heavy")
        return HEAVY_DECREASE_HEALTH;
    else if(weapon=="pistol")
        return PISTOL_DECREASE_HEALTH;
    else if(weapon=="knife")
        return KNIFE_DECREASE_HEALTH;
    else
        return -1;
}

void player::update_weapons(string weapon, string status)
{
    if (status=="get")
    {
        if(weapon=="heavy")
            heavy=1;
        else if(weapon=="pistol")
            pistol=1;
    }
    else if (status=="loose")
    {
            heavy=0;
            pistol=0;
    }   
}

void player::buy_weapon(string weapon_name, int if_start)
{
    if (if_start==1)
        cout<<"you can't buy weapons anymore"<<'\n';
    else if(if_afk()==0)
        cout<<"user not available"<<'\n'; 
    else if(weapon_name!="heavy" && weapon_name!="pistol" && weapon_name!="knife")
        cout<<"weapon not available"<<'\n';
    else if(weapon_existence(weapon_name))
        cout<<"you already have this weapon"<<'\n';
    else if(have_enough_money(weapon_name)==false)
        cout<<"insufficient money"<<'\n';
    else
    {
        update_money(how_much_money(weapon_name,"buy"),MINUS);
        update_weapons(weapon_name,"get");
        cout<<"weapon bought successfully"<<'\n';
    }
}

int player::shoot(string weapon,int if_start,player attacked)
{
    int shot_done=0;

    if (if_start==0)
        cout<<"The game hasn't started yet"<<'\n';
    else if(if_afk()==0 || attacked.if_afk()==0)
        cout<<"user not available"<<'\n';
    else if(if_dead())
        cout<<"attacker is dead"<<'\n';
    else if(attacked.if_dead())
        cout<<"attacked is dead"<<'\n';
    else if(weapon_existence(weapon)==0)
        cout<<"attacker doesn't have this gun"<<'\n';
    else if(player_role()==attacked.player_role())
        cout<<"you can't shoot this player"<<'\n';
    else
    {
        update_money(how_much_money(weapon,"shoot"),PLUS);
        shot_done=1;
        cout<<"nice shot"<<'\n';
    }
    return shot_done;
}

vector <string> split_by_space(string line) 
{
    vector <string> results;
    int result_index=0;
    int space_index;
    while ( result_index<line.size()) 
    {
		space_index=line.find(SPLIT_DELIMITER,result_index);
		if (space_index==string::npos) 
        {
			results.push_back(line.substr(result_index));
			break;
		}
		results.push_back(line.substr(result_index,space_index-result_index));
		result_index=space_index+1;
	}
    return results;
}

int recognize_player(vector<player> players, string user_name)
{
    for(int count_players=0;count_players<players.size();count_players++)
    {
        if(players[count_players].equal_user_name(user_name))
            return count_players;
    }
    return -1;
}

void make_health_of_all_players_to_hundred(vector <player> &players)
{
    for(int count_players=0;count_players<players.size();count_players++)
        players[count_players].update_health(100,NEW_ROUND);
}

void back_all_players_to_life(vector <player> &players)
{
    for(int count_players=0;count_players<players.size();count_players++)
        players[count_players].live();
}

void update_players_money(vector <player> &players, int countet_terrorist_won)
{
    for(int count_players=0;count_players<players.size();count_players++)
    {
        if(countet_terrorist_won==1)
        {
            if(players[count_players].player_role()=="counter-terrorist")
                players[count_players].update_money(WON_PRIZE,PLUS);
            else if(players[count_players].player_role()=="terrorist")
                players[count_players].update_money(LOST_PRIZE,PLUS);
        }
        else if(countet_terrorist_won==0)
        {
            if(players[count_players].player_role()=="counter-terrorist")
                players[count_players].update_money(LOST_PRIZE,PLUS);
            else if(players[count_players].player_role()=="terrorist")
                players[count_players].update_money(WON_PRIZE,PLUS);
        }
    }
}

int game_result(vector <player> players)
{
    vector <player> counter_terrorist;
    vector <player> terrorist;
    int alive_count_terrorist=0;

    for(int count_players=0;count_players<players.size();count_players++)
    {
        if(players[count_players].player_role()=="counter-terrorist")
            counter_terrorist.push_back(players[count_players]);
        else if(players[count_players].player_role()=="terrorist")
            terrorist.push_back(players[count_players]);
    }
    for(int count_counter=0;count_counter<counter_terrorist.size();count_counter++)
    {
        if(counter_terrorist[count_counter].if_dead()==0 && 
           counter_terrorist[count_counter].if_afk()==1)
                alive_count_terrorist++;
    }
    if(alive_count_terrorist!=0)
    {
        cout<<"counter-terrorist won"<<'\n';
        return 1;
    }
    else
    {
        cout<<"terrorist won"<<'\n';
        return 0;
    }
}

void print_board(vector <players_for_score> players, string role)
{
    cout<<role<<" players:"<<'\n';
    for(int count_players=0;count_players<players.size();count_players++)
    {
        if(players[count_players].role==role)
        {
            cout<<players[count_players].name<<' ';
            cout<<players[count_players].kills_num<<' ';
            cout<<players[count_players].dies_num<<'\n';
        }
    }
}

vector <players_for_score> put_objects_to_struct(vector <player> players)
{
    vector <players_for_score> players_s;
    players_for_score new_player;
    players_for_score dummy_player={"dummy", -1, -1, "dummy"};
    for(int count_players=0;count_players<players.size();count_players++)
    {
        new_player.name=players[count_players].player_name();
        new_player.kills_num=players[count_players].kills_number();
        new_player.dies_num=players[count_players].dies_number();
        new_player.role=players[count_players].player_role();
        players_s.push_back(new_player);
    }
    players_s.push_back(dummy_player);
    return players_s;
}

void score_board(vector <player> players)
{
    int sort_die_start=0;
    int sort_name_start;
    vector <players_for_score> players_s=put_objects_to_struct(players);

    sort(players_s.begin(),players_s.end(),[](players_for_score a, players_for_score b)
    {
        return a.kills_num>b.kills_num;
    });

    for(int count_players=1;count_players<players_s.size()-1;count_players++)
    {
        if(players_s[count_players-1].kills_num==players_s[count_players].kills_num)
        {
            if(players_s[count_players-1].kills_num!=players_s[count_players+1].kills_num)
            {
                sort(players_s.begin()+sort_die_start,players_s.begin()+count_players+1,
                    [](players_for_score a,players_for_score b)
                {
                    return a.dies_num<b.dies_num;
                });
                sort_name_start=sort_die_start;
                for(int second_count=sort_name_start+1;second_count<=count_players;second_count++)
                {
                    if(players_s[second_count-1].dies_num==players_s[second_count].dies_num)
                    {
                        if(players_s[second_count-1].dies_num!=players_s[second_count+1].dies_num)
                        {
                            sort(players_s.begin()+sort_name_start,players_s.begin()+second_count+1,
                                [](players_for_score a,players_for_score b)
                            {
                                return a.name<b.name;
                            });
                            sort_name_start=second_count+1;
                            second_count++;
                        }
                    }
                    else
                        sort_name_start=second_count;
                }
                sort_die_start=count_players+1;
                count_players++;
            }
        }
        else 
            sort_die_start=count_players;
    }
    print_board(players_s,"counter-terrorist");
    print_board(players_s,"terrorist");
}

void process_round_commands(vector<player> &players, vector <string> parts_of_command,int if_start)
{
    int which_player;

    if(parts_of_command[COMMAND_NAME]=="get-money")
    {
        which_player=recognize_player(players,parts_of_command[1]);
        players[which_player].get_money();
    }
    else if(parts_of_command[COMMAND_NAME]=="get-health")
    {
        which_player=recognize_player(players,parts_of_command[1]);
        players[which_player].get_health();
    }
    else if(parts_of_command[COMMAND_NAME]=="go-afk")
    {
        which_player=recognize_player(players,parts_of_command[1]);
        players[which_player].disable_attack();
        cout<<"ok"<<'\n';
    }
    else if(parts_of_command[COMMAND_NAME]=="go-atk")
    {
        which_player=recognize_player(players,parts_of_command[1]);
        players[which_player].enable_attack();
         cout<<"ok"<<'\n';
    }
    else if(parts_of_command[COMMAND_NAME]=="buy")
    {
        which_player=recognize_player(players,parts_of_command[1]);
        if(which_player==-1)
            cout<<"user not available"<<'\n';
        else
            players[which_player].buy_weapon(parts_of_command[2],if_start);
    }
    else if(parts_of_command[COMMAND_NAME]=="shoot")
    {
        which_player=recognize_player(players,parts_of_command[1]);
        int attacked=recognize_player(players,parts_of_command[2]);

        if (which_player==-1 || attacked==-1)
            cout<<"user not available"<<'\n';
        else 
        {
            int shot_done=players[which_player].shoot(parts_of_command[3],if_start,players[attacked]);
            if(shot_done)
            {
                players[attacked].update_health(players[attacked].how_much_health
                                                                  (parts_of_command[3]),0);
                if(players[attacked].if_dead())
                {
                    players[which_player].add_kills();
                    players[attacked].add_dies();
                    players[attacked].update_weapons(parts_of_command[3],"loose");
                }
            }
        }
    }
    else if(parts_of_command[COMMAND_NAME]=="score-board")
        score_board(players);    
}

void process_game_inputs()
{
    vector <player> players;
    string num_of_rounds;
    int num_of_round_commands;
    vector <string> parts_of_line;
    string line;
    int countet_terrorist_won;
    int if_start=0;

    getline(cin,num_of_rounds);
    for(int count_rounds=0;count_rounds<stoi(num_of_rounds);count_rounds++)
    {
        getline(cin,line);
        parts_of_line=split_by_space(line);
        if(parts_of_line[COMMAND_NAME]=="round") 
        {
            if_start=0;
            make_health_of_all_players_to_hundred(players);
            back_all_players_to_life(players);
            num_of_round_commands=stoi(parts_of_line[1]);
            for(int count_commands=0;count_commands<num_of_round_commands;count_commands++)
            {
                getline(cin,line);
                parts_of_line=split_by_space(line);
                if(parts_of_line[COMMAND_NAME]=="start")
                {
                    cout<<"fight!"<<'\n';
                    if_start=1;
                }
                else
                    process_round_commands(players,parts_of_line,if_start);
            }
            countet_terrorist_won=game_result(players);
            update_players_money(players, countet_terrorist_won);
        }
        else if(parts_of_line[COMMAND_NAME]=="add-user") 
        {
           player new_player(parts_of_line[1],parts_of_line[2]);
           players.push_back(new_player);
           count_rounds--;
           cout<<"ok"<<'\n';
        } 
        else if(parts_of_line[COMMAND_NAME]=="score-board")
        {
           score_board(players); 
           count_rounds--;
        }
    }
    while(cin>>line)
        score_board(players);
}

int main()
{
    process_game_inputs();
    return 0;
}