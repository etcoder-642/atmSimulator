#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../include/Wallet.h"
using namespace std;

void Wallet::deposit(float amount)
{
    balance += amount;
    txRecord.push_back(amount);
}

bool Wallet::withdraw(float amount)
{
    if (amount > balance)
    {
        return false;
    }
    balance -= amount;
    txRecord.push_back(-amount);
    return true;
}

void Wallet::freeze()
{
    state = true;
}

void Wallet::unfreeze()
{
    state = false;
}

bool Wallet::checkNameExists(string name){
    return userName == name;
}