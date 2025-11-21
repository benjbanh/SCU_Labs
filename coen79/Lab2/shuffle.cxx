/*
 * Name: Your Name
 * Email: Your email
 */
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;
#include "card.h"
#include "deck.h"
#include "ctime"

namespace csen79 {
	// Fisher-Yates shuffle
	void Deck::shuffle(void) {
		int n = CARDS_PER_DECK;
		std::srand(std::time(0));
		
		for(int i = n-1; i> 0; i--){
			int j = std::rand() % i;
			std::swap(cards[i],cards[j]);
		}

		nCards = CARDS_PER_DECK;
	}
}

