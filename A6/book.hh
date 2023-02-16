#ifndef __BOOK_HH__
#define __BOOK_HH__

#include "document.hh"

class Book :public Document
{
    public:
        Book(std::string book_title, int _copies);
        int calculate_penalty(int return_time,int borrowing_time);
        bool extend_after_penalty(int borrowing_time,int cur_time);
        int update_borrow_time_except_magazines(int borrowing_time);

};

#endif