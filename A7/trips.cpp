#include "trips.hpp"
#include <iostream>

using namespace std;

Trip::Trip(string Applicator,string Origin,string Destination,int id,double price)
{
    user_name=Applicator;
    origin=Origin;
    destination=Destination;
    trip_id=id;
    status=WATING_STATUS;
    trip_price=price;
}

Trip::Trip(const Trip* trip)
{
    user_name=trip->user_name;
    origin=trip->origin;
    destination=trip->destination;
    trip_id=trip->trip_id;
    status=trip->status;
    trip_price=trip->trip_price;
}

void Trip::print_details_of_trip()
{
    cout<<trip_id<<' '<<user_name<<' '<<origin<<' '<<destination<<' '<<trip_price<<' '<<status<<'\n';
}

bool Trip::is_id_matched(int id)
{
    if(trip_id==id)
        return true;
    return false;
}

bool Trip::is_user_name_matched(string name)
{
    if(user_name==name)
        return true;
    return false;
}

bool Trip::is_driver_name_matched(string driver_name)
{
    if(assigned_driver==driver_name)
        return true;
    return false;
}

bool Trip::is_trip_waiting()
{
    if(status==WATING_STATUS)
        return true;
    return false;
}

void Trip::change_status(string new_status)
{
    status=new_status;
}

void Trip::assign_driver(string driver_name)
{
    assigned_driver=driver_name;
}