/*
 * benjamin Banh bbanh@scu.edu
 */
 
#include <iostream>
#include <stdexcept>
#include "roster.h"

namespace csen79 {

	std::ostream& operator<<(std::ostream& os, const Student &t){
		os << t.id << " " << t.first_name << " " << t.last_name << std::endl;
		return os;
	}

	Roster::Roster(void) {size = 0; head=nullptr; tail=nullptr;}
	
	void Roster::insert(Student* s){
    	if (head == nullptr){
        	head = s;
        	tail = s;
    	} 
	else {
        	tail->next(s);
        	tail = s;
    	}
    	size++;
	}	

	void Roster::erase(Student::ID_t id){
    Student* curr = head;
    Student* prev = nullptr;

    while (curr != nullptr){
        if (curr->id == id){
            if (prev){
                prev->next(curr->next());
            } 

	    else {
                head = curr->next();
            }

            if (tail == curr) {
                tail = prev; 
            }

            delete curr;
            size--;
            return;
        }
        prev = curr;
        curr = curr->next();
    }
}


	//returns a pointer to the first record of the roster data
	Student* Roster::begin(){
		return head;

	}

	//returns last student
	Student* Roster::end(){
		return tail->next();
	}

	//returns next student
	Student* Roster::next(Student* current){
		return current->next();
	}

}
