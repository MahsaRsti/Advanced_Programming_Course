#include "ref.hh"

using namespace std;

const int ALLOWED_BORROWING_TIME=5;
const int FIRST_THREE_DAYS_PENALTY=5000;
const int AFTER_THIRD_DAY_PENALTY=7000;

Reference::Reference(string reference_title, int _copies): Document(reference_title,_copies)
{
}

int Reference::calculate_penalty(int return_time,int borrowing_time)
{
    int delay=return_time-borrowing_time;
    if(delay<=ALLOWED_BORROWING_TIME)
        return 0;
    else
    {
        int main_delay=delay-ALLOWED_BORROWING_TIME;
        if(main_delay<=3)
            return main_delay*FIRST_THREE_DAYS_PENALTY;
        else 
            return 3*FIRST_THREE_DAYS_PENALTY+(main_delay-3)*AFTER_THIRD_DAY_PENALTY;
    }
}

bool Reference::extend_after_penalty(int borrowing_time,int cur_time)
{
    if(cur_time>borrowing_time+ALLOWED_BORROWING_TIME)
        return true;
    else
        return false;
}

int Reference::update_borrow_time_except_magazines(int borrowing_time)
{
    return borrowing_time+ALLOWED_BORROWING_TIME;
}