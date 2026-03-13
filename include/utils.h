#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Wallet.h"
using namespace std;

bool checkFile(string fileName);
vector<string> splitString(string str);
void updateFile(const vector<Wallet>& data);
bool checkNameExist(const vector<Wallet>& data, string name);
void updateTransaction(vector<Wallet>& data, int num);
void handleMoneyTransfer(vector<Wallet>& data, int index, string receiverName, float amount);
void loadUserData(vector<Wallet>& masterData);
void loadTransactionData(vector<Wallet> &masterData);

#endif