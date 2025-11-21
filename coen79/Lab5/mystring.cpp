#include "mystring.h"
#include <cstring> 
#include <cassert>  

namespace coen79_lab5 {
   
    string::string(const char str[]){
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strcpy(characters, str);
    }

    
    string::string(char c){
        current_length = 1;
        allocated = 2;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }

  
    string::string(const string& source){
        current_length = source.current_length;
        allocated = source.allocated;
        characters = new char[allocated];
        strcpy(characters, source.characters);
    }

   
    string::~string(){
        delete[] characters;
    }

    
    string& string::operator =(const string& source){
        
        if (this == &source){
            return *this;
        } 
        char *new_data = new char[source.allocated];
        strcpy(new_data, source.characters);
        delete[] characters;
        characters = new_data;
        allocated = source.allocated;
        current_length = source.current_length;
        return *this;
    }


    void string::operator +=(const string& addend){
        size_t new_length = current_length + addend.current_length;
        reserve(new_length);
        strcat(characters, addend.characters);
        current_length = new_length;
    }

    void string::operator +=(const char addend[ ]){
        size_t new_length = current_length + (sizeof(addend) / sizeof(char));
        reserve(new_length);
        strcat(characters, addend);
        current_length = new_length;
    }

    void string::operator +=(char addend){
        reserve(1);
        strcat(characters, &addend);
        current_length += 1;
    }

 
    void string::reserve(size_t n){
        if (allocated < n){
            char *larger_array = new char[n];
            strcpy(larger_array, characters);
            delete[] characters;
            characters = larger_array;
            allocated = n;
        }
    }

   
    void string::insert(const string& source, unsigned int position) {
        assert(position <= current_length);
        size_t new_length = current_length + source.current_length;
        reserve(new_length + 1);

        for (size_t i = current_length; i >= position; --i){
            characters[i + source.current_length] = characters[i];
        }
        for (size_t i = 0; i < source.current_length; ++i){
            characters[position + i] = source.characters[i];
        }

        current_length = new_length;
        characters[current_length] = '\0';
    }

    void string::dlt(unsigned int position, unsigned int num){
        if ((position + num) >= current_length) {return;}
        for(int i = position; i < current_length - num; i++){
            characters[i] = characters[i + num];
        }
        current_length -= num;
        characters[current_length] = '\0';
    }
    
    void string::replace(char c, unsigned int position){
        if (position < current_length) {
            characters[position] = c;
        }
    }
    
    void string::replace(const string& source, unsigned int position){
        if (position + source.current_length <= current_length) {
            for (int i = 0; i < source.current_length; ++i) {
                characters[position + i] = source.characters[i];
            }
        } 
    }

    char string::operator[](size_t position) const {
        assert(position < current_length);
        return characters[position];
    }

   
    int string::search(char c) const {
        for (size_t i = 0; i < current_length; ++i){
            if (characters[i] == c) return static_cast<int>(i);
        }
        return -1; 
    }

    int string::search(const string& substring) const {
        if (substring.current_length == 0) {return 0;}

        for (int i = 0; i <= current_length - substring.current_length; ++i) {
            bool match = true;
            for (int j = 0; j < substring.current_length; ++j) {
                //check if match
                if (characters[i + j] != substring.characters[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
        return -1;
    }


    
    unsigned int string::count(char c) const {
        unsigned int count = 0;
        for (size_t i = 0; i < current_length; ++i){
            if (characters[i] == c) ++count;
        }
        return count;
    }

   
    std::ostream& operator<<(std::ostream& outs, const string& source){
        outs << source.characters;
        return outs;
    }

    std::istream& operator>>(std::istream& ins, string& target){
        char temp[1000]; 
        ins >> temp;
        target = string(temp);
        return ins;
    }

    bool operator==(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) == 0;
    }

    bool operator!=(const string& s1, const string& s2) {
        return !(s1 == s2);
    }

    bool operator<(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) < 0;
    }

    bool operator<=(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) <= 0;
    }

    bool operator>(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) > 0;
    }

    bool operator>=(const string& s1, const string& s2) {
        return strcmp(s1.characters, s2.characters) >= 0;
    }

    string operator+(const string& s1, const string& s2) {
        string temp = s1;
        temp += s2;
        return temp;
    }

    string operator+(const string& s1, const char addend[]) {
        string temp = s1;
        temp += string(addend);
        return temp;
    }
}
