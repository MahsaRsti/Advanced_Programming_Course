#include "document.hh"

using namespace std;

const int EXTEND_LIMIT=2;

Document::Document(string _doc_name, int _copies)
{
    doc_name=_doc_name;
    copies=_copies;
}

bool Document::does_copies_become_zero()
{
    if (copies==0)
        return true;
    return false;
}

bool Document::extending_in_borrowing_day(int cur_time,int borrowing_time)
{
    if(borrowing_time==cur_time)
        return true;
    return false;
}

bool Document::reach_num_of_using_extend(int extend_time_of_doc)
{
    if(extend_time_of_doc==EXTEND_LIMIT)
        return true;
        
    return false;
}