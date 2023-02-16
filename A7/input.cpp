#include "input.hpp"
#include "person.hpp"
#include "passenger.hpp"
#include "trips.hpp"
#include "driver.hpp"
#include "error.hpp"
#include "locations.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <iomanip>

using namespace std;

vector <string> split_line(string line,char delimiter) 
{
    vector <string> results;
    int result_index=0;
    int index;
    while ( result_index<line.size()) 
    {
		index=line.find(delimiter,result_index);
		if (index==string::npos) 
        {
			results.push_back(line.substr(result_index));
			break;
		}
		results.push_back(line.substr(result_index,index-result_index));
		result_index=index+1;
	}
    return results;
}

Input::Input(string map_file_name)
{
    ifstream locations(map_file_name);
    string line;
    getline(locations,line);
    while(getline(locations,line))
    {
        vector <string> location_info=split_line(line,COMMA_DELIMITER);
        Locations *cur_location=new Locations(location_info[0],stod(location_info[1]),
                               stod(location_info[2]),stod(location_info[3]));
       
        available_locations.push_back(cur_location);
    }
    locations.close();
    cur_trip_id=0;
}

void Input::take_commands()
{
    string line;
    vector <string> line_sections;
    error_checking first_command_checker;
    while(getline(cin,line))
    {
        line_sections=split_line(line,SPACE_DELIMITER);
        try
        {
            first_command_checker.check_first_command(line_sections[0]);

            if (line_sections[0]==POST_WORD)
                post_commands_process(line_sections);

            else if(line_sections[0]==GET_WORD)
                get_commands_process(line_sections);

            else if(line_sections[0]==DELETE_WORD)
                delete_commands_process(line_sections);
        }
        catch(Local_runtime_error &ex)
        {
            cout<<BAD_REQUEST_ERROR<<'\n';
        }
    }
}

Person* Input::find_member(string user_name)
{
    for(int count=0;count<members.size();count++)
    {
        if(members[count]->member_existence(user_name))
            return members[count];
    }
    return NULL;
}

Locations* Input::finding_place(string place)
{
    for(int count=0;count<available_locations.size();count++)
    {
        if(available_locations[count]->location_name()==place)
            return available_locations[count];
    }
    return NULL;
}

Trip* Input::find_trip_by_id(int id)
{
    for(int count=0;count<trips.size();count++)
    {
        if(trips[count]->is_id_matched(id))
            return trips[count];
    }
    return NULL;
}

string Input::find_item_in_line(vector <string> line,string item_name)
{
     for(int find_item=3;find_item<line.size();find_item++)
     {
         if(line[find_item]==item_name)
            return line[find_item+1];
     }
     return "NULL";
}

void Input::signup(vector <string> line)
{
    string user_name=find_item_in_line(line,USERNAME_WORD);
    string role=find_item_in_line(line,ROLE_WORD);
    error_checking signup_errors;

    try
    {
        signup_errors.check_sign_up_errors(find_member(user_name),role);
        
        if (role==PASSENGER_WORD)
        {
            Passenger *new_passenger=new Passenger(user_name,role);
            members.push_back(new_passenger);
        }
        else if(role==DRIVER_WORD)
        {
            Driver *new_driver=new Driver(user_name,role);
            members.push_back(new_driver);
        }
        cout<<SUCCSESS_MESSAGE<<'\n';
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    }
}

void Input::requesting_trip(vector <string> line)
{
    string user_name=find_item_in_line(line,USERNAME_WORD);
    string origin=find_item_in_line(line,ORIGIN_WORD);
    string destination=find_item_in_line(line,DESTINATION_WORD);
    string hurry_status=find_item_in_line(line,HURRY_WORD);
    error_checking requesting_errors;
   
    try
    {
        requesting_errors.not_finding_member_error(find_member(user_name));
        requesting_errors.not_finding_place_error(finding_place(origin));
        requesting_errors.not_finding_place_error(finding_place(destination));
        requesting_errors.check_command_size(line.size(),11,"request_type");
        requesting_errors.check_bool_vars_error(find_member(user_name)->is_in_trip(),true,
                                                "request_type");
        requesting_errors.check_bool_vars_error(find_member(user_name)->is_passenger(),false,
                                                "permission_type");           

        cur_trip_id++;
        double total_cost=total_price(finding_place(origin),finding_place(destination),hurry_status);
        find_member(user_name)->change_trip_status("start");
        Trip* new_trip=new Trip(user_name,origin,destination,cur_trip_id,total_cost);
        trips.push_back(new_trip);
        cout<<cur_trip_id<<'\n';
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    }
}

