#include "student.hh"

using namespace std;

const int STUDENT_ALLOWED_DOCS=2;

Student::Student(string student_id,string student_name): Person(student_name)
{
    _student_id=student_id;
}

bool Student::is_max_been_reached()
{
    if(num_of_person_docs==STUDENT_ALLOWED_DOCS)
        return true;
    return false;
}