/*
 * CSEN 79 Lab Sample Code
 * Your name, Your email
 */
namespace csen79 {
	// Deck class with an embedded Card class
	// See stand-alone Card class in "card.h"
	class Deck {
	public:
		static const size_t CARDS_PER_DECK = 52;
		Deck(void);	//constructor
		const Card &deal(void);
		void shuffle(void);

	friend std::ostream& operator<<(std::ostream& os, const Deck &);

	private:
		int nCards;
		Card cards[CARDS_PER_DECK];
		int next;
		int guard;
	};
}
