#include "prof.hh"

using namespace std;

const int PROF_ALLOWED_DOCS=5;

Professor::Professor(string prof_name): Person(prof_name)
{
}

bool Professor::is_max_been_reached()
{
    if(num_of_person_docs==PROF_ALLOWED_DOCS)
        return true;
    return false;
}