#include <stdio.h>
//code to compute the driving cost based on miles per gallon, dollars per gallon, and miles driven

double DrivingCost(double milesPerGallon, double dollarsPerGallon, double milesDriven){
    if (milesDriven==0){ // if the miles driven is zero, compute the cost for 10, 50, and 400 miles
    printf("$%.2f ", ((10 / milesPerGallon) * dollarsPerGallon));
    printf("$%.2f ", ((50 / milesPerGallon) * dollarsPerGallon));
    printf("$%.2f\n", ((400 / milesPerGallon) * dollarsPerGallon));
    }
    else{
   return (milesDriven / milesPerGallon) * dollarsPerGallon; // compute the value of driving cost 
    }
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
