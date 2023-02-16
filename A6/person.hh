#ifndef __PERSON_HH__
#define __PERSON_HH__

#include <vector>
#include <string>
class Document;
class Person
{
    protected:
        int num_of_person_docs;

    public:
        Person(std::string _person_name);
        std::string name_of_person(){return person_name;}
        bool does_have_this_doc_now(std::string title);
        virtual bool is_max_been_reached()=0;
        void update_mem_docs_info(Document *new_doc,int cur_time);
        int how_much_penalty(int cur_time);
        void returning_doc_process(std::string document_title,int cur_time);
        void check_extending_error(std::string document_title,int cur_time);
        void extend(std::string document_title);
        
    private:
        void print_error_and_exit(std::string error);
        std::string person_name;
        std::vector <Document*> person_docs;
        std::vector <int> borrowing_times;
        std::vector <int> extend_times_of_each_doc;
        std::vector <int> each_doc_penalty;
        std::vector <int> returning_status_of_each_doc;
};

#endif