#include "mystring.h"
#include <iostream>

using namespace coen79_lab5;
using std::cout;
using std::cin;
using std::endl;

int main() {
    string s1, s2("Hello, World!"), s3("Hello, World!");

    // Tests for += operator
    cout << "*** += operator tests ***" << endl;
    cout << "s1 length: " << s1.length() << endl;
    s1 += 'A';
    cout << "s1: " << s1 << endl;
    cout << "s1 length: " << s1.length() << endl;
    s1 += 'B';
    cout << "s1: " << s1 << endl;
    cout << "s1 length: " << s1.length() << endl;
    s1 += 'C';
    cout << "s1: " << s1 << endl;
    cout << "s1 length: " << s1.length() << endl;

    // Test for [] operator
    cout << "*** [] operator test ***" << endl;
    cout << "s1[0]: " << s1[0] << endl;
    cout << "s1[1]: " << s1[1] << endl;
    cout << "s1[2]: " << s1[2] << endl;

    // Tests for = operator
    cout << "*** = operator test ***" << endl;
    s2 = "Test 1 Success";
    cout << "s2: " << s2 << endl;
    s2 = "Test 2 Success";
    cout << "s2: " << s2 << endl;

    // Logical operator tests
    cout << "*** logical operator tests ***" << endl;
    cout << "A == A: " << (string("A") == string("A")) << endl;
    cout << "A == B: " << (string("A") == string("B")) << endl;
    cout << "A != A: " << (string("A") != string("A")) << endl;
    cout << "A != B: " << (string("A") != string("B")) << endl;
    cout << "A > A: " << (string("A") > string("A")) << endl;
    cout << "A > B: " << (string("A") > string("B")) << endl;
    cout << "B > A: " << (string("B") > string("A")) << endl;
    cout << "A >= A: " << (string("A") >= string("A")) << endl;
    cout << "A >= B: " << (string("A") >= string("B")) << endl;
    cout << "B >= A: " << (string("B") >= string("A")) << endl;
    cout << "A < A: " << (string("A") < string("A")) << endl;
    cout << "A < B: " << (string("A") < string("B")) << endl;
    cout << "B < A: " << (string("B") < string("A")) << endl;
    cout << "A <= A: " << (string("A") <= string("A")) << endl;
    cout << "A <= B: " << (string("A") <= string("B")) << endl;
    cout << "B <= A: " << (string("B") <= string("A")) << endl;

    // + operator tests
    cout << "*** + operator tests ***" << endl;
    cout << "A + B: " << (string("A") + string("B")) << endl;
    cout << "A + C: " << (string("A") + string("C")) << endl;
    cout << "B + A: " << (string("B") + string("A")) << endl;

    // >> operator test
    cout << "*** >> operator test ***" << endl;
    string university;
    cout << "Please enter a word: ";
    cin >> university;
    cout << "You entered: " << university << endl;

    // Single character constructor test
    cout << "*** Single character constructor test ***" << endl;
    string c('C');
    cout << "C: " << c << endl;

    // Insert tests
    cout << "*** insert tests ***" << endl;
    s1 = "ABC";
    s1.insert(string("D"), 3);  // Inserting at the end
    cout << "s1: " << s1 << endl;
    s1.insert(string("-"), 0);  // Inserting at the beginning
    cout << "s1: " << s1 << endl;
    s1.insert(string("*"), 3);  // Inserting in the middle
    cout << "s1: " << s1 << endl;
    s1 += ".";
    cout << "s1: " << s1 << endl;

    // Deletion tests
    cout << "*** dlt tests ***" << endl;
    s1 = "1112233445555";
    cout << "s1: " << s1 << endl;
    s1.dlt(0, 3);  // Deleting '111'
    cout << "s1: " << s1 << endl;
    s1.dlt(2, 2);  // Deleting '33'
    cout << "s1: " << s1 << endl;
    s1.dlt(4, 6);  // Deleting '5555'
    cout << "s1: " << s1 << endl;

    // Replacement tests
    cout << "*** replace tests ***" << endl;
    s1 = "abc";
    cout << "s1: " << s1 << endl;
    s1.replace('z', 0);  // Replace 'a' with 'z'
    cout << "s1: " << s1 << endl;
    s1.replace('y', 1);  // Replace 'b' with 'y'
    cout << "s1: " << s1 << endl;
    s1.replace('x', 2);  // Replace 'c' with 'x'
    cout << "s1: " << s1 << endl;
    s1 = "123DEFGHIJKLMNOP";
    s1.replace(string("123"), 5);  // Replace 'FGH' with '123'
    cout << "s1: " << s1 << endl;
    s1.replace(string("123"), 13);  // Replace 'NOP' with '123'
    cout << "s1: " << s1 << endl;

    // Count tests
    cout << "*** count tests ***" << endl;
    s1 = "ABBCCCDDDD";
    cout << "s1: " << s1 << endl;
    cout << "Num A's: " << s1.count('A') << endl;
    cout << "Num B's: " << s1.count('B') << endl;
    cout << "Num C's: " << s1.count('C') << endl;
    cout << "Num D's: " << s1.count('D') << endl;
    cout << "Num E's: " << s1.count('E') << endl;

    // Search tests
    cout << "*** search tests ***" << endl;
    s1 = "ABBCCCDDDD";
    cout << "s1: " << s1 << endl;
    cout << "First A: " << s1.search('A') << endl;
    cout << "First B: " << s1.search('B') << endl;
    cout << "First C: " << s1.search('C') << endl;
    cout << "First D: " << s1.search('D') << endl;
    cout << "First E: " << s1.search('E') << endl;
    s1 = "ABCDEFGHIJKLMNOP";
    cout << "Location of \"ABC\": " << s1.search(string("ABC")) << endl;
    cout << "Location of \"GHI\": " << s1.search(string("GHI")) << endl;
    cout << "Location of \"NOP\": " << s1.search(string("NOP")) << endl;
    cout << "Location of \"XYZ\": " << s1.search(string("XYZ")) << endl;

    return 0;
}
