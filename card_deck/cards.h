#ifndef FALL25_PT4_DEAL_CARDS_H
#define FALL25_PT4_DEAL_CARDS_H

// struct that represents a deck of cards -- size must be between 5 and 52
struct cardDeck {
    unsigned int * cards;   // array of cards
    unsigned int size;      // size of array
    unsigned int undealt;   // number of cards that have not been dealt
};

typedef struct cardDeck CardDeck;

CardDeck * createDeck(unsigned int numCards);
void shuffleDeck(CardDeck *deck);
unsigned int * deal(CardDeck * deck, unsigned int numCards);

void cardToString(unsigned int card, char * str);
void printCard(unsigned int card);  // single card
void printCards(unsigned int * cards, unsigned int numCards);   // array of cards

#endif //FALL25_PT4_DEAL_CARDS_H