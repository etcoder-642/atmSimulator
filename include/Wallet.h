#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>

using namespace std;

struct Wallet
{
    float balance = 0;
    string userName;
    string password;
    vector<float> txRecord;
};

struct Admin
{
    string adminName;
    string adminPassword;
};

#endif