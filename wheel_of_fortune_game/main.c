// ECE 209 Program 2: Wheel of Fortune
// Fall 2026
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "random.h"
#include "game.h"

// User interface -- play the game!
int main()
{
    printf("*******************************\n");
    printf("* WELCOME to WHEEL OF FORTUNE *\n");
    printf("*******************************\n");

    int numPuzzles = setupGame("puzzles.txt", "wheel.txt");
    if (numPuzzles == 0)
    {
        printf("ERROR during game setup\n");
        return 0; // if setupGame returns an error, exit
    }
    int userSeed = 0;
    printf("\n");
    while (!userSeed)
    {
        printf("Enter a non-zero decimal or hexadecimal number, to seed the random number generator: ");
        fflush(stdout);
        scanf("%i", &userSeed);
        if (userSeed)
        {
            seedRandom((unsigned int)userSeed);
        }
    }
    int numPlayers = 1;
    int i;
    printf("\nHow many players (1-3)? ");
    fflush(stdout);
    scanf("%d", &numPlayers);
    if ((numPlayers < 1) || (numPlayers > 3))
    {
        printf("That's not a legal number of players.  We'll just stick with one.\n\n");
    }

    int gameScores[numPlayers];
    int roundScores[numPlayers];
    for (i = 0; i < numPlayers; i++)
        gameScores[i] = 0;

    // Three rounds, three puzzles
    int currentPlayer = 0; // start with Player 1
    for (int r = 0; r < 3; r++)
    {
        printf("\n\n===========\n");
        printf("  ROUND %d  \n", r + 1);
        printf("===========\n");

        // set up the next puzzle
        // choose a puzzle number
        unsigned int puzzleNumber = getRandom(numPuzzles);
        int status = setupPuzzle(puzzleNumber);
        if (!status)
        {
            printf("ERROR: Unable to read puzzle %d\n", puzzleNumber);
            return 0;
        }
        const char *category = getPuzzleCategory();
        const char *puzzle = getPuzzle();
        char solution[101] = "";
        // NOTE: phrase string cannot be changed directly from this function
        // (that's why it's const), but the game functions will change it

        // clear player scores for this round
        for (i = 0; i < numPlayers; i++)
            roundScores[i] = 0;

        bool solved = false;
        int move = 0;
        int spinResult = 0;
        char guess[2]; // a 1-character string to make I/O easier
        int guessResult;
        while (!solved)
        {
            for (i = 0; i < numPlayers; i++)
            {
                printf("Player %d: $%d  ", i + 1, roundScores[i]);
            }
            printf("\n\nCategory: %s\n", category);
            printf("Puzzle:\n%s\n", puzzle);
            printf("Used characters:\n");
            printUsedCharacters();

            move = 0;
            while (!move)
            {
                if (roundScores[currentPlayer] >= 250)
                {
                    printf("\nPlayer %d: Solve (1), Spin (2), or Buy a vowel (3)?  ", currentPlayer + 1);
                }
                else
                {
                    printf("\nPlayer %d: Solve (1) or Spin (2)?  ", currentPlayer + 1);
                }
                fflush(stdout);
                int n = scanf("%d", &move);
                if ((n != 1) || (getchar() != '\n'))
                {
                    // read characters up to and including linefeed
                    while (getchar() != '\n')
                        ;
                    move = 0;
                }
                if ((move < 1) || (move > 3) || (move == 3 && roundScores[currentPlayer] < 250))
                {
                    printf("Invalid choice: try again!\n");
                    move = 0;
                }
            }
            switch (move) // guaranteed to be 1, 2, or 3
            {
            case 1: // solve
                printf("Enter your solution:\n");
                fgets(solution, 101, stdin); // read line from standard input
                char *lf = strchr(solution, '\n');
                if (lf)
                    *lf = '\0';
                if (checkSolution(solution))
                {
                    printf("\nCORRECT!! You win the round with $%d!!!\n", roundScores[currentPlayer]);
                    solved = true;
                }
                else
                {
                    printf("\nSorry, that's not the answer. Your turn is over.\n");
                    currentPlayer = (currentPlayer + 1) % numPlayers;
                }
                break; // skip next case
            case 2:    // spin
                spinResult = spinWheel();
                printf("\nSpinning....  You landed on ");
                if (spinResult > 0)
                {
                    printf("$%d.\nWhat is your letter?  ", spinResult);
                    fflush(stdout);
                    scanf("%1s", guess); // assume one letter: skips previous linefeed
                    guessResult = chooseConsonant(*guess);
                    if (guessResult == -2)
                    {
                        printf("That's not a consonant. You lose your turn.\n");
                        currentPlayer = (currentPlayer + 1) % numPlayers;
                    }
                    else
                    {
                        printf("%s\n", puzzle);
                        if (guessResult == 0) // no match
                        {
                            printf("Sorry, there is no %c.\n", *guess);
                            currentPlayer = (currentPlayer + 1) % numPlayers;
                        }
                        else if (guessResult == -1)
                        {
                            printf("%c has already been used.\n", *guess);
                            printf("You lose your turn.\n");
                            currentPlayer = (currentPlayer + 1) % numPlayers;
                        }
                        else
                        {
                            if (guessResult == 1)
                            {
                                printf("There is one %c, so you win $%d!\n", *guess, spinResult);
                            }
                            else
                            {
                                printf("There are %d %c's, so you win $%d!\n",
                                       guessResult, *guess, guessResult * spinResult);
                            }
                            roundScores[currentPlayer] += guessResult * spinResult;
                        }
                    }
                }
                else if (spinResult == 0)
                {
                    printf("LOSE A TURN\n");
                    currentPlayer = (currentPlayer + 1) % numPlayers;
                }
                else
                {
                    printf("BANKRUPT\n");
                    roundScores[currentPlayer] = 0;
                    currentPlayer = (currentPlayer + 1) % numPlayers;
                }
                break; // skip next case
            case 3:    // buy a vowel
                if (roundScores[currentPlayer] < 250)
                {
                    printf("You don't have enough money to buy a vowel.\n");
                }
                else
                {
                    roundScores[currentPlayer] -= 250;
                    printf("Choose your vowel: ");
                    scanf("%1s", guess);
                    guessResult = chooseVowel(*guess);
                    if (guessResult == -2)
                    {
                        printf("That's not a vowel -- you lose your turn.\n");
                        currentPlayer = (currentPlayer + 1) % numPlayers;
                    }
                    else
                    {
                        printf("%s\n", puzzle);
                        if (guessResult == 0) // no match
                        {
                            printf("Sorry, there is no %c.\n", *guess);
                            currentPlayer = (currentPlayer + 1) % numPlayers;
                        }
                        else if (guessResult == -1)
                        {
                            printf("%c has already been used.\n", *guess);
                            printf("You lose your turn.\n");
                            currentPlayer = (currentPlayer + 1) % numPlayers;
                        }
                        else
                        {
                            if (guessResult == 1)
                            {
                                printf("There is one %c.\n", *guess);
                            }
                            else
                            {
                                printf("There are %d %c's.\n", guessResult, *guess);
                            }
                        }
                    }
                }
            }
        }

        gameScores[currentPlayer] += roundScores[currentPlayer];

        printf("\nAt the end of round %d...\n", r + 1);
        for (i = 0; i < numPlayers; i++)
        {
            printf("PLAYER %d: $%d\n", i + 1, gameScores[i]);
            roundScores[i] = 0;
        }
    }
    int maxi = 0;
    int maxScore = gameScores[0];
    for (i = 1; i < numPlayers; i++)
    {
        if (gameScores[i] > maxScore)
        {
            maxScore = gameScores[i];
            maxi = i;
        }
    }
    printf("############################\n");
    printf(" Player %d wins!!!\n", maxi + 1);
    printf("############################\n");

    return 0;
}
