#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>

#include "../include/Wallet.h"
#include "../include/display.h"
#include "../include/utils.h"
#include "../include/Bank.h"

using namespace std;

void showAnalytics(Bank &bank)
{
    vector<Wallet> wallets = bank.getWallet();
    float totalLiquidity = 0;
    float transactionVol = 0;
    float netFlow = 0;
    int transactionNum = 0;
    float avWealth = 0;
    int totalUsers = bank.size();
    for (int i = 0; i < bank.size(); i++)
    {
        totalLiquidity += wallets[i].getBalance();
        for (int j = 0; j < wallets[i].getTxRecord().size(); j++)
        {
            netFlow += wallets[i].getTxRecord()[j];
            transactionNum++;
            if (wallets[i].getTxRecord()[j] > 0)
            {
                transactionVol += wallets[i].getTxRecord()[j];
            }
            else if (wallets[i].getTxRecord()[j] < 0)
            {
                transactionVol += -wallets[i].getTxRecord()[j];
            }
            else
                continue;
        }
    }
    avWealth = totalLiquidity / totalUsers;
    displayAdminAnalytics(totalLiquidity, transactionVol, netFlow, transactionNum, totalUsers, avWealth);
}

void showAllAccounts(Bank &mainbank)
{
    vector<Wallet> wallets = mainbank.getWallet();
    vector<int> trxnNums;
    for (int i = 0; i < mainbank.size(); i++)
    {
        int tempNum = 0;
        for (int j = 0; j < wallets[i].getTxRecord().size(); j++)
        {
            tempNum++;
        }
        trxnNums.push_back(tempNum);
    }
    displayAllAccounts(mainbank, trxnNums);
}

void systemWideActions(Bank &bank)
{
    vector<Wallet> wallets = bank.getWallet();
    int systemActionChoice;
    while (systemActionChoice != 6)
    {
        displaySystemActions(systemActionChoice);
        switch (systemActionChoice)
        {
        case 1:
        {
            int amount;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            bank.systemWideAmountChange(amount);
            displaySystemWideAccountChange(amount);
        }
        break;
        case 2:
        {
            int amount;
            cout << "Enter Amount to Withdrawn: ";
            cin >> amount;
            bank.systemWideAmountChange(-amount);
            displaySystemWideAccountChange(-amount);
        }
        break;
        case 3:
        {
            int userChoice;
            receiveMessage("Are you sure you want to do it? (Enter 1 to Cancel or 2 to Proceed): ", userChoice);
            if (userChoice == 1)
                continue;
            else
            {
                bank.freezeAllAccounts();
                bank.updateFile();
                displaySpecialMessage("All Accounts Successfully Frozen");
            }
        }
        break;
        case 4:
        {
            bank.unfreezeAllAccounts();
            bank.updateFile();
            displaySpecialMessage("All Accounts Successfully Unfrozen");
        }
        break;
        case 5:
        {
            int userChoice;
            receiveMessage("Are you sure you want to do it? (Enter 1 to cancel or 2 to proceed): ", userChoice);
            if(userChoice == 1) continue;
            else {
                bank.deleteAllAccounts();
                bank.updateFile();
                bank.updateTransaction();
                displaySpecialMessage("ALL ACCOUNTS HAVE SUCCESSFULLY BEEN ERASED!");
            }
        }
        default:
            break;
        }
    }
}

void userSpecificActions(Bank &bank)
{
    vector<Wallet> wallets = bank.getWallet();
    int userActionChoice;
    while (userActionChoice != 8)
    {
        displayUserSpecificActions(userActionChoice);
        switch (userActionChoice)
        {
        case 1:
        {
            int tempNum;
            receiveMessage("Enter User Index: ", tempNum);
            displayUserInfo(bank, tempNum);
        }
        break;
        case 2:
        {
            int tempNum;
            receiveMessage("Enter Index of Account to Freeze: ", tempNum);
            bank.freezeAccount(tempNum);
            bank.updateFile();
            displaySpecialMessage("Account Successfully Frozen!");
        }
        break;
        case 3:
        {
            int tempNum;
            receiveMessage("Enter Index of Account to Unfreeze: ", tempNum);
            bank.unfreezeAccount(tempNum);
            bank.updateFile();
            displaySpecialMessage("Account Successfully Unfrozen!");
        }
        break;
        case 4:
        {
            int tempNum;
            float amount;
            receiveMessage("Enter Index of Account to Deposit to: ", tempNum);
            receiveMessage("Enter Amount to Deposit: ", amount);
            bank.depositToAccount(tempNum, amount);
            bank.updateFile();
            bank.updateTransaction();
            string tempString = "Successfully Deposited " + to_string(amount) + " Birr to " + wallets[tempNum].getUserName();
            displaySpecialMessage(tempString);
        }
        break;
        case 5:
        {
            int tempNum;
            float amount;
            receiveMessage("Enter Index of Account to Deduct from: ", tempNum);
            receiveMessage("Enter Amount to be Deducted: ", amount);
            bank.deductFromAccount(tempNum, amount);
            bank.updateFile();
            bank.updateTransaction();
            string tempString = "Successfully Deducted " + to_string(amount) + " Birr from " + wallets[tempNum].getUserName();
            displaySpecialMessage(tempString);
        }
        break;
        case 6:
        {
            int tempNum;
            int num;
            receiveMessage("Enter Index of Account to Reset Password: ", tempNum);
            receiveMessage("Are you sure you want to reset " + wallets[tempNum].getUserName() + "'s Password ? (Enter 1 to Cancel or 2 to Proceed): ", num);
            if(num == 1) continue;
            else {
                bank.setPassword(tempNum, "12345678");
                bank.updateFile();
                displaySpecialMessage(wallets[tempNum].getUserName() + "'s Password have been Successfully Resetted.");
            }
        }
        break;
        case 7:
        {
            int tempNum;
            int num;
            receiveMessage("Enter Index of Account to be Deleted: ", tempNum);
            receiveMessage("Are you sure you want to Delete " + wallets[tempNum].getUserName() + "'s Account? (Enter 1 to Cancel or 2 to Proceed): ", num);
            if(num == 1) continue;
            else {
                displaySpecialMessage(wallets[tempNum].getUserName() + "'s Account have been successfully deleted.");
                bank.deleteAccount(tempNum);
                bank.updateFile();
                bank.updateTransaction();
            }
        }
        default:
            break;
        }
    }
}


int handleAdminSession(Admin &adminAcc, Bank& bank)
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
            showAnalytics(bank);
            continue;
            break;
        case 2:
            showAllAccounts(bank);
            continue;
            break;
        case 3:
            systemWideActions(bank);
            continue;
            break;
        case 4:
            userSpecificActions(bank);
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
