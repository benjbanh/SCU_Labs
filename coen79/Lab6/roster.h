/*
 * Benjamin Banh bbanh@scu.edu
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
			friend std::ostream& operator<<(std::ostream& os, const Student &);
			
			Student* next(void){return next_node;}
			void next(Student* node){next_node = node;}

			ID_t id;
		private:	
			std::string first_name;
			std::string last_name;
			Student* next_node;
	};

	class Roster {
		public:
			using T = Student;
						using ID_t = unsigned int;	//delete this line
			Roster(void);	//constructor

			void insert(Student* s);
			void erase(Student::ID_t id);

			T* begin(void);
			T* end(void);
			T* next(Student* current);

		private:
			int size;
			T* head;
			T* tail;
		};
}
#endif // ROSTER_H