void Input::accepting_travel(vector <string> line)
{
    string driver_name=find_item_in_line(line,USERNAME_WORD);
    int trip_id=stoi(find_item_in_line(line,ID_WORD));
    error_checking accepting_errors;

    try
    {
        accepting_errors.not_finding_member_error(find_member(driver_name));
        accepting_errors.not_finding_trip_error(find_trip_by_id(trip_id));
        accepting_errors.check_bool_vars_error(find_member(driver_name)->is_passenger(),true,
                                               "permission_type");
        accepting_errors.check_bool_vars_error(find_member(driver_name)->is_in_trip(),true,
                                               "request_type");
        accepting_errors.check_bool_vars_error(find_trip_by_id(trip_id)->is_trip_waiting(),false,
                                               "request_type");
        
        find_trip_by_id(trip_id)->change_status(TRAVELLING_STATUS);
        find_trip_by_id(trip_id)->assign_driver(driver_name);
        find_member(driver_name)->change_trip_status("accept");
        cout<<SUCCSESS_MESSAGE<<'\n';
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    }
}

void Input::finish_travel(vector <string> line)
{
    string driver_name=find_item_in_line(line,USERNAME_WORD);
    int trip_id=stoi(find_item_in_line(line,ID_WORD));
    error_checking finishing_errors;

    try
    {
        finishing_errors.not_finding_member_error(find_member(driver_name));
        finishing_errors.not_finding_trip_error(find_trip_by_id(trip_id));
        finishing_errors.check_bool_vars_error(find_member(driver_name)->is_passenger(),true,
                                               "permission_type");
        finishing_errors.check_bool_vars_error(find_member(driver_name)->is_in_trip(),false,
                                               "request_type");
        finishing_errors.check_bool_vars_error(find_trip_by_id(trip_id)->
                                               is_driver_name_matched(driver_name),false,
                                               "request_type");

        find_member(find_trip_by_id(trip_id)->passenger_is_needed())->change_trip_status("end");
        find_trip_by_id(trip_id)->change_status(FINISHED_STATUS);
        find_member(driver_name)->change_trip_status("finish"); 
        cout<<SUCCSESS_MESSAGE<<'\n';                              
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    }
}

void Input::post_commands_process(vector <string> line)
{
    if(line[1]==SIGNUP_WORD)
        signup(line);

    else if(line[1]==TRIPS_COMMAND_WORD)
        requesting_trip(line);

    else if(line[1]==ACCEPT_TRAVEL_WORD)
        accepting_travel(line);

    else if(line[1]==FINISH_TRAVEL_WORD)
        finish_travel(line);

    else
        cout<<BAD_REQUEST_ERROR<<'\n';
}

void Input::print_sorted_trips()
{
    vector <Trip> copy_trips;
    for(int count=0;count<trips.size();count++)
    {
        Trip cur_trip(trips[count]);
        copy_trips.push_back(cur_trip);
    }
    sort(copy_trips.begin(),copy_trips.end(),
         [](Trip a, Trip b)
    {
        return a.trip_price_getter() > b.trip_price_getter();
    });

    for(int count=0;count<copy_trips.size();count++)
        copy_trips[count].print_details_of_trip();
    
}

void Input::display_trips(vector <string> line)
{
    string user_name=find_item_in_line(line,USERNAME_WORD);
    string sorting_status=find_item_in_line(line,SORT_COST_WORD);
    error_checking display_errors;
    try
    {   
        display_errors.not_finding_member_error(find_member(user_name));
        display_errors.check_command_size(trips.size(),0,"empty_field_type");
        display_errors.check_bool_vars_error(find_member(user_name)->is_passenger(),true,
                                             "permission_type");
        if(sorting_status==NOT_SORTING)
            for(int count=0;count<trips.size();count++)
                trips[count]->print_details_of_trip(); 
        else if(sorting_status==SORTING)
            print_sorted_trips();
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    }
}

