#ifndef __PERSON_HH__
#define __PERSON_HH__

#include <vector>
#include <string>

class Person
{
    public:
        Person(std::string User_name,std::string Role);
        bool member_existence(std::string User_name);
        virtual void change_trip_status(std::string status)=0;
        bool is_passenger();
        virtual bool is_in_trip()=0;
        
    private:
        std::string user_name;
        std::string role;
};

#endif