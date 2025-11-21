/*
 * @Author: Benjamin Banh
 * Lab 4
 * 
 * Function headers for the Roster class and the Student class
 */
#ifndef ROSTER_H
#define ROSTER_H

#include <string>

// Class declaration for roster
namespace csen79 {
	class Student {
		public:
			using ID_t = unsigned int;	// really should be a 7-digit unsigned int
			Student(ID_t n=0, std::string fn="", std::string ln=""): id{n}, first_name{fn}, last_name{ln} {};
			// Card(suit_t s=0, rank_t r=0): rank{r}, suit{s} {}


			friend std::ostream& operator<<(std::ostream& os, const Student &);
			ID_t id;
		private:	
			std::string first_name;
			std::string last_name;
	};

	class Roster {
		public:
			using T = Student;
			Roster(void);	//constructor
            ~Roster(void);	//constructor

			void insert(T &);
			void erase(Student::ID_t);

			T* begin(void);
			T* end(void);
			T* next(Student* current);

			int getSize(void){return size;}
			void modifySize(int i){size = i;}

		private:
			int size = 0;
            int CAPACITY=30;
			T* arr;
		};
}
#endif 
