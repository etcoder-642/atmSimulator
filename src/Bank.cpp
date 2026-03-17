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
        if (bank[i].checkNameExists(name))
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
        userInfo << bank[i].getUserName() << " " << bank[i].getPassword() << " " << bank[i].getState() << " " << bank[i].getBalance() << endl;
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
        for (int j = 0; j < bank[i].getTxRecord().size(); j++)
        {
            transaction << " " << bank[i].getTxRecord()[j];
        }
        transaction << endl;
    }
    transaction.close();
}

void Bank::handleMoneyTransfer(int index, string receiverName, float amount)
{
    bool checkSuccess = false;
    if (bank[index].getBalance() < amount)
    {
        cout << "You don't have enough Amount!" << endl;
        return;
    }
    for (int i = 0; i < bank.size(); i++)
    {
        if (receiverName == bank[i].getUserName())
        {
            bank[index].withdraw(amount);
            bank[i].deposit(amount);
            bank[index].setTxRecord(-amount);
            bank[i].setTxRecord(amount);
            cout << "Money Transfer Successful!" << endl;
            cout << amount << " Birr withdrawn from: " << bank[index].getUserName() << endl;
            cout << amount << " Birr deposited to: " << bank[i].getUserName() << endl;
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
            tempWallet.setUserName(data[0]);
            tempWallet.setPassword(data[1]);
            tempWallet.setState((data[2] == "1") ? true : false);
            tempWallet.setBalance(stof(data[3]));
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
                bank[stoi(data[0])].setTxRecord(stof(data[i]));
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
            if (tempName == bank[i].getUserName())
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
            if (tempPassword == bank[foundIndex].getPassword())
            {
                cout << "Successfully Logged In!" << endl;
                cout << "Welcome " << bank[foundIndex].getUserName() << endl;
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
        bank[i].deposit(amount);
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
    bank[index].freeze();
}

void Bank::unfreezeAccount(int index)
{
    bank[index].unfreeze();
}

void Bank::depositToAccount(int index, float amount)
{
    bank[index].deposit(amount);
}

void Bank::deductFromAccount(int index, float amount)
{
    if (bank[index].withdraw(amount) == false)
    {
        cout << "You don't have enough Amount!" << endl;
        return;
    }
;
}

void Bank::setPassword(int index, string newPassword)
{
    bank[index].setPassword(newPassword);
}

void Bank::deleteAccount(int index)
{
    bank.erase(bank.begin() + index);
}

void Bank::freezeAllAccounts()
{
    for (int i = 0; i < bank.size(); i++)
    {
        bank[i].setState(true);
    }
}

void Bank::unfreezeAllAccounts()
{
    for (int i = 0; i < bank.size(); i++)
    {
        bank[i].setState(false);
    }
}