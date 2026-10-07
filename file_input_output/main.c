// Read strings from a file.
// Find longest, shortest, first, and last strings.
//
// For ECE 209 students only -- DO NOT SHARE with others


#include <stdio.h>
#include <string.h>
#include <ctype.h>   // ispunct

// declaration -- don't change this 
// see below for definition -- write your code there
int wordInfo(const char * filename, char shortest[], char longest[], char lowest[], char highest[]);

int main() {
   char filename[25];
   char shortWord[16] = "";
   char longWord[16] = "";
   char firstWord[16] = "";
   char lastWord[16] = "";
   printf("Filename: ");
   fflush(stdout);
   scanf("%24s", filename);

   int w = wordInfo(filename, shortWord, longWord, firstWord, lastWord);
   if (w == -1) {
      printf("Could not open file: %s\n", filename);
   }
   else {
      printf("File has %d words.\n", w);
      printf("Shortest word: %s\n", shortWord);
      printf("Longest word: %s\n", longWord);
      printf("Alphabetically first: %s\n", firstWord);
      printf("Alphabetically last: %s\n", lastWord);
   }

   return 0;
}

int wordInfo(const char* filename, char *shortest, char *longest, char *lowest, char *highest) {
   // create a local variable large enough to hold one word (see spec for max size)
   char word[16];
   // NOTE: suggestion is to read one word at a time, not a line
   // You don't need to store all of the words, just one. Process each word as it is read.

   // Task 1: open file, read one word at a time and count them
   FILE *fp = fopen(filename, "r");
   if (fp == NULL) {
      return -1; // file could not be opened
   }
   // read one word at a time, process it, and count the number of words
   // whitespace is ' ', '\n', '\t'
   int count = 0; // initialize word count to 0
   while (fscanf(fp, "%15s", word) == 1) { 
      count++;
      // Task 2: remove punctuation from the end of a word
      int len = strlen(word);
      while (len > 0 && ispunct(word[len - 1])) {
         word[len - 1] = '\0';
         len--;
      }

      // Task 3: find the longest and shortest words
      // Task 4: find the first and last words in alphabetical order
      if (count == 1) { // initialize all variables to the first word
         strcpy(shortest, word); 
         strcpy(longest, word);
         strcpy(lowest, word);
         strcpy(highest, word);
      } else {
         if (strlen(word) < strlen(shortest)) { // if current word shorter than previous shortest, update shortest
            strcpy(shortest, word);
         }
         if (strlen(word) > strlen(longest)) { // if current word longer than previous longest, update longest
            strcpy(longest, word);
         }
         if (strcmp(word, lowest) < 0) { // if current word comes before previous lowest in alphabetical order, update lowest
            strcpy(lowest, word);
         }
         if (strcmp(word, highest) > 0) { // if current word comes after previous highest in alphabetical order, update highest
            strcpy(highest, word);
         }
      }

   }
   fclose(fp); // close the file
   return count;
}

