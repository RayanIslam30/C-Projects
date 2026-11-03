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
    // Free information from a previous setupGame call
    free(puzzles);
    puzzles = NULL;
    numPuzzles = 0;

    FILE *puzzleFile = fopen(puzzleFileName, "r");
    if (puzzleFile == NULL) {
        return -1;
    }

    FILE *wheelFile = fopen(wheelFileName, "r");
    if (wheelFile == NULL) {
        fclose(puzzleFile);
        return -1;
    }

    // Read the 24 wheel values into a temporary array
    int newWheel[NUM_WEDGES];

    for (int i = 0; i < NUM_WEDGES; i++) {
        if (fscanf(wheelFile, "%d", &newWheel[i]) != 1) {
            fclose(puzzleFile);
            fclose(wheelFile);
            return -1;
        }

        if (newWheel[i] < -1) {
            fclose(puzzleFile);
            fclose(wheelFile);
            return -1;
        }
    }

    // Make sure there is nothing except whitespace after the 24 values
    char extra;
    if (fscanf(wheelFile, " %c", &extra) == 1) {
        fclose(puzzleFile);
        fclose(wheelFile);
        return -1;
    }

    fclose(wheelFile);

    // Load puzzles
    Puzzle *loaded = NULL;
    int count = 0;
    char line[MAX_CATEGORY + MAX_PHRASE + 4];

    while (fgets(line, sizeof(line), puzzleFile) != NULL) {

        // Every line must end with a newline
        char *newline = strchr(line, '\n');

        if (newline == NULL) {
            free(loaded);
            fclose(puzzleFile);
            return -1;
        }

        *newline = '\0';

        // Handle Windows-style line endings
        int length = (int)strlen(line);

        if (length > 0 && line[length - 1] == '\r') {
            line[--length] = '\0';
        }

        // Find the category/phrase separator
        char *separator = strchr(line, '/');

        if (separator == NULL) {
            free(loaded);
            fclose(puzzleFile);
            return -1;
        }

        int categoryLength = (int)(separator - line);
        int phraseLength = (int)strlen(separator + 1);

        // Validate lengths
        if (categoryLength > MAX_CATEGORY ||
            phraseLength > MAX_PHRASE) {
            free(loaded);
            fclose(puzzleFile);
            return -1;
        }

        // Validate category: all letters must be uppercase
        for (int i = 0; i < categoryLength; i++) {
            if (isalpha((unsigned char)line[i]) &&
                !isupper((unsigned char)line[i])) {
                free(loaded);
                fclose(puzzleFile);
                return -1;
            }
        }

        // Validate phrase
        for (int i = 0; i < phraseLength; i++) {
            char c = separator[1 + i];

            if (c == '_') {
                free(loaded);
                fclose(puzzleFile);
                return -1;
            }

            if (isalpha((unsigned char)c) &&
                !isupper((unsigned char)c)) {
                free(loaded);
                fclose(puzzleFile);
                return -1;
            }
        }

        // Allocate space for another puzzle
        Puzzle *temp = realloc(loaded,
                               (count + 1) * sizeof(Puzzle));

        if (temp == NULL) {
            free(loaded);
            fclose(puzzleFile);
            return -1;
        }

        loaded = temp;

        // Copy category
        memcpy(loaded[count].category, line, categoryLength);
        loaded[count].category[categoryLength] = '\0';

        // Copy phrase
        strcpy(loaded[count].solution, separator + 1);

        count++;
    }

    if (ferror(puzzleFile)) {
        free(loaded);
        fclose(puzzleFile);
        return -1;
    }

    fclose(puzzleFile);

    // Save successfully loaded information
    puzzles = loaded;
    numPuzzles = count;

    // Copy wheel values into the global array
    for (int i = 0; i < NUM_WEDGES; i++) {
        wheel[i] = newWheel[i];
    }

    return numPuzzles;
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
    int first = 1;

    for (int i = 0; i < 26; i++) {
        if (usedLetters[i]) {
            if (!first) {
                printf(" ");
            }

            printf("%c", 'A' + i);
            first = 0;
        }
    }

    printf("\n");
}

// checkSolution: compare s to the puzzle solution (case-insensitive)
int checkSolution(const char *s)
{
    if (s == NULL) {
        return 0;
    }

    const char *solution = puzzles[currentPuzzle].solution;

    while (*s != '\0' && *solution != '\0') { // loop through each character in the input string and the solution string, check if they match (case-insensitive)
        if (toupper((unsigned char)*s) !=
            toupper((unsigned char)*solution)) {
            return 0;
        }

        s++;
        solution++;
    }

    return (*s == '\0' && *solution == '\0'); 
}
// spinWheel: choose a random wedge on the wheel and return its value
int spinWheel() // select random wheel location, return value
{
    int index = getRandom(NUM_WEDGES); // get a random index for the wheel

    return wheel[index];
}

// helper function to use for both chooseVowel and chooseConsonant
static int chooseLetter(char c, int vowel)
{
    // Make sure the character is a letter
    if (!isalpha((unsigned char)c)) {
        return -2;
    }

    // Convert to uppercase
    c = (char)toupper((unsigned char)c);

    // Determine whether the character is a vowel
    int isVowel = (c == 'A' || c == 'E' ||
                   c == 'I' || c == 'O' ||
                   c == 'U');

    // Check whether the letter is the correct type
    if (isVowel != vowel) {
        return -2;
    }

    // Check whether the letter has already been guessed
    int index = c - 'A';

    if (usedLetters[index]) {
        return -1;
    }

    // Remember that this letter has been guessed
    usedLetters[index] = 1;

    // Replace matching underscores
    int matches = 0;

    for (int i = 0; puzzleDisplay[i] != '\0'; i++) {
        if (puzzles[currentPuzzle].solution[i] == c) {
            puzzleDisplay[i] = c;
            matches++;
        }
    }

    return matches;
}
// chooseVowel: flip matching vowels in the puzzle
// return -2 if not a vowel, -1 if letter already used
// otherwise, return the number of matches
int chooseVowel(char c)
{
    return chooseLetter(c, 1);
}

// chooseConsonant: flip matching letters in the puzzle
// return -2 if not a consonant, -1 if letter already used
// otherwise, return the number of matches
int chooseConsonant(char c)
{
    return chooseLetter(c, 0);
}