#include "book.hh"

using namespace std;

const int ALLOWED_BORROWING_TIME=10;
const int FIRST_SEVEN_DAYS_PENALTY=2000;
const int SECOND_FOURTEEN_DAYS_PENALTY=3000;
const int AFTER_TWENTY_FIRST_DAY_PENALTY=5000;

Book::Book(string book_title, int _copies): Document(book_title,_copies)
{
}

int Book::calculate_penalty(int return_time,int borrowing_time)
{
    int delay=return_time-borrowing_time;
    if(delay<=ALLOWED_BORROWING_TIME)
        return 0;
    else
    {
        int main_delay=delay-ALLOWED_BORROWING_TIME;
        if(main_delay<=7)
            return main_delay*FIRST_SEVEN_DAYS_PENALTY;
        else if(8<=main_delay<=21)
            return 7*FIRST_SEVEN_DAYS_PENALTY+(main_delay-7)*SECOND_FOURTEEN_DAYS_PENALTY;
        else if(main_delay>21)
            return 7*FIRST_SEVEN_DAYS_PENALTY+14*SECOND_FOURTEEN_DAYS_PENALTY+
                   (main_delay-21)*AFTER_TWENTY_FIRST_DAY_PENALTY;
    }
}

bool Book::extend_after_penalty(int borrowing_time,int cur_time)
{
    if(cur_time>borrowing_time+ALLOWED_BORROWING_TIME)
        return true;
    else
        return false;
}

int Book::update_borrow_time_except_magazines(int borrowing_time)
{
    return borrowing_time+ALLOWED_BORROWING_TIME;
}