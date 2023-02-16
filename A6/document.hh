#ifndef __DOCUMENT_HH__
#define __DOCUMENT_HH__

#include <string>

class Document
{
    public:
        Document(std::string _doc_name, int _copies);
        std::string name_of_doc(){return doc_name;}
        bool does_copies_become_zero();
        void decrease_num_of_copies(){copies--;}
        void increase_num_of_copies(){copies++;}
        virtual int calculate_penalty(int return_time,int borrowing_time)=0;
        bool extending_in_borrowing_day(int cur_time,int borrowing_time);
        virtual bool extend_after_penalty(int borrowing_times,int cur_time)=0;
        bool reach_num_of_using_extend(int extend_times_of_doc);
        virtual int update_borrow_time_except_magazines(int borrowing_time)=0;

    private:
        std::string doc_name;
        int copies;
        
};

#endif
