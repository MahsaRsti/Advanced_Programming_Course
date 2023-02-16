#ifndef __LIBRARY_HH__
#define __LIBRARY_HH__

#include <vector>
#include <string>

class Person;
class Document;

class Library {

	public:
		Library(){time=0;}
		void add_student_member(std::string student_id, std::string student_name);
		void add_prof_member(std::string prof_name);
		void add_book(std::string book_title, int copies);
		void add_magazine(std::string magazine_title, int year, int number, int copies);
		void add_reference(std::string reference_title, int copies);
		void borrow(std::string member_name, std::string document_title);
		void extend(std::string member_name, std::string document_title);
		void return_document(std::string member_name, std::string document_title);
		int get_total_penalty(std::string member_name);
		std::vector<std::string> available_titles();
		void time_pass(int days);
		void delete_library();
		
	private:
		bool did_person_add_before(std::string name);
		bool did_document_add_before(std::string title);
		void print_error_and_exit(std::string error);

		Person* find_person(std::string person_name);
		Document* find_doc(std::string doc_title);

		std::vector <Person*> people;
		std::vector <Document*> documents;
		int time;

};

#endif