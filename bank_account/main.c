#include <stdio.h>
#include <string.h>

#include "BankAccount.h"

int main() {
   BankAccount account = InitBankAccount("Mickey", 500.00, 1000.00);
   char name[20];
   
   account = SetChkBalance(500, account);
   account = SetSavBalance(500, account);
   account = WithdrawSavings(100, account);
   account = WithdrawChecking(100, account);
   account = TransferToChecking(300, account);
   
   GetName(name, account);
   printf("%s\n", name);
   printf("$%.2f\n", GetChkBalance(account));
   printf("$%.2f\n", GetSavBalance(account));

   return 0;
}