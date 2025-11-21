#include <iostream>
#include <cctype>

/*Count the number of alphanumeric characters and non-alphanumeric characters from the standard input (cin). Spaces (‘ ‘) should not be counted toward either type of character*/
int main() {
    std::string input;
    std::getline(std::cin, input);

    int alphanumeric = 0;
    int non_alphanumeric = 0;

    for (char c : input) {
	//checks alphanumeric characters
        if (isalnum(c)) {
            alphanumeric++;
        } 
	//checks non-alphanumeric characters
	else if (!isspace(c)) {
            non_alphanumeric++;
        }
    }

    std::cout << "Alphanumeric characters: " << alphanumeric << std::endl;
    std::cout << "Non-alphanumeric characters: " << non_alphanumeric << std::endl;

    return 0;
}

