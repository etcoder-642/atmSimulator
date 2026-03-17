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


bool authenticateAdmin(Admin adminAcc, string tempName, string tempPassword)
{
    if(tempName == adminAcc.adminName){
        if(tempPassword == adminAcc.adminPassword){
            cout << "Successfully Logged In" << endl;
            return true;
        }
        cout << "Wrong Password" << endl;
        return false;
    } else return false;
}

void uploadAdminData(const Admin& adminAcc)
{
    ofstream admin("data/admin.txt");
    admin << adminAcc.adminName << " " << adminAcc.adminPassword;
}

void loadAdminData(Admin& adminAcc)
{
    ifstream admin("data/admin.txt");
    string line;
    if(admin)
    {
        while (getline(admin, line))
        {
            vector<string> data = splitString(line);
            adminAcc.adminName = data[0];
            adminAcc.adminPassword = data[1];
        }
        
    }
}