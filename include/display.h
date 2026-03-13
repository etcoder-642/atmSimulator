#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>
#include "Wallet.h"

using namespace std;

void initialPage(int &initialVal);
void userDisplay(string user, int &value, float &balance);
void displayTransactionHistory(const vector<Wallet>& data, int num);
void displayBalance(string user, float balance);
void displaySignUpPage(Wallet& myWallet);
void displayLogInPage(string &tempName, string &tempPassword);
void displayAdminDashBoard(int &adminChoice, string admin);
void displayAdminSignUpPage(Admin& adminAcc);
void displayAdminLogInPage(string& tempName, string& tempPassword);
void displayAdminAnalytics(float totalLiquidity, float transactionVol, float netFlow, int transactionNum, int totalUsers, float avWealth);
void displayAllAccounts(const vector<Wallet> &masterData, vector<int> trxnNums);
void displaySystemActions(int& value);

#endif
