#ifndef __PROF_HH__
#define __PROF_HH__

#include "person.hh"

class Professor :public Person
{
    public:
        Professor(std::string prof_name);
        bool is_max_been_reached();
};

#endif