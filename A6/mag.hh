#ifndef __MAG_HH__
#define __MAG_HH__

#include "document.hh"

class Magazine :public Document
{
    public:
        Magazine(std::string magazine_title, int _year, int _number, int _copies);
        int calculate_penalty(int return_time,int borrowing_time);
        bool extend_after_penalty(int borrowing_times,int cur_time);
        int update_borrow_time_except_magazines(int borrowing_time);

    private:
        int year;
        int number;
};
#endif