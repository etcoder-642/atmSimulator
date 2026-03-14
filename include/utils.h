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
void updateTransaction(vector<Wallet>& data);
void handleMoneyTransfer(vector<Wallet>& data, int index, string receiverName, float amount);
void loadUserData(vector<Wallet>& masterData);
void loadTransactionData(vector<Wallet>& masterData);
bool authenticateUser(vector<Wallet> &data, string tempName, string tempPassword, int &index);
bool authenticateAdmin(Admin adminAcc, string tempName, string tempPassword);
void loadAdminData(Admin& adminAcc);
void uploadAdminData(const Admin& adminAcc);
void systemWideAmountChange(vector<Wallet>& masterData, float amount);

#endif