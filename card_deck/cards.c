
#include "cards.h"
#include <stdlib.h>
#include <stdio.h>

// declaration
static void permute(unsigned int a[], unsigned int n);

// create a new card deck
CardDeck * createDeck(unsigned int numCards) {
    CardDeck *deck = malloc(sizeof(CardDeck));

    deck->cards = malloc(numCards * sizeof(unsigned int));

    deck->size = numCards;
    deck->undealt = numCards;

    for (unsigned int i = 0; i < numCards; i++) {
        deck->cards[i] = i;
    }

    return deck;
}

// rearrange deck and reset count
void shuffleDeck(CardDeck *deck) {
    deck->undealt = deck->size;
    permute(deck->cards, deck->size);
}

// deal cards from the end of the array
unsigned int * deal(CardDeck *deck, unsigned int numCards) {
    if (deck->undealt < numCards) {
        return NULL;
    }

    unsigned int *dealt = malloc(numCards * sizeof(unsigned int));

    if (dealt == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < numCards; i++) {
        deck->undealt--;
        dealt[i] = deck->cards[deck->undealt];
    }

    return dealt;
}

// convert card number to string
void cardToString(unsigned int c, char* str) {
    char *suits[] = {"C", "D", "H", "S"};
    char *ranks[] = {"2", "3", "4", "5", "6", "7",
                     "8", "9", "10", "J", "Q", "K", "A"};

    unsigned int suit = c / 13;
    unsigned int rank = c % 13;

    sprintf(str, "%s%s", ranks[rank], suits[suit]);
}

// print one card
void printCard(unsigned int c) {
    char str[10];
    cardToString(c, str);
    printf("%s", str);
}

// print array of cards
void printCards(unsigned int *c, unsigned int numCards) {
    for (unsigned int i = 0; i < numCards; i++) {
        printCard(c[i]);
        printf(" ");
    }
}

// permute array
static void permute(unsigned int a[], unsigned int n) {
    if (n < 2) return;

    for (unsigned int i = n - 1; i > 0; i--) {
        unsigned int j = rand() % (i + 1);

        unsigned int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}
