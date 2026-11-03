#include "game.h"
#include "random.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// GLOBAL VARIABLES
#define MAX_CATEGORY 20
#define MAX_PHRASE 80
#define NUM_WEDGES 24
 
//structure to hold puzzle information
typedef struct {
    char category[MAX_CATEGORY + 1];
    char solution[MAX_PHRASE + 1];
} Puzzle;

static Puzzle *puzzles = NULL;
static int numPuzzles = 0;

static int wheel[NUM_WEDGES]; //variable to hold the values of the wheel wedges

static unsigned int currentPuzzle = 0; // variable to hold the index of the current puzzle

static char puzzleDisplay[MAX_PHRASE + 1]; //

static int usedLetters[26] = {0};s
// (good idea to declare as static for file scope)

// setupGame: load information from puzzle and wheel files
// If error, return -1. Otherwise, return the number of puzzles.
int setupGame(const char *puzzleFileName, const char *wheelFileName)
{

    return 0;
}

// setupPuzzle: load information for the specified puzzle number
// The puzzle number corresponds to the line number in the puzzle file.
// Set up all data structures for the beginning of a round.
// Return 1 if success, 0 if error.
int setupPuzzle(unsigned int n) // choose a random puzzle, clear used character list
{
    return 0;
}

// getPuzzleCategory: returns a pointer to the category information of the current puzzle
const char *getPuzzleCategory()
{
    return NULL;
}

// getPuzzlePhrase: returns a pointer to the current puzzle phrase
// This is the version where un-guessed letters are replaced with underscores.
const char *getPuzzle()
{
    return NULL;
}

// getPuzzlePhrase: returns a pointer to the current puzzle solution
// (used for testing, not for cheating!)
const char *getPuzzleSolution()
{
    return NULL;
}

// printUsedCharacters: print all character that have been guessed in this round
// must be printed in alphabetical order, each letter followed by a space
void printUsedCharacters()
{
    return; // not yet implemented
}

// checkSolution: compare s to the puzzle solution (case-insensitive)
int checkSolution(const char *s)
{
    return 0;
}

// spinWheel: choose a random wedge on the wheel and return its value
int spinWheel() // select random wheel location, return value
{
    return 0;
}

// chooseVowel: flip matching vowels in the puzzle
// return -2 if not a vowel, -1 if letter already used
// otherwise, return the number of matches
int chooseVowel(char c)
{
    return 0;
}

// chooseConsonant: flip matching letters in the puzzle
// return -2 if not a consonant, -1 if letter already used
// otherwise, return the number of matches
int chooseConsonant(char c)
{
    return 0;
}