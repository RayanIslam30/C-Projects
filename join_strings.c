#include <stdio.h>
#include <string.h>
//function to join two strings based on alphabetical order
void inOrder(const char* s1, const char* s2, char* out) {
    // Compare the two strings and concatenate them in alphabetical order
   if (strcmp(s1, s2) < 0) {
      strcpy(out, s1);
      strcat(out, s2);
   } 
   else {
      strcpy(out, s2);
      strcat(out, s1);
   }


}

int main() {
   return 0;
}
