#ifndef __INPUT_HH__
#define __INPUT_HH__

#include <vector>
#include <string>

const char COMMA_DELIMITER=',';
const char SPACE_DELIMITER=' ';
const std::string SUCCSESS_MESSAGE="OK";
const std::string POST_WORD="POST";
const std::string GET_WORD="GET";
const std::string DELETE_WORD="DELETE";
const std::string SIGNUP_WORD="signup";
const std::string TRIPS_COMMAND_WORD="trips";
const std::string USERNAME_WORD="username";
const std::string ROLE_WORD="role";
const std::string ORIGIN_WORD="origin";
const std::string DESTINATION_WORD="destination";
const std::string ID_WORD="id";
const std::string ACCEPT_TRAVEL_WORD="accept";
const std::string FINISH_TRAVEL_WORD="finish";
const std::string PASSENGER_WORD="passenger";
const std::string DRIVER_WORD="driver";
const std::string WATING_STATUS="waiting";
const std::string TRAVELLING_STATUS="traveling";
const std::string FINISHED_STATUS="finished";
const std::string GETTING_COST_WORD="cost";
const std::string HURRY_WORD="in_hurry";
const std::string IS_IN_HURRY="yes";
const std::string IS_NOT_IN_HURRY="no";
const std::string SORT_COST_WORD="sort_by_cost";
const std::string SORTING="yes";
const std::string NOT_SORTING="no";

class Person;
class Trip;
class Locations;

class Input
{
    public:
        Input(std::string map_file_name);
        ~Input();
        void take_commands();

    private:
        void post_commands_process(std::vector <std::string> line);
        void get_commands_process(std::vector <std::string> line);
        void delete_commands_process(std::vector <std::string> line);
        void signup(std::vector <std::string> line);
        void requesting_trip(std::vector <std::string> line);
        void display_trips(std::vector <std::string> line);
        void display_wanted_trip(std::vector <std::string> line);
        void accepting_travel(std::vector <std::string> line);
        void finish_travel(std::vector <std::string> line);
        void calculate_cost(std::vector <std::string> line);

        Trip* find_trip_by_id(int id);
        Person* find_member(std::string user_name);
        Locations* finding_place(std::string place);
        std::string find_item_in_line(std::vector <std::string> line,std::string item_name);
        double total_price(Locations* loc1,Locations* loc2, std::string in_hurry_status);
        void print_sorted_trips();
        std::vector <Locations*> available_locations;
        std::vector <Person*> members;
        std::vector <Trip*> trips;
        int cur_trip_id; 
};

#endif