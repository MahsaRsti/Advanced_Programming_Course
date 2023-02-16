#ifndef __TRIP_HH__
#define __TRIP_HH__

#include <vector>
#include <string>
#include "input.hpp"

class Trip
{
    public:
        Trip(std::string applicator,std::string origin,std::string destination,int id,double price);
        Trip(const Trip* trip);
        void print_details_of_trip();
        bool is_id_matched(int id);
        bool is_user_name_matched(std::string user_name);
        bool is_driver_name_matched(std::string driver_name);
        bool is_trip_waiting();
        void change_status(std::string new_status);
        void assign_driver(std::string driver);
        std::string passenger_is_needed(){return user_name;}
        double trip_price_getter(){return trip_price;}

    private:
        std::string user_name;
        std::string origin;
        std::string destination;
        int trip_id;
        std::string status;
        std::string assigned_driver;
        double trip_price;
};

#endif