#include "person.hh"
#include "document.hh"
#include <iostream>

using namespace std;

const string EXTEND_IN_BORROING_DAY_ERROR="You can't extend and borrow a document on the same day";
const string EXTEND_AFTER_PENALTY_ERROR="You can't renew a document after receiving a penalty";
const string REACH_EXTEND_LIMIT_ERROR="You can't renew a document more than two times";
const string NOT_HAVING_DOC_ERROR="You have not borrowed this document";
const string MAGAZINE_ERROR="You can't renew magazines";
const int NOT_RETURNED=0;
const int RETURNED=1;

Person::Person(string _person_name)
{
    person_name=_person_name;
    num_of_person_docs=0;
}
bool Person::does_have_this_doc_now(string title)
{
    for(int count=0;count<person_docs.size();count++)
    {
        if(title==person_docs[count]->name_of_doc() && returning_status_of_each_doc[count]==
            NOT_RETURNED)
            return true;
    }
    return false;
}

void Person::print_error_and_exit(string error)
{
    cout<<error<<'\n';
    exit(EXIT_SUCCESS);
}

void Person::update_mem_docs_info(Document *new_doc,int cur_time)
{
    person_docs.push_back(new_doc);
    borrowing_times.push_back(cur_time);
    returning_status_of_each_doc.push_back(NOT_RETURNED);
    each_doc_penalty.push_back(0);
    extend_times_of_each_doc.push_back(0);
    num_of_person_docs++;
}

int Person::how_much_penalty(int cur_time)
{
    int cur_penalty=0;
    for(int count=0;count<person_docs.size();count++)
    {
        if(returning_status_of_each_doc[count]==RETURNED)
            cur_penalty+=each_doc_penalty[count];
        else
            cur_penalty+=person_docs[count]->calculate_penalty(cur_time,borrowing_times[count]);
    }
    return cur_penalty;
}

void Person::returning_doc_process(string document_title,int return_time)
{
    int doc_existence=0;
    for(int count=0;count<person_docs.size();count++)
    {
        if(document_title==person_docs[count]->name_of_doc() && returning_status_of_each_doc[count]==
           NOT_RETURNED)
        {
            doc_existence=1;
            each_doc_penalty[count]=person_docs[count]->calculate_penalty
                                                        (return_time,borrowing_times[count]);
            returning_status_of_each_doc[count]=RETURNED;
            num_of_person_docs--;
            break;
        }
    }
    if(doc_existence==0)
        print_error_and_exit(NOT_HAVING_DOC_ERROR);
}

void Person::check_extending_error(string document_title,int cur_time)
{
    int doc_existence=0;
    for(int count=0;count<person_docs.size();count++)
    {
        if(document_title==person_docs[count]->name_of_doc() && returning_status_of_each_doc[count]==
           NOT_RETURNED)
        {
            doc_existence=1;
            if(person_docs[count]->extending_in_borrowing_day(cur_time,borrowing_times[count]))
                print_error_and_exit(EXTEND_IN_BORROING_DAY_ERROR);

            if(person_docs[count]->extend_after_penalty(borrowing_times[count],cur_time))
                print_error_and_exit(EXTEND_AFTER_PENALTY_ERROR);

            if(person_docs[count]->reach_num_of_using_extend(extend_times_of_each_doc[count]))
                print_error_and_exit(REACH_EXTEND_LIMIT_ERROR);

            break;
        }
    }
    if(doc_existence==0)
        print_error_and_exit(NOT_HAVING_DOC_ERROR);
}

void Person::extend(string document_title)
{
    for(int count=0;count<person_docs.size();count++)
    {
        if(document_title==person_docs[count]->name_of_doc() && returning_status_of_each_doc[count]==
           NOT_RETURNED)
        {
            int update_borrowing_time=person_docs[count]->update_borrow_time_except_magazines
                                                          (borrowing_times[count]);
            if(update_borrowing_time==-1)
                print_error_and_exit(MAGAZINE_ERROR);
            else
            {
                borrowing_times[count]=update_borrowing_time;
                extend_times_of_each_doc[count]++;
            }
        }
    }
}