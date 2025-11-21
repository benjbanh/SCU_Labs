/*
 * CSEN 79 Lab Sample Code
 */
#include <iostream>
#include <stdexcept>
#include "roster.h"

namespace csen79 {
	std::ostream& operator<<(std::ostream& os, const Student &t) {
		os << t.id << " " << t.first_name << " " << t.last_name << std::endl;
		return os;
	}

	Roster::Roster(void) {count = 0; size = 0;}
	
	// state your pre-/post-conditions
	void Roster::insert(T &rec) {
		if (size < 30) {
			arr[size++] = rec;
		}
	}

	// state your pre-/post-conditions
	void Roster::erase(Student::ID_t id) {
		for (int i = 0; i < size; i++){
			if(arr[i].id == id){
				arr[i] = arr[size-1];
				size--;
				break;
			}
		}
	}

	// // The function begin() will return a pointer to the first record of the roster data
	Student* Roster::begin() {
		if (size > 0) {
			return &arr[0];
		} 
		else {
			return nullptr;
		}

	}

	//Last student
	Student* Roster::end() {
		if (size > 0) {
			return &arr[size];
		} 
		else {
			return nullptr;
		}
	}

	//Next student
	Student* Roster::next(Student* current) {
		if (current >= end() - 1) return end();
		return current + 1;
	}

}
