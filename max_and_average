#include <stdio.h>
//Code that takes in a series of positive integers and outputs the maximum and average of those numbers. 
// The program will stop taking input when a negative number is entered.
int main(void) {
   //declare our variables
   int num;
   int sum = 0;
   int count = 0;
   int max = 0;
   double average;

   while(1){ //infinite loop until a negative number breaks it
   scanf("%d", &num);
   if (num < 0) { //end loop if negative number
      break;
   }
   sum += num; //get our sum to average
   count++; //used to calculate average

   if (num>max){ //get new max 
      max=num;
   }
 }
   average = (double)sum / count; //get average

    printf("%d %.2lf\n", max, average); //print max and average

   return 0;
}
