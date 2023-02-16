#ifndef __PASSENGER_HH__
#define __PASSENGER_HH__

#include "person.hpp"
#include <vector>
#include <string>

class Passenger :public Person
{
    public:
            Passenger(std::string name,std::string role);   
            void change_trip_status(std::string status);
            bool is_in_trip(){return travelling;}
    private:
            bool travelling;
};

#endif