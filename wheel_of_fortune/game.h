#ifndef ECE_209_WHEEL_GAME_H_
#define ECE_209_WHEEL_GAME_H_

int setupGame(const char *puzzleFileName, const char *wheelFileName);
int setupPuzzle(unsigned int num); // set data for selected puzzle, clear used character list
const char *getPuzzleCategory();   // return pointer to string with current puzzle's category
const char *getPuzzle();           // return pointer to string with current puzzle's phrase
const char *getPuzzleSolution();   // return pointer to string with current puzzle's solution

int spinWheel(); // select random wheel location, return value

// Vanna, turn the letters! Return the number of letters found.
// Replace _ with the letter in the puzzle string.
// return -2 if the character is not the required type (consonant/vowel)
// return -1 if the character has already been called in this round
int chooseConsonant(char c);
int chooseVowel(char c);

void printUsedCharacters(); // print all character that have been used in this round

int checkSolution(const char *s); // compare s to puzzle solution

#endif