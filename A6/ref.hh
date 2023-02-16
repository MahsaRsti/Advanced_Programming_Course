#ifndef __REF_HH__
#define __REF_HH__

#include "document.hh"

class Reference :public Document
{
    public:
        Reference(std::string reference_title, int copies);
        int calculate_penalty(int return_time,int borrowing_time);
        bool extend_after_penalty(int borrowing_time,int cur_time);
        int update_borrow_time_except_magazines(int borrowing_time);
};

#endif