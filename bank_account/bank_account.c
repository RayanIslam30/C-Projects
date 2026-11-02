#include "bank_account.h"
#include <stdio.h>
#include <string.h>

//creates a new bank account with the given name and balances

//use the functions from the bank_account.h file to implement the functions in bank_account.c

BankAccount InitBankAccount(char* newName, double chBalance, double sBalance) {
    BankAccount account;

    strcpy(account.customerName, newName);
    account.checkingBalance = chBalance;
    account.savingsBalance = sBalance;

    return account;
}

BankAccount SetName(char* newName, BankAccount account) {
    strcpy(account.customerName, newName);
    return account;
}

void GetName(char* customerName, BankAccount account) {
    strcpy(customerName, account.customerName);
}

BankAccount SetChkBalance(double balance, BankAccount account) {
    account.checkingBalance = balance;
    return account;
}

double GetChkBalance(BankAccount account) {
    return account.checkingBalance;
}

BankAccount SetSavBalance(double balance, BankAccount account) {
    account.savingsBalance = balance;
    return account;
}

double GetSavBalance(BankAccount account) {
    return account.savingsBalance;
}

BankAccount DepositChecking(double amt, BankAccount account) {
    if (amt > 0) {
        account.checkingBalance += amt;
    }

    return account;
}

BankAccount DepositSavings(double amt, BankAccount account) {
    if (amt > 0) {
        account.savingsBalance += amt;
    }

    return account;
}

BankAccount WithdrawChecking(double amt, BankAccount account) {
    if (amt > 0) {
        account.checkingBalance -= amt;
    }

    return account;
}

BankAccount WithdrawSavings(double amt, BankAccount account) {
    if (amt > 0) {
        account.savingsBalance -= amt;
    }

    return account;
}

BankAccount TransferToChecking(double amt, BankAccount account) {
    if (amt > 0) {
        account.savingsBalance -= amt;
        account.checkingBalance += amt;
    }

    return account;
}
