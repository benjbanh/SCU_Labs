/*
 * @author: Benjamin Banh
 * CSEN 79 Lab 4 Driver code
 */
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "roster.h"

using namespace std;
using namespace csen79;

// Test code for class roster
// Input file: <CMD> [ID] [FIRST LAST]
// CMD : A | X | L
// ID: 7-digit unsigned integer
// FIRST, LAST: string
int main() {
	Roster r;
	Student::ID_t id;
	string cmd, first, last;

	// Read cmd first, then branch accordingly
	// cout << "(A)dd/(X)Remove/(L)ist" << endl;
	while (cin >> cmd) {
		if (cmd == "A") {
			cin >> id;
			cin >> first;
			cin >> last;
			Student s = Student(id, first, last);
			r.insert(s);
			// cout << s;
		} else if (cmd == "X") {
			cin >> id;
			r.erase(id);
		} else if (cmd == "L") {
			// this should just work, if you did your begin/end/next correctly
			int i = 1;
			for (auto st = r.begin(); st != r.end(); st = r.next(st), i++){
				cout << i << ": " << *st;
			}
		} 
	}
	return EXIT_SUCCESS;
}

