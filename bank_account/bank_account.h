#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

// BankAccount structure definition
typedef struct {
    char customerName[21];
    double savingsBalance;
    double checkingBalance;
} BankAccount;

//Function outlines
BankAccount InitBankAccount(char* newName, double chBalance, double sBalance);

BankAccount SetName(char* newName, BankAccount account);
void GetName(char* customerName, BankAccount account);

BankAccount SetChkBalance(double balance, BankAccount account);
double GetChkBalance(BankAccount account);

BankAccount SetSavBalance(double balance, BankAccount account);
double GetSavBalance(BankAccount account);

BankAccount DepositChecking(double amt, BankAccount account);
BankAccount DepositSavings(double amt, BankAccount account);

BankAccount WithdrawChecking(double amt, BankAccount account);
BankAccount WithdrawSavings(double amt, BankAccount account);

BankAccount TransferToChecking(double amt, BankAccount account);

#endif