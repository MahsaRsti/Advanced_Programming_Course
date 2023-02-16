#include "passenger.hpp"

using namespace std;

Passenger::Passenger(string name,string role):Person(name,role)
{
}

void Passenger::change_trip_status(string status)
{
    if(status=="start")
        travelling=true;
    else if(status=="end")
        travelling=false;
}