#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
/*Convert to uppercase and display all the words from an input file with length of at least 10 characters. All punctuation marks are removed and do not contribute to the words' length. The name of the file to be read should be read in as a command line argument.*/


// Function to remove punctuation marks from a string
void removePunctuation(string &word) {
    for (char &c : word) {
        if (ispunct(c)) {
            c = ' ';
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if file name is provided as command line argument
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <file_name>" << endl;
        return 1;
    }

    // Open the file
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return 1;
    }

    string word;
    while (file >> word) {
        // Remove punctuation marks
        for (char &c : word) {
            if (ispunct(c)) {
                c = ' ';
            }
        }

        // Check if word length is at least 10 characters
        if (word.length() >= 10) {
	    //capitalize all characters
            for (char &c : word) {
                c = toupper(c);
            }
            // Print the word
            cout << word << endl;
        }
    }

    // Close the file
    file.close();

    return 0;
}


