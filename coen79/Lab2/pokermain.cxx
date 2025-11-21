/*
 * Name: Your Name
 * Email: Your email
 */
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cmath>
#include "card.h"
#include "deck.h"
#include "poker.h"

using namespace std;
using namespace csen79;

// Poker test code
int main(void) {
    Poker game;


    // Generate one hand for each ranking category
    cout << "One hand for each ranking:" << endl;
    game.getEveryHand();
    
    cout << "Statistics:" << endl;
    game.statistics();




}