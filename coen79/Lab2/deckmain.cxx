/*
 * Name: Your Name
 * Email: Your email
 */
#include <iomanip>
#include <iostream>
#include "card.h"
#include "deck.h"

using namespace std;
using namespace csen79;

// Test program for Deck class
int main(void) {
	cout <<"start" << std::endl;;
	Deck deck;
	cout << deck;
	deck.shuffle();
	cout << "shuffled" << deck;

	for(int i = 0; i < 60; i++){
		cout <<"Deal: " << deck.deal() << std::endl;
	}
	cout << "test";
	return EXIT_SUCCESS;
}

