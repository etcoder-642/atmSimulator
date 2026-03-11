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

#endif
