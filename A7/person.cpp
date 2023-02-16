#include "person.hpp"

using namespace std;


Person::Person(string User_name,string Role)
{
    user_name=User_name;
    role=Role;
}

bool Person::member_existence(string User_name)
{
    if(user_name==User_name)
        return true;
    return false;
}

bool Person::is_passenger()
{
    if(role=="passenger")
        return true;
    return false;
}