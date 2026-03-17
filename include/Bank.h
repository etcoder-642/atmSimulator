#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

#include "Wallet.h"

using namespace std;

class Bank {
    private:
      vector<Wallet> bank;  
    public:
      vector<Wallet>& getWallet(){ return bank;}
      void setWallet(vector<Wallet> myBank) { bank = myBank;}
      void updateFile();
      void updateTransaction();
      void handleMoneyTransfer(int index, string receiverName, float amount);
      void loadUserData();
      void loadTransactionData();
      bool authenticateUser(string tempName, string tempPassword, int &index);
      void systemWideAmountChange(float amount);
      bool checkNameExist(string name);
      void addValue(Wallet myWallet);
      int  size();
      void deleteAllAccounts();
      void freezeAccount(int index);
      void unfreezeAccount(int index);
      void depositToAccount(int index, float amount);
      void deductFromAccount(int index, float amount);
      void resetPassword(int index);
      void setPassword(int index, string newPassword);
      void deleteAccount(int index);
      void freezeAllAccounts();
      void unfreezeAllAccounts();
};

#endif