void Input::display_wanted_trip(vector <string> line)
{
    string driver_name=find_item_in_line(line,USERNAME_WORD);
    int trip_id=stoi(find_item_in_line(line,ID_WORD));
    error_checking dispaly_errors;

    try
    {
        dispaly_errors.not_finding_member_error(find_member(driver_name));
        dispaly_errors.not_finding_trip_error(find_trip_by_id(trip_id));
        dispaly_errors.check_bool_vars_error(find_member(driver_name)->is_passenger(),true,
                                             "permission_type");

        find_trip_by_id(trip_id)->print_details_of_trip();
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    }
}

double Input::total_price(Locations* loc1,Locations* loc2,string in_hurry_status)
{
    double dist=110.5*sqrt(pow(loc2->latitude_getter()-loc1->latitude_getter(),2)+
                           pow(loc2->longitude_getter()-loc1->longitude_getter(),2));
    double price=dist*(loc1->traffic_getter()+loc2->traffic_getter())*10000;
    if (in_hurry_status==IS_IN_HURRY)
        price=price*1.2;
    return price;
}

void Input::calculate_cost(vector <string> line)
{
    string passenger_name=find_item_in_line(line,USERNAME_WORD);
    string origin=find_item_in_line(line,ORIGIN_WORD);
    string destination=find_item_in_line(line,DESTINATION_WORD);
    string in_hurry=find_item_in_line(line,HURRY_WORD);
    error_checking calculate_errors;
    try
    {
        calculate_errors.not_finding_member_error(find_member(passenger_name));
        calculate_errors.not_finding_place_error(finding_place(origin));
        calculate_errors.not_finding_place_error(finding_place(destination));
        calculate_errors.check_bool_vars_error(find_member(passenger_name)->is_passenger(),false,
                                               "permission_type");
        calculate_errors.check_command_size(line.size(),11,"request_type");

        double total_cost=total_price(finding_place(origin),finding_place(destination),in_hurry);
        cout<<fixed<<setprecision(2)<<total_cost<<'\n';
    }
    catch(Local_runtime_error &ex)
    {
        cout<<ex.error_message()<<'\n';
    } 
}

void Input::get_commands_process(vector <string> line)
{
    if(line[1]==TRIPS_COMMAND_WORD)
    {
        string display_type=find_item_in_line(line,SORT_COST_WORD);
        if(display_type!="NULL")
            display_trips(line);
        else if(display_type=="NULL")
            display_wanted_trip(line);
    }
    else if(line[1]==GETTING_COST_WORD)
        calculate_cost(line);
    else
        cout<<BAD_REQUEST_ERROR<<'\n';
}

void Input::delete_commands_process(vector <string> line)
{
    if(line[1]==TRIPS_COMMAND_WORD)
    {
        string passeneger_name=find_item_in_line(line,USERNAME_WORD);
        int trip_id=stoi(find_item_in_line(line,ID_WORD));
        error_checking deleting_errors;

        try
        {
            deleting_errors.not_finding_trip_error(find_trip_by_id(trip_id));
            deleting_errors.not_finding_member_error(find_member(passeneger_name));
            deleting_errors.check_bool_vars_error(find_trip_by_id(trip_id)->
                                                  is_user_name_matched(passeneger_name),false,
                                                  "permission_type");
            deleting_errors.check_bool_vars_error(find_trip_by_id(trip_id)->is_trip_waiting(),false,
                                                  "request_type");
                                       
            delete trips[trip_id-1];
            trips.erase(trips.begin()+trip_id-1);
            find_member(passeneger_name)->change_trip_status("end");
            cout<<SUCCSESS_MESSAGE<<'\n';
        }
        catch(Local_runtime_error &ex)
        {
            cout<<ex.error_message()<<'\n';
        }
    }
    else 
        cout<<BAD_REQUEST_ERROR<<'\n';
}

Input::~Input()
{
    for(int count=0;count<members.size();count++)
        delete members[count];

    for(int count=0;count<trips.size();count++)
        delete trips[count];

    for(int count=0;count<available_locations.size();count++)
        delete available_locations[count];
}
