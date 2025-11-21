/*
 * Name: Your Name
 * Email: Your email
 */
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
#include "card.h"
#include "deck.h"

// Deck class implementation
namespace csen79 {
	Deck::Deck(void){
		int i = 0;
		for( int suit = 1; suit <5; suit++){
			for( int rank=2; rank < 15; rank++){
				cards[i] = Card(suit,rank);
				i++;
			}
		}
		nCards = CARDS_PER_DECK;
		guard = 5;
	}

	// deal out one card
	const Card &Deck::deal() {
		// this is stud function.  Replace it with your code
		if (nCards < guard){
			static csen79::Card defaultCard;
    			return defaultCard;	
		}
		nCards--;
		return cards[nCards];
	}

	// print 13 cards each row
	ostream& operator<<(ostream& os, const Deck &d) {
		// this is stud function.  Replace it with your code
		int i = 0;
		for(int i = 0; i<d.nCards; i ++){
			if(i % 13 == 0){os << std::endl << "	";}
			os << d.cards[i];
		}
		os << std::endl;
		return os;
	}
}	
