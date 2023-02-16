#ifndef __ERROR_HH__
#define __ERROR_HH__

#include <vector>
#include <string>
#include <stdexcept>
#include "input.hpp"

const std::string BAD_REQUEST_ERROR="Bad Request";
const std::string NOT_FOUND_ERROR_MESSAGE="Not Found";
const std::string PERMISSION_ERROR_MESSAGE="Permission Denied";
const std::string EMPTY_ERROR_MESSAGE="Empty";

class Person;
class Trip;
class Locations;

class Local_runtime_error
{
     public:
        Local_runtime_error(std::string error_message){message=error_message;}
        std::string error_message(){return message;}

    private:
        std::string message;
};

class Bad_requesting :public Local_runtime_error
{
    public:
        Bad_requesting(std::string error_message):Local_runtime_error(error_message){}

};

class Not_found_error :public Local_runtime_error
{
    public:
        Not_found_error(std::string error_message):Local_runtime_error(error_message){}

};

class Permission_denying :public Local_runtime_error
{
    public:
        Permission_denying(std::string error_message):Local_runtime_error(error_message){}

};

class Empty_error :public Local_runtime_error
{
    public:
        Empty_error(std::string error_message):Local_runtime_error(error_message){}

};

class error_checking
{
    public:
        bool not_finding_trip_error(Trip* wanted_trip);
        bool not_finding_member_error(Person* user_name);
        bool not_finding_place_error(Locations* place);
        bool check_command_size(int command_size,int suitable_command_size,std::string _error_type);
        bool check_bool_vars_error(bool var_value,bool var_value_checker,std::string _error_type);
        bool check_first_command(std::string command);
        bool check_sign_up_errors(Person *new_member,std::string role);
};

#endif