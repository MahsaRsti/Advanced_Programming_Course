#ifndef __STUDENT_HH__
#define __STUDENT_HH__

#include "person.hh"

class Student :public Person
{
    public:
        Student(std::string student_id, std::string student_name);
        bool is_max_been_reached();

    private:
        std::string _student_id;
};

#endif