
#include "cards.h"
#include <stdlib.h>
#include <stdio.h>

// declaration -- copy the definition from the previous task
// and replace the definition at the end of this file
static void permute(unsigned int a[], unsigned int n);

// create a new card deck, with cards in sequence from 0 to numCard-1
CardDeck * createDeck(unsigned int numCards) {
    return NULL;
}

// rearrange deck and reset count, starting from previous shuffled state
void shuffleDeck(CardDeck *deck) {
}

// remove a new array and remove cards from the deck (starting at the end of the array)
// if not enough undealt cards, return NULL
unsigned int * deal(CardDeck *deck, unsigned int numCards) {
    return NULL;
}

// no error checking -- if c is too large, string is garbage
void cardToString(unsigned int c, char* str) {
}

// use cardToString, then print the resulting string (no space afterward)
void printCard(unsigned int c) {
}

// use printCard to print an array of cards, with space after each
void printCards(unsigned int * c, unsigned int numCards) {
}

// permute -- rearrange the elements of an array of size n
// must call rand() and must follow exactly the algorithm in the spec
// this is static because it is only called in this file
static void permute(unsigned int a[], unsigned int n) {
    // your code goes here
}