#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>

using namespace std;


class Wallet  {
  friend class Bank;
    private: 
      float balance;
      string userName;
      string password;
      bool state; // true for frozen, false for active
      vector<float> txRecord;
    public:
      void setState(bool &s) {
        s = state;
      }
      bool getState(){
        return state;
      }
      void setBalance(float s) {
        s = balance;
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
};

struct Admin
{
    string adminName;
    string adminPassword;
};

#endif