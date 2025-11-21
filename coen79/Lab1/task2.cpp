#include <iostream>
#include <iomanip>
#include <string>
/* Given the input 0123456789, print the pattern below:
9876543210 0123456789
  9876543210 0123456789
    9876543210 0123456789
      9876543210 0123456789
        9876543210
  */
int main() {
    std::string input;
    std::cout << "Enter input string: ";
    std::getline(std::cin, input); // Use std::getline() to read the whole line

    int length = input.length();
    std::string reversed;
    
    // Reverse the input string and save result to reversed
    for (int j = length - 1; j >= 0; --j) {
        reversed += input[j];
    }
    
    std::string line;
    int i = 1;
    // Use checks number of times to be printed
    while (i <= length) { 
        //prints input
	if (i % 2 == 0) {
            line += input;
            line += "\n";
            std::cout << std::setw(2*length + 1) << std::setfill(' ') << line;
            line = "";
        }
	//adds reversed to printed string
        else {
            std::string repeatedString(i-1, ' ');
            line += repeatedString;
            line += reversed;
            line += " ";
        }
        i++;
    }

    return 0;
}

