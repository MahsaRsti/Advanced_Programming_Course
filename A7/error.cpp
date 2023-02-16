#include "error.hpp"

using namespace std;

bool error_checking::not_finding_trip_error(Trip* wanted_trip)
{
    if(wanted_trip==NULL)
        throw Not_found_error(NOT_FOUND_ERROR_MESSAGE);
    return true;
}

bool error_checking::not_finding_member_error(Person* user_name)
{
    if(user_name==NULL)
        throw Not_found_error(NOT_FOUND_ERROR_MESSAGE);
    return true;
}

bool error_checking::not_finding_place_error(Locations* place)
{
    if(place==NULL)
        throw Not_found_error(NOT_FOUND_ERROR_MESSAGE);
    return true;
}

bool error_checking::check_command_size(int command_size,int suitable_command_size,string _error_type)
{
    if(command_size!=suitable_command_size)
    {
        if(_error_type=="request_type")
            throw Bad_requesting(BAD_REQUEST_ERROR);
        else if(_error_type=="empty_field_type")
        {
            if(command_size==suitable_command_size)
                throw Empty_error(EMPTY_ERROR_MESSAGE);
        }
    }
    return true;
}

bool error_checking::check_bool_vars_error(bool var_value,bool var_value_checker,string _error_type)
{
    if(var_value==var_value_checker)
    {
        if(_error_type=="request_type")
            throw Bad_requesting(BAD_REQUEST_ERROR);
        else if(_error_type=="permission_type")
            throw Permission_denying(PERMISSION_ERROR_MESSAGE);
    }
    return true;
}

bool error_checking::check_first_command(string command)
{
    if(command==POST_WORD || command==GET_WORD || command==DELETE_WORD)
        return true;
    else
        throw Bad_requesting(BAD_REQUEST_ERROR);
}

bool error_checking::check_sign_up_errors(Person *new_member,string role)
{
    if(new_member==NULL && (role==PASSENGER_WORD || role==DRIVER_WORD))
        return true;
    else
        throw Bad_requesting(BAD_REQUEST_ERROR);
}














