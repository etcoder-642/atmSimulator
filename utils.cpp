#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Wallet.h"

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
    ofstream userInfo("userInfo.txt");
    for (int i = 0; i < data.size(); i++)
    {
        userInfo << data[i].userName << " " << data[i].password << " " << data[i].balance << endl;
    }
    userInfo.close();
}

void updateTransaction(vector<Wallet>& data, int num){
    ofstream transaction("transaction.txt");
    for(int i = 0; i < data.size(); i++){
        transaction << i;
        for(int j = 0; j < data[i].txRecord.size(); j++){
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
