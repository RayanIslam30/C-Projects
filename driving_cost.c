#include <stdio.h>
//code to compute the driving cost based on miles per gallon, dollars per gallon, and miles driven

double DrivingCost(double milesPerGallon, double dollarsPerGallon, double milesDriven){
   return (milesDriven / milesPerGallon) * dollarsPerGallon; // compute the value of driving cost 
}
int main(void) {

    double milesPerGallon;
    double dollarsPerGallon;
    double milesDriven;
    printf("Enter miles per gallon: ");
    scanf("%lf", &milesPerGallon);
    printf("Enter dollars per gallon: ");
    scanf("%lf", &dollarsPerGallon);
    printf("Enter miles driven: ");
    scanf("%lf", &milesDriven);
    // compute and display the driving cost
    double cost = DrivingCost(milesPerGallon, dollarsPerGallon, milesDriven);
    printf("The driving cost is: $%.2f\n", cost);

   return 0;
}
