/*
 * @Author: Benjamin Banh
 * Lab 4
 * 
 * Function definitions for the Roster class
 */
#include <iostream>
#include <stdexcept>
#include "roster.h"

namespace csen79 {
	std::ostream& operator<<(std::ostream& os, const Student &t) {
		os << t.id << " " << t.first_name << " " << t.last_name << std::endl;
		return os;
	}

	Roster::Roster(void) : size(0), CAPACITY(30), arr(new T[CAPACITY]) {}    //constructor

    Roster::~Roster() {delete[] arr;}                   //destructor
	
	void Roster::insert(T &rec) {
		if (size >= CAPACITY) {
			// Allocate new memory block when CAPACITY is exhausted
			CAPACITY *= 2;
			T* newRoster = new T[CAPACITY];
			for (int i = 0; i < size; ++i) {
				newRoster[i] = arr[i];
			}
			// Deallocate old memory
			delete[] arr;
			// Point roster to the new memory block
			arr = newRoster;
		}
		arr[size] = rec;
		size++; 
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

	// The function begin() will return a pointer to the first record of the roster data
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
