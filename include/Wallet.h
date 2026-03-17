#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>

using namespace std;


class Wallet  {
    private: 
      float balance;
      string userName;
      string password;
      bool state; // true for frozen, false for active
      vector<float> txRecord;
    public:
      void setState(bool s) {
        state = s;
      }
      bool getState(){
        return state;
      }
      void setBalance(float s) {
        balance = s;
      }
      float getBalance() {
        return balance;
      }
      void setUserName(string name) {
        userName = name;
      }
      string getUserName() {
        return userName;
      }
      void setPassword(string word){
        password = word;
      }
      string getPassword(){
        return password;
      }
      void setTxRecord(float tx){
        txRecord.push_back(tx);
      }
      vector<float> getTxRecord(){
        return txRecord;
      }
      void deposit(float amount);
      bool withdraw(float amount);
      void freeze();
      void unfreeze();
      bool checkNameExists(string name);
};

struct Admin
{
    string adminName;
    string adminPassword;
};

#endif