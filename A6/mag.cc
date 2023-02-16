#include "mag.hh"

using namespace std;

const int YEAR_OF_CHANGING_PENALTY=1390;
const int ALLOWED_BORROWING_TIME=2;
const int BEFORE_CHANGING_YEAR_PENALTY=2000;
const int AFTER_CHANGING_YEAR_PENALTY=3000;

Magazine::Magazine(string magazine_title, int _year, int _number, int _copies)
                   : Document(magazine_title,_copies)
{
    year=_year;
    number=_number;
}

int Magazine::calculate_penalty(int return_time,int borrowing_time)
{
    int delay=return_time-borrowing_time;
    if(delay<=ALLOWED_BORROWING_TIME)
        return 0;
    else
    {
        if(year<=YEAR_OF_CHANGING_PENALTY)
            return (delay-ALLOWED_BORROWING_TIME)*BEFORE_CHANGING_YEAR_PENALTY;
        else
            return (delay-ALLOWED_BORROWING_TIME)*AFTER_CHANGING_YEAR_PENALTY;
    }
}

bool Magazine::extend_after_penalty(int borrowing_times,int cur_time)
{
    if(cur_time>borrowing_times+ALLOWED_BORROWING_TIME)
        return true;
    else
        return false;
}

int Magazine::update_borrow_time_except_magazines(int borrowing_time)
{
    return -1;
}