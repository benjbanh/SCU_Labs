/*
 * Name: Your Name
 * Email: Your email
 */
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <ctime>

#include "card.h"
#include "deck.h"
#include "poker.h"

using namespace std;

namespace csen79 {
	Poker::Poker(void){
		deck.shuffle();
	}

	// so that we can simply "cout << " a poker hand
	ostream& operator<<(ostream& os, const Poker &h) {
		for(int i = 0; i<5; i ++){
			os << h.hand[i];
		}
		return os;
	}

	void Poker::dealHand(void){
		for(int i=0; i<5; i++){
			hand[i] = deck.deal();
		}
	}

	int Poker::rankHand(void){													//problem with straights(never counted)
		int combo = 1;
		int maxcombo = 0;
		bool hasPair = false;
		bool hasTwoPair = false;
		bool isFlush = true;
		bool isStraight = true;

		// Sort the array
		std::sort(hand, hand + 5);

		for(int i = 1; i < 5;i++){
			//checks if previous card is the same as current(incr combo)
			if (int(hand[i]) == int(hand[i-1])){
				combo++;
			}
			else{
				if (combo >= 2){
					if(hasPair){hasTwoPair=true;}
					else{hasPair=true;}
				}
				combo = 1; 
			}
			//checks for flush continuation
			if (hand[i].getSuit() != hand[i-1].getSuit()){isFlush = false;}
			//checks for straight
			if (int(hand[i]) != int(hand[i-1]) + 1){isStraight = false;}

			if(maxcombo < combo){ maxcombo = combo; }
		}

		if (combo >= 2){
			if(hasPair){hasTwoPair=true;}
			else{hasPair=true;}
		}

		// cout << maxcombo << "|hasPair " << hasPair << "|hasTwoPair " << hasTwoPair << "|isFlush " << isFlush << "|isStraight  " << isStraight << endl;

		if (maxcombo == 5) {return POKER_5CARD;}
		else if (isStraight && isFlush) {return POKER_STRAIGHT_FLUSH;}
		else if (maxcombo == 4) {return POKER_QUAD;}
		else if (maxcombo == 3 && hasTwoPair) {return POKER_FULLHOUSE;}
		else if (isFlush) {return POKER_FLUSH;}
		else if (isStraight) {return POKER_STRAIGHT;}
		else if (maxcombo == 3) {return POKER_TRIPLE;}
		else if (hasTwoPair) {return POKER_2_PAIR;}
		else if (maxcombo == 2) { return POKER_PAIR;}
		else {return POKER_HIGHCARD;}
	}

	//generates hands until at least one of every hand is made
	void Poker::getEveryHand(void){
		hand[0] = Card(1, 14);
		hand[1] = Card(2, 14);
		hand[2] = Card(3, 14);
		hand[3] = Card(4, 14);
		hand[4] = Card(4, 14);//5 CARD
		cout << *this << "	" << rankHand() << " = 	5 card" << endl;

		hand[0] = Card(1, 14);
		hand[1] = Card(1, 13);
		hand[2] = Card(1, 12);
		hand[3] = Card(1, 11);
		hand[4] = Card(1, 10);//Straight Flush
		cout << *this << "	" << rankHand() << " = 	Straight Flush" << endl;//presumed Flush

		hand[0] = Card(1, 14);
		hand[1] = Card(2, 14);
		hand[2] = Card(3, 14);
		hand[3] = Card(4, 14);
		hand[4] = Card(1, 10);//Quad
		cout << *this << "	" << rankHand() << " = 	4 Card" << endl;

		hand[0] = Card(1, 14);
		hand[1] = Card(2, 14);
		hand[2] = Card(4, 14);
		hand[3] = Card(1, 2);
		hand[4] = Card(2, 2);//full house
		cout << *this << "	" << rankHand() << " = 	Full House" << endl;

		hand[0] = Card(1, 14);
		hand[1] = Card(1, 10);
		hand[2] = Card(1, 5);
		hand[3] = Card(1, 3);
		hand[4] = Card(1, 2);//flush
		cout << *this << "	" << rankHand() << " = 	Flush" << endl;

		hand[0] = Card(1, 14);
		hand[1] = Card(2, 13);
		hand[2] = Card(3, 12);
		hand[3] = Card(4, 11);
		hand[4] = Card(1, 10);//straight
		cout << *this << "	" << rankHand() << " = 	Straight" << endl;	//presumed high card

		hand[0] = Card(1, 14);
		hand[1] = Card(2, 14);
		hand[2] = Card(3, 14);
		hand[3] = Card(1, 11);
		hand[4] = Card(1, 10);//triple
		cout << *this << "	" << rankHand() << " = 	Triple" << endl;

		hand[0] = Card(1, 14);
		hand[1] = Card(4, 14);
		hand[2] = Card(1, 12);
		hand[3] = Card(4, 12);
		hand[4] = Card(1, 10);//2 pair
		cout << *this << "	" << rankHand() << " = 	2 Pair" << endl;

		hand[0] = Card(2, 14);
		hand[1] = Card(2, 13);
		hand[2] = Card(2, 12);
		hand[3] = Card(1, 10);
		hand[4] = Card(5, 10);//pair
		cout << *this << "	" << rankHand() << " = 	Pair" << endl;

		hand[0] = Card(1, 14);
		hand[1] = Card(2, 11);
		hand[2] = Card(3, 10);
		hand[3] = Card(4, 5);
		hand[4] = Card(1, 2);//high card
		cout << *this << "	" << rankHand() << " = 	High Card" << endl;
		
	}

