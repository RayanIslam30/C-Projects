#include <stdio.h>
//code to take a number and print the card associated with that number
//clubs are cards 0-12, diamonds are 13-25, hearts are 26-38, and spades are 39-51

void cardToString(unsigned int card, char * str) {
    // your code goes here
}

void printCard(unsigned int card) {
    // your code goes here
}

void printCards(unsigned int * cards, unsigned int size) {
    // your code goes here
}

int main()
{
    unsigned int card;
    printf("Enter a card number: ");
    fflush(stdout);
    scanf("%u", &card);
    printCard(card);
    return 0;
}