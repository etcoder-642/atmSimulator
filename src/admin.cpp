#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>

#include "../include/Wallet.h"
#include "../include/display.h"
#include "../include/utils.h"

using namespace std;

void showAnalytics(const vector<Wallet> &masterData)
{
    float totalLiquidity = 0;
    float transactionVol = 0;
    float netFlow = 0;
    int transactionNum = 0;
    float avWealth = 0;
    int totalUsers = masterData.size();
    for (int i = 0; i < masterData.size(); i++)
    {
        totalLiquidity += masterData[i].balance;
        for (int j = 0; j < masterData[i].txRecord.size(); j++)
        {
            netFlow += masterData[i].txRecord[j];
            transactionNum++;
            if (masterData[i].txRecord[j] > 0)
            {
                transactionVol += masterData[i].txRecord[j];
            }
            else if (masterData[i].txRecord[j] < 0)
            {
                transactionVol += -masterData[i].txRecord[j];
            }
            else
                continue;
        }
    }
    avWealth = totalLiquidity / totalUsers;
    displayAdminAnalytics(totalLiquidity, transactionVol, netFlow, transactionNum, totalUsers, avWealth);
}

void showAllAccounts(const vector<Wallet> &masterData)
{
    vector<int> trxnNums;
    for (int i = 0; i < masterData.size(); i++)
    {
        int tempNum = 0;
        for (int j = 0; j < masterData[i].txRecord.size(); j++)
        {
            tempNum++;
        }
        trxnNums.push_back(tempNum);
    }
    displayAllAccounts(masterData, trxnNums);
}

void systemWideActions(const vector<Wallet>& masterData)
{
    int systemActionChoice;
    displaySystemActions(systemActionChoice);
}

int handleAdminSession(Admin& adminAcc, const vector<Wallet>& masterData)
{
    bool adminAuthenticated = false;
    int adminChoice;
    while (!adminAuthenticated)
    {
        loadAdminData(adminAcc);
        if (adminAcc.adminName.empty())
        {
            displayAdminSignUpPage(adminAcc);
            uploadAdminData(adminAcc);
            adminAuthenticated = true;
        }
        else
        {
            string tempAdminName;
            string tempAdminPassword;
            displayAdminLogInPage(tempAdminName, tempAdminPassword);
            if (authenticateAdmin(adminAcc, tempAdminName, tempAdminPassword))
                adminAuthenticated = true;
            else
            {
                cout << "ADMIN AUTHENTICATION FAILED!" << endl;
                adminAuthenticated = false;
            }
        }
    }
    while (true)
    {
        displayAdminDashBoard(adminChoice, adminAcc.adminName);
        switch (adminChoice)
        {
        case 1:
            showAnalytics(masterData);
            continue;
            break;
        case 2:
            showAllAccounts(masterData);
            continue;
            break;
        case 3:
            systemWideActions(masterData);
            continue;
            break;
        case 4:
            // userSpecificActions(masterData);
            continue;
            break;
        case 5:
            return 5;
            break;
        case 6:
            return 6;
            break;
        }
    }
    return 0;
}
