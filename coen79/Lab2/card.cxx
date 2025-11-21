/*
 * Name: Benjamin Banh
 * Email: BBanh@scu.edu
 */
#include <iomanip>
#include <iostream>
#include "card.h"
using namespace std;

// Stand-alone Card definitions
namespace csen79 {
	ostream& operator<<(ostream& os, const Card &c) {
		// implement cout
		switch(c.suit){
			case 1:   os << "♣"; break;
            case 2:   os << "♦"; break;
            case 3:   os << "♥"; break;
			case 4:   os << "♠"; break;
		}
		os << c.rank << " ";
		return os;
	}

	int Card::getSuit(void) const{
		return suit;
	}

	//overloads "int()" operator
	Card::operator int() const {
		return rank;
	}

	//overloads "<" operator
	bool Card::operator<(const Card& other) const{
		//compare ranks
		if(int(*this) != int(other)) {
			return int(*this) < int(other);
		} 
		//compare suits
		else{
			//Spade(4) > Heart(3) > Diamonds(2) > Clubs(1)
			return suit < other.suit;
		}
	}
}
