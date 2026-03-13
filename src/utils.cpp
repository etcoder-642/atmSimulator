#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "../include/Wallet.h"

using namespace std;

bool checkFile(string fileName)
{
    ifstream file(fileName);
    if (file)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> splitString(string str)
{
    vector<string> a;
    string temp;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
        {
            temp += str[i];
        }
        else
        {
            a.push_back(temp);
            temp = "";
        }
    }
    if (!temp.empty())
    {
        a.push_back(temp);
    }
    return a;
}

void updateFile(const vector<Wallet> &data)
{
    ofstream userInfo("data/userInfo.txt");
    for (int i = 0; i < data.size(); i++)
    {
        userInfo << data[i].userName << " " << data[i].password << " " << data[i].balance << endl;
    }
    userInfo.close();
}

void updateTransaction(vector<Wallet> &data, int num)
{
    ofstream transaction("data/transaction.txt");
    for (int i = 0; i < data.size(); i++)
    {
        transaction << i;
        for (int j = 0; j < data[i].txRecord.size(); j++)
        {
            transaction << " " << data[i].txRecord[j];
        }
        transaction << endl;
    }
    transaction.close();
}

bool checkNameExist(const vector<Wallet> &data, string name)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].userName == name)
        {
            return true;
        }
    }
    return false;
}

void handleMoneyTransfer(vector<Wallet> &data, int index, string receiverName, float amount)
{
    bool checkSuccess = false;
    if (data[index].balance < amount)
    {
        cout << "You don't have enough Amount!" << endl;
        return;
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (receiverName == data[i].userName)
        {
            data[index].balance -= amount;
            data[i].balance += amount;
            data[index].txRecord.push_back(-amount);
            data[i].txRecord.push_back(amount);
            cout << "Money Transfer Successful!" << endl;
            cout << amount << " Birr withdrawn from: " << data[index].userName << endl;
            cout << amount << " Birr deposited to: " << data[i].userName << endl;
            checkSuccess = true;
        }
    }
    if (!checkSuccess)
    {
        cout << "ERROR: TRANSFER PROCESS FAILED!";
    }
}

void loadUserData(vector<Wallet> &masterData)
{
    ifstream userInfo("data/userInfo.txt");
    string line;
    if (userInfo)
    {
        while (getline(userInfo, line))
        {
            vector<string> data = splitString(line);
            Wallet tempWallet;
            tempWallet.userName = data[0];
            tempWallet.password = data[1];
            tempWallet.balance = stof(data[2]);
            masterData.push_back(tempWallet);
        }
    }
}

void loadTransactionData(vector<Wallet> &masterData)
{
    ifstream transaction("data/transaction.txt");
    string line;
    if (transaction)
    {
        while (getline(transaction, line))
        {
            vector<string> data = splitString(line);
            for (int i = 1; i < data.size(); i++)
            {
                masterData[stoi(data[0])].txRecord.push_back(stof(data[i]));
            }
        }
    }
}
