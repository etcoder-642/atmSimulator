#ifndef WALLET_H
#define WALLET_H

#include <string>

using namespace std;

struct Wallet
{
    float balance = 0;
    string userName;
    string password;
};

#endif