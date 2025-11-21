/*
 * Name: Benjamin Banh
 * Email: BBanh@scu.edu
 */
#include <iomanip>
#include <iostream>
#include "card.h"

using namespace std;
using namespace csen79;

// Test program for Card
int main(void) {
	// test code just for Card class
	Card c1(3, 14); //Ace of Hearts
	Card c2(1, 13); //King of Clubs

	std::cout << "c1: " << c1;
	std::cout << "c2: " << c2;
	
	if(c1 > c2){std::cout << "c1 > c2";}
	else{std::cout << "c1 > c2";}
	return EXIT_SUCCESS;
}
