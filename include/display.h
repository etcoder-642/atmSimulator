#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>
#include "Wallet.h"
#include "Bank.h"

using namespace std;

void initialPage(int &initialVal);
void userDisplay(string user, int &value, float balance);
void displayTransactionHistory(Bank &bank, int num);
void displayBalance(string user, float balance);
void displaySignUpPage(Wallet& myWallet);
void displayLogInPage(string &tempName, string &tempPassword);
void displayAdminDashBoard(int &adminChoice, string admin);
void displayAdminSignUpPage(Admin& adminAcc);
void displayAdminLogInPage(string& tempName, string& tempPassword);
void displayAdminAnalytics(float totalLiquidity, float transactionVol, float netFlow, int transactionNum, int totalUsers, float avWealth);
void displayAllAccounts(Bank &bank, vector<int> trxnNums);
void displaySystemActions(int& value);
void displayUserSpecificActions(int& value);
void displayUserInfo(Bank bank, int num);
void displaySystemWideAccountChange(float amount);
void displayAccountFreezeMessage(string name);
void displaySpecialMessage(string message);

template <typename T>
void receiveMessage(string message, T& var)
{
    cout << string(80, '-') << endl;
    cout << message;
    cin >> var;
    cout << string(80, '-') << endl;
}

#endif
