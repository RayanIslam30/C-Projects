#include <stdio.h>
//code to take a number and print the card associated with that number
//clubs are cards 0-12, diamonds are 13-25, hearts are 26-38, and spades are 39-51

void cardToString(unsigned int card, char *str) {
    char *suits[] = {"C", "D", "H", "S"};
    char *ranks[] = {"2", "3", "4", "5", "6", "7",
                     "8", "9", "10", "J", "Q", "K", "A"};

    unsigned int suit = card / 13;
    unsigned int rank = card % 13;

    sprintf(str, "%s%s", ranks[rank], suits[suit]);
}

void printCard(unsigned int card) {
    char str[50];
    cardToString(card, str);
    printf("%s", str);
}
void printCards(unsigned int *cards, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        printCard(cards[i]);
        printf(" ");
    }
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