#include <stdio.h>
//create tsv file with student last name, first name, midterm 1 grade, midterm 2 grade, final exam grade, and final letter grade
//at end of file, add overall average for each exam
int main(void) {

   /* TODO: Declare any necessary variables here. */
    char filename[26];
    char lastName[20][26];
    char firstName[20][26];
    int midterm1[20], midterm2[20], finalExam[20];
    char grade[20][3];
    int numStudents = 0;
    double midterm1Avg = 0.0, midterm2Avg = 0.0, finalExamAvg = 0.0;
      
   /* TODO: Read a file name from the user and read the tsv file here. */
   scanf("%25s", filename);
   //open file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
          printf("Error opening file.\n");
          return 1;
     }
     //read information from file
     while (numStudents < 20 && fscanf(file, "%25s %25s %d %d %d", lastName[numStudents], firstName[numStudents], &midterm1[numStudents], &midterm2[numStudents], &finalExam[numStudents]) == 5) 
     {
        midterm1Avg += midterm1[numStudents];
        midterm2Avg += midterm2[numStudents];
        finalExamAvg += finalExam[numStudents];
        //calculate letter grade
        double average = (midterm1[numStudents] + midterm2[numStudents] + finalExam[numStudents]) / 3.0;
        if (average >= 90) {
            strcpy(grade[numStudents], "A");
        } else if (average >= 80) {
            strcpy(grade[numStudents], "B");
        } else if (average >= 70) {
            strcpy(grade[numStudents], "C");
        } else if (average >= 60) {
            strcpy(grade[numStudents], "D");
        } else {
            strcpy(grade[numStudents], "F");
        }
        numStudents++;
        }

   fclose(file);
   
   /* TODO: Compute student grades and exam averages, then output results to a text file here. */
   midterm1Avg /= numStudents;
   midterm2Avg /= numStudents;
   finalExamAvg /= numStudents;

    //open output file
    FILE *outputFile = fopen("grades_output.tsv", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }
    for (int i = 0; i < numStudents; i++) {
        fprintf(outputFile, "%s\t%s\t%d\t%d\t%d\t%c\n",
                lastName[i], firstName[i],
                midterm1[i], midterm2[i], finalExam[i], grade[i]);
    }

    /* Write exam averages to two decimal places */
    fprintf(outputFile,
            "\nAverages: midterm1 %.2f, midterm2 %.2f, final %.2f\n",
            midterm1Avg, midterm2Avg, finalExamAvg);

    fclose(outputFile);

   return 0;
}
