#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "include/Wallet.h"

using namespace std;

void updateFile(const vector<Wallet> &data)
{
    ofstream userInfo("data/userInfo.txt");
    if(data.empty()){
        userInfo << ' ';
        return;
    }
    for (int i = 0; i < data.size(); i++)
    {
        userInfo << data[i].userName << " " << data[i].password << " " << data[i].state << " " << data[i].balance << endl;
    }
    userInfo.close();
}
