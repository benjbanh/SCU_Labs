/*
 * Benjamin Banh bbanh@scu.edu 
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

    while (cin >> cmd) {
        if (cmd == "A") {
            cin >> id >> first >> last;
            Student* s = new Student(id, first, last); // Correctly allocate a new Student
            r.insert(s);
        } else if (cmd == "X") {
            cin >> id;
            r.erase(id);
        } else if (cmd == "L") {
            int i = 1;
            for (auto st = r.begin(); st != r.end(); st = r.next(st), i++) {
                cout << i << ": " << *st;
            }
        }
    }
    return EXIT_SUCCESS;
}