	void Poker::statistics(void){
		static csen79::Card defaultCard;

		int count5CARD = 0;
		int countSTRAIGHT_FLUSH = 0;
		int countQUAD = 0;
		int countFULLHOUSE = 0;
		int countFLUSH = 0;
		int countSTRAIGHT = 0;
		int countTRIPLE = 0;
		int count2_PAIR = 0;
		int countPAIR = 0;
		int countHIGHCARD = 0;	

		const int total = 9999999;	

		clock_t start = clock();	//starting time
		for(int i = 0;i < total; i++){
			dealHand();
			if(int(hand[0]) ==  0){
				deck.shuffle();
				dealHand();
			}
			int ans = rankHand();

			switch(ans){
				case 0:
					countHIGHCARD++;
					break;
				case 1:
					countPAIR++;
					break;
				case 2:
					count2_PAIR++;
					break;
				case 3:
					countTRIPLE++;
					break;
				case 4:
					countSTRAIGHT++;
					break;
				case 5:
					countFLUSH++;
					break;
				case 6:
					countFULLHOUSE++;
					break;
				case 7:
					countQUAD++;
					break;
				case 8:
					countSTRAIGHT_FLUSH++;
					break;
				case 9:
					count5CARD++;
            		break;
			}
		}

		clock_t end = clock();
		double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
		std::cout << "Elapsed time: " << elapsed_secs << " seconds" << endl;
		std::cout << "Average time: " << elapsed_secs/100 << " seconds per 100K hands" << endl;

		cout << "	5CARD: " << count5CARD << "		" << 100*float(count5CARD)/float(total) << "%";

		cout << endl<< "	STRAIGHT_FLUSH: " << countSTRAIGHT_FLUSH << "	" << 100*float(countSTRAIGHT_FLUSH)/float(total) << "%";

		cout << endl<< "	QUAD: " << countQUAD << "			" << 100*float(countQUAD)/float(total) << "%";

		cout << endl << "	FULLHOUSE: " << countFULLHOUSE << "	" << 100*float(countFULLHOUSE)/float(total) << "%";

		cout << endl << "	FLUSH: " << countFLUSH << "		" << 100*float(countFLUSH)/float(total) << "%";

		cout << endl << "	STRAIGHT: " << countSTRAIGHT << "		" << 100*float(countSTRAIGHT)/float(total) << "%";

		cout << endl << "	TRIPLE: " << countTRIPLE << "		" << 100*float(countTRIPLE)/float(total) << "%";

		cout << endl << "	2_PAIR: " << count2_PAIR << "		" << 100*float(count2_PAIR)/float(total) << "%";

		cout << endl << "	PAIR: " << countPAIR << "		" << 100*float(countPAIR)/float(total) << "%";

		cout << endl << "	HIGHCARD: " << countHIGHCARD << "	" << 100*float(countHIGHCARD)/float(total) << "%";

		cout << endl;
	}

}
