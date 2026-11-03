#include "game.h"
#include "random.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

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

static char puzzleDisplay[MAX_PHRASE + 1]; //variable to hold the current puzzle display (with underscores for unguessed letters)

static int usedLetters[26] = {0};
// (good idea to declare as static for file scope)

// setupGame: load information from puzzle and wheel files
// If error, return -1. Otherwise, return the number of puzzles.
int setupGame(const char *puzzleFileName, const char *wheelFileName)
{
    // Open puzzle file and wheel file
    FILE *puzzleFile = fopen(puzzleFileName, "r");
    if (puzzleFile == NULL) {
        return -1;
    }

    FILE *wheelFile = fopen(wheelFileName, "r");
    if (wheelFile == NULL) {
        fclose(puzzleFile);
        return -1;
    }

    // Read exactly 24 wheel values
    for (int i = 0; i < NUM_WEDGES; i++) {
        if (fscanf(wheelFile, "%d", &wheel[i]) != 1) {
            fclose(puzzleFile);
            fclose(wheelFile);
            return -1;
        }
    }

    // Check for additional non-whitespace content
    char extra;
    if (fscanf(wheelFile, " %c", &extra) == 1) {
        fclose(puzzleFile);
        fclose(wheelFile);
        return -1;
    }
    
    //close the puzzle and wheel files
    fclose(puzzleFile);
    fclose(wheelFile);

    return 0; // Temporarily; eventually return numPuzzles
}

// setupPuzzle: load information for the specified puzzle number
// The puzzle number corresponds to the line number in the puzzle file.
// Set up all data structures for the beginning of a round.
// Return 1 if success, 0 if error.
int setupPuzzle(unsigned int n) // choose a random puzzle, clear used character list
{
    //select the puzzle associated with given number n, and set up display and used letters
    currentPuzzle = n;

    // Clear previously guessed letters
    for (int i = 0; i < 26; i++) {
        usedLetters[i] = 0;
    }
    // Initialize puzzle display with underscores for unguessed letters
    int i = 0;
    while (puzzles[n].solution[i] != '\0') { // loop through each character in puzzle
        if (isalpha((unsigned char)puzzles[n].solution[i])) { //check if character is a letter
            puzzleDisplay[i] = '_';
        }
        else {
            puzzleDisplay[i] = puzzles[n].solution[i]; // keep non-letter (spaces, punctuation) as is
        }

        i++;
    }

    puzzleDisplay[i] = '\0';

    return 1;
}

// getPuzzleCategory: returns a pointer to the category information of the current puzzle
const char *getPuzzleCategory()
{
    return puzzles[currentPuzzle].category;
}

// getPuzzlePhrase: returns a pointer to the current puzzle phrase
// This is the version where un-guessed letters are replaced with underscores.
const char *getPuzzle()
{
    return puzzleDisplay;
}

// getPuzzlePhrase: returns a pointer to the current puzzle solution
// (used for testing, not for cheating!)
const char *getPuzzleSolution()
{
    return puzzles[currentPuzzle].solution;
}

// printUsedCharacters: print all character that have been guessed in this round
// must be printed in alphabetical order, each letter followed by a space
void printUsedCharacters()
{
    // Print all guessed letters in alphabetical order
    for (int i = 0; i < 26; i++) {
        if (usedLetters[i]) {
            printf("%c ", 'A' + i);
        }
    }
    printf("\n");
}

// checkSolution: compare s to the puzzle solution (case-insensitive)
int checkSolution(const char *s)
{
    if (strcasecmp(s, puzzles[currentPuzzle].solution) == 0) {
        return 1;
    }
}

// spinWheel: choose a random wedge on the wheel and return its value
int spinWheel() // select random wheel location, return value
{
    int index = getRandom(NUM_WEDGES); // get a random index for the wheel

    return wheel[index];
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