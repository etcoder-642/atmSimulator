#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../include/Wallet.h"
#include "../include/Bank.h"
#include "../include/utils.h"
using namespace std;

void Bank::addValue(Wallet myWallet){
    bank.push_back(myWallet);
}

int Bank::size(){
    return bank.size();
}

bool Bank::checkNameExist(string name)
{
    for (int i = 0; i < bank.size(); i++)
    {
        if (bank[i].userName == name)
        {
            return true;
        }
    }
    return false;
}

void Bank::updateFile()
{
    ofstream userInfo("bank/userInfo.txt");
    if (bank.empty())
    {
        userInfo << ' ';
        return;
    }
    for (int i = 0; i < bank.size(); i++)
    {
        userInfo << bank[i].userName << " " << bank[i].password << " " << bank[i].state << " " << bank[i].balance << endl;
    }
    userInfo.close();
}

void Bank::updateTransaction()
{
    ofstream transaction("data/transaction.txt");
    if (bank.empty())
    {
        transaction << ' ';
        return;
    }
    for (int i = 0; i < bank.size(); i++)
    {
        transaction << i;
        for (int j = 0; j < bank[i].txRecord.size(); j++)
        {
            transaction << " " << bank[i].txRecord[j];
        }
        transaction << endl;
    }
    transaction.close();
}

void Bank::handleMoneyTransfer(int index, string receiverName, float amount)
{
    bool checkSuccess = false;
    if (bank[index].balance < amount)
    {
        cout << "You don't have enough Amount!" << endl;
        return;
    }
    for (int i = 0; i < bank.size(); i++)
    {
        if (receiverName == bank[i].userName)
        {
            bank[index].balance -= amount;
            bank[i].balance += amount;
            bank[index].txRecord.push_back(-amount);
            bank[i].txRecord.push_back(amount);
            cout << "Money Transfer Successful!" << endl;
            cout << amount << " Birr withdrawn from: " << bank[index].userName << endl;
            cout << amount << " Birr deposited to: " << bank[i].userName << endl;
            checkSuccess = true;
        }
    }
    if (!checkSuccess)
    {
        cout << "ERROR: TRANSFER PROCESS FAILED!";
    }
}

void Bank::loadUserData()
{
    ifstream userInfo("data/userInfo.txt");
    string line;
    if (userInfo && userInfo.peek() != EOF)
    {
        while (getline(userInfo, line))
        {
            if (line.empty())
                continue;
            vector<string> data = splitString(line);
            Wallet tempWallet;
            tempWallet.userName = data[0];
            tempWallet.password = data[1];
            tempWallet.state = (data[2] == "1") ? true : false;
            tempWallet.balance = stof(data[3]);
            bank.push_back(tempWallet);
        }
    }
}

void Bank::loadTransactionData()
{
    ifstream transaction("data/transaction.txt");
    string line;
    if (transaction && transaction.peek() != EOF)
    {
        while (getline(transaction, line))
        {
            if (line.empty())
                continue;
            vector<string> data = splitString(line);
            for (int i = 1; i < data.size(); i++)
            {
                bank[stoi(data[0])].txRecord.push_back(stof(data[i]));
            }
        }
    }
}

bool Bank::authenticateUser(string tempName, string tempPassword, int &index)
{
    while (true)
    {
        if (bank.empty())
        {
            cout << "Error: No previous accounts exist." << endl;
            return false;
        }
        int checkSuccess = 0;
        int foundIndex = -1;
        for (int i = 0; i < bank.size(); i++)
        {
            if (tempName == bank[i].userName)
            {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex == -1)
        {
            cout << "This Account doesn't exist." << endl;
            return false;
        }
        else
        {
            if (tempPassword == bank[foundIndex].password)
            {
                cout << "Successfully Logged In!" << endl;
                cout << "Welcome " << bank[foundIndex].userName << endl;
                index = foundIndex;
                return true;
            }
            else
            {
                cout << "Wrong Password! Try Again!" << endl;
                return false;
            }
        }
    }
}

void Bank::systemWideAmountChange(float amount)
{
    for (int i = 0; i < bank.size(); i++)
    {
        bank[i].balance += amount;
    }
    updateFile();
}

void Bank::deleteAllAccounts()
{
    bank.clear();
    bank.shrink_to_fit();
}

void Bank::freezeAccount(int index)
{
    bank[index].state = true;
}

void Bank::unfreezeAccount(int index)
{
    bank[index].state = false;
}

void Bank::depositToAccount(int index, float amount)
{
    bank[index].balance += amount;
    bank[index].txRecord.push_back(amount);
}

void Bank::deductFromAccount(int index, float amount)
{
    if (bank[index].balance < amount)
    {
        cout << "You don't have enough Amount!" << endl;
        return;
    }
    bank[index].balance -= amount;
    bank[index].txRecord.push_back(-amount);
}

void Bank::setPassword(int index, string newPassword)
{
    bank[index].password = newPassword;
}

void Bank::deleteAccount(int index)
{
    bank.erase(bank.begin() + index);
}

void Bank::freezeAllAccounts()
{
    for (int i = 0; i < bank.size(); i++)
    {
        bank[i].state = true;
    }
}

void Bank::unfreezeAllAccounts()
{
    for (int i = 0; i < bank.size(); i++)
    {
        bank[i].state = false;
    }
}