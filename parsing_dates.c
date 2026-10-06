#include <stdio.h>
#include <string.h>

// code that converts MONTH DAY, YEAR into mm-dd-yyyy

//takes multiple dates at once, stops with '-1'


//function that converts month string to integer
int GetMonthAsInt(char *monthString) {
	int monthInt;

	if (strcmp(monthString, "January") == 0) {
		monthInt = 1;
	}
	else if (strcmp(monthString, "February") == 0) {
		monthInt = 2;
	}
	else if (strcmp(monthString, "March") == 0) {
		monthInt = 3;
	}
	else if (strcmp(monthString, "April") == 0) {
		monthInt = 4;
	}
	else if (strcmp(monthString, "May") == 0) {
		monthInt = 5;
	}
	else if (strcmp(monthString, "June") == 0) {
		monthInt = 6;
	}
	else if (strcmp(monthString, "July") == 0) {
		monthInt = 7;
	}
	else if (strcmp(monthString, "August") == 0) {
		monthInt = 8;
	}
	else if (strcmp(monthString, "September") == 0) {
		monthInt = 9;
	}
	else if (strcmp(monthString, "October") == 0) {
		monthInt = 10;
	}
	else if (strcmp(monthString, "November") == 0) {
		monthInt = 11;
	}
	else if (strcmp(monthString, "December") == 0) {
		monthInt = 12;
	}
	else {
		monthInt = 0;
	}

	return monthInt;
}

int main(void) {

	// TODO: Read dates from input, parse the dates to find the ones
   //       in the correct format, and output in m-d-yyyy format

   //declare variables to store values
   char date[100];
   char month[20];
   int day, year, monthInt;
   //loop to read multiple dates from input
   while (fgets(date, sizeof(date), stdin) != NULL) {

      // Stop when the line is -1
      if (strcmp(date, "-1\n") == 0 || strcmp(date, "-1") == 0) {
         break;
      }

      // Parse: Month Day, Year
      // parse works because each part parsed adds 1, so if it returns 3, we know all three parts were parsed
      if (sscanf(date, "%s %d, %d", month, &day, &year) == 3) {
         
         monthInt = GetMonthAsInt(month);

         // Only output if the month is valid
         if (monthInt != 0) {
            printf("%d-%d-%d\n", monthInt, day, year);
         }
      }
   }

    
	return 0;
}
