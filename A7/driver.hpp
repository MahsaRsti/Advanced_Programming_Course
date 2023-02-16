#ifndef __DRIVER_HH__
#define __DRIVER_HH__

#include "person.hpp"
#include <vector>
#include <string>


class Driver :public Person
{
     public:
          Driver(std::string name,std::string role);  
          void change_trip_status(std::string status);
          bool is_in_trip(){return in_trip;}

     private:
          bool in_trip;
          
};


#endif