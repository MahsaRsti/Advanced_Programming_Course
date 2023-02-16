#include <iostream>
#include "Library.hh"
#include "person.hh"
#include "document.hh"
#include "student.hh"
#include "prof.hh"
#include "book.hh"
#include "mag.hh"
#include "ref.hh"

using namespace std;

const string READDING_PERSON_ERROR="Name already exists";
const string EMPTY_FIELD_ERROR="Empty field";
const string READDING_DOC_ERROR="A document with specified name already exists";
const string NUMBER_ERROR="Invalid number";
const string YEAR_ERROR="Invalid year";
const string DOC_EXISTENCE_ERROR="This document does not exist";
const string REBORROWING_ERROR="You borrowed this document alsready";
const string MAX_BORROWING_ERROR="Maximum number of allowed borrows exceeded";
const string DAYS_ERROR="Invalid day";

Person* Library::find_person(string person_name)
{
    Person* dummy;
    for(int count=0;count<people.size();count++)
    {
        if(person_name==people[count]->name_of_person())
            return people[count];
    }
    return dummy;
}

Document* Library::find_doc(string title)
{
    Document* dummy;
    for(int count=0;count<documents.size();count++)
    {
        if(title==documents[count]->name_of_doc())
            return documents[count];
    }
    return dummy;
}

void Library::time_pass(int days)
{
    if(days<=0)
        print_error_and_exit(DAYS_ERROR);
    else
        time+=days;
}

bool Library::did_person_add_before(string name)
{
    for(int count=0;count<people.size();count++)
    {
        if(name==people[count]->name_of_person())
            return true;
    }
    return false;
}

void Library::print_error_and_exit(string error)
{
    cout<<error<<'\n';
    delete_library();
    exit(EXIT_SUCCESS);
}

void Library::add_student_member(string student_id,string student_name)
{
    if(did_person_add_before(student_name))
        print_error_and_exit(READDING_PERSON_ERROR);

    if(student_id=="" || student_name=="")
        print_error_and_exit(EMPTY_FIELD_ERROR);

    Student *cur_student=new Student(student_id,student_name);
    people.push_back(cur_student);
}

void Library::add_prof_member(string prof_name)
{
    if(did_person_add_before(prof_name))
        print_error_and_exit(READDING_PERSON_ERROR);

    if(prof_name=="")
        print_error_and_exit(EMPTY_FIELD_ERROR);

    Professor *cur_prof=new Professor(prof_name);
    people.push_back(cur_prof);
}

bool Library::did_document_add_before(string title)
{
    for(int count=0;count<documents.size();count++)
    {
        if(title==documents[count]->name_of_doc())
            return true;   
    }
    return false;
}

void Library::add_book(string book_title, int copies)
{
    if(did_document_add_before(book_title))
        print_error_and_exit(READDING_DOC_ERROR);

    if(book_title=="")
        print_error_and_exit(EMPTY_FIELD_ERROR);

    Book *cur_book=new Book(book_title,copies);
    documents.push_back(cur_book);
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
    if(did_document_add_before(magazine_title))
        print_error_and_exit(READDING_DOC_ERROR);

    if(magazine_title=="")
        print_error_and_exit(EMPTY_FIELD_ERROR);

    if(year<=0)
        print_error_and_exit(YEAR_ERROR);

    if(number<=0)
        print_error_and_exit(NUMBER_ERROR);

    Magazine *cur_mag=new Magazine(magazine_title,year,number,copies);
    documents.push_back(cur_mag);
}

void Library::add_reference(string reference_title, int copies)
{
    if(did_document_add_before(reference_title))
        print_error_and_exit(READDING_DOC_ERROR);

    if(reference_title=="")
        print_error_and_exit(EMPTY_FIELD_ERROR);

    Reference *cur_ref=new Reference(reference_title,copies);
    documents.push_back(cur_ref);
}

void Library::borrow(string member_name,string document_title)
{
    if(did_document_add_before(document_title)==false || find_doc(document_title)->
                                                                  does_copies_become_zero())
        print_error_and_exit(DOC_EXISTENCE_ERROR);

    if(find_person(member_name)->does_have_this_doc_now(document_title))
        print_error_and_exit(REBORROWING_ERROR);

    if(find_person(member_name)->is_max_been_reached())
        print_error_and_exit(MAX_BORROWING_ERROR);
    
    find_doc(document_title)->decrease_num_of_copies();
    find_person(member_name)->update_mem_docs_info(find_doc(document_title),time);
}

int Library::get_total_penalty(string member_name)
{
    return find_person(member_name)->how_much_penalty(time);
}

void Library::return_document(string member_name,string document_title)
{
    find_person(member_name)->returning_doc_process(document_title,time);
    find_doc(document_title)->increase_num_of_copies();
}

void Library::extend(string member_name,string document_title)
{
    find_person(member_name)->check_extending_error(document_title,time);
    find_person(member_name)->extend(document_title);
}

vector<string> Library::available_titles()
{
    vector <string> available_docs;
    for(int count=0;count<documents.size();count++)
    {
        if(documents[count]->does_copies_become_zero()==false)
        {
            available_docs.push_back(documents[count]->name_of_doc());
            cout<<documents[count]->name_of_doc()<<'\n';
        }
    }
    return available_docs;
}

void Library::delete_library()
{
    for(int count=0;count<people.size();count++)
        delete people[count];

    for(int count=0;count<documents.size();count++)
        delete documents[count];
}