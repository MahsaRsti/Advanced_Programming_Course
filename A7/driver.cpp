#include "driver.hpp"

using namespace std;

Driver::Driver(string name,string role):Person(name,role)
{
}

void Driver::change_trip_status(string status)
{
    if(status=="accept")
        in_trip=true;
    else if(status=="finish")
        in_trip=false;
}