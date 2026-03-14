#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../include/Wallet.h"

using namespace std;

void userDisplay(string user, int &value, float &balance)
{
    cout << string(80, '=') << endl;
    cout << "Choose what to do: " << endl;
    cout << string(80, '-') << endl;
    cout << "1. Deposit Money" << endl;
    cout << "2. Withdraw Money" << endl;
    cout << "3. Check Balance" << endl;
    cout << "4. See Transaction History" << endl;
    cout << "5. Transfer Money" << endl;
    cout << "6. Log Out" << endl;
    cout << "7. Exit" << endl;
    cout << string(80, '-') << endl;
    cin >> value;
    cout << string(80, '=') << endl;
    cout << endl;
};

void displayBalance(string user, float balance)
{
    cout << string(80, '-') << endl;
    cout << "====================== YOUR WALLET =============================================" << endl;
    cout << setfill('.');
    cout << left << setw(20) << "User: " << user << endl;
    cout << left << setw(20) << "Current Balance: " << fixed << setprecision(2) << balance << endl;
    cout << setfill(' ');
    cout << string(80, '-') << endl;
    cout << endl;
}

void initialPage(int &initialVal)
{
    cout << string(80, '=') << endl;
    cout << "====================== ATM SIMULATOR ===========================================" << endl;
    cout << "Choose what you would do" << endl;
    cout << string(80, '-') << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Log In as an ADMIN" << endl;
    cout << "4. exit" << endl;
    cout << string(80, '-') << endl;
    cin >> initialVal;
    cout << string(80, '=') << endl;
    cout << endl;
}

void displayTransactionHistory(const vector<Wallet> &data, int num)
{
    cout << string(80, '=') << endl;
    cout << "============================ " << data[num].userName << "'s TRANSACTION HISTORY ===================" << endl;
    if (data[num].txRecord.size() == 0)
    {
        cout << " YOU HAVE NO TRANSACTION HISTORY" << endl;
        cout << string(80, '=') << endl;
        cout << endl;
        return;
    }
    for (int i = 0; i < data[num].txRecord.size(); i++)
    {
        if (data[num].txRecord[i] > 0)
        {
            cout << "Deposit: " << fixed << setprecision(2) << data[num].txRecord[i] << endl;
        }
        else if (data[num].txRecord[i] < 0)
        {
            cout << "Withdraw: " << fixed << setprecision(2) << data[num].txRecord[i] << endl;
        }
    }
    cout << string(80, '=') << endl;
    cout << endl;
}

void displayAdminDashBoard(int &adminChoice, string admin)
{
    cout << string(80, '-') << endl;
    cout << setfill('=');
    cout << "========================= WELCOME " << left << setw(46) << admin << endl;
    cout << setfill(' ');

    cout << "Chose what to do: " << endl;
    cout << "1. See system-wide analytics" << endl;
    cout << "2. See User's Accounts" << endl;
    cout << "3. Take system-wide actions" << endl;
    cout << "4. Take User-specific actions" << endl;
    cout << "5. Log Out" << endl;
    cout << "6. exit" << endl;

    cin >> adminChoice;
    cout << string(80, '-') << endl;
    cout << endl;
}

void displaySignUpPage(Wallet &myWallet)
{
    cout << "Enter User Name: ";
    cin >> myWallet.userName;
    cout << "Enter Account Password: ";
    cin >> myWallet.password;
    cout << "Enter Current Account Balance: ";
    cin >> myWallet.balance;
}

void displayLogInPage(string &tempName, string &tempPassword)
{
    cout << "Enter User Name: ";
    cin >> tempName;
    cout << "Enter Password: ";
    cin >> tempPassword;
}

void displayAdminSignUpPage(Admin &adminAcc)
{
    cout << string(80, '=') << endl;
    cout << "NO ADMIN ACCOUNT HAVE BEEN CREATED!" << endl;
    cout << string(80, '-') << endl;
    cout << "Create Admin Account" << endl;
    cout << "Enter Admin Name: ";
    cin >> adminAcc.adminName;
    cout << "Enter Admin Password: ";
    cin >> adminAcc.adminPassword;
    cout << string(80, '=') << endl;
    cout << endl;
}

void displayAdminLogInPage(string &tempName, string &tempPassword)
{
    cout << string(80, '-') << endl;
    cout << "Log In to Admin Account" << endl;
    cout << "Enter Admin Name: ";
    cin >> tempName;
    cout << "Enter Admin Password: ";
    cin >> tempPassword;
    cout << string(80, '-') << endl;
}

void displayAdminAnalytics(float totalLiquidity, float transactionVol, float netFlow, int transactionNum, int totalUsers, float avWealth)
{
    cout << string(80, '=') << endl;
    cout << "=============================== SYSTEM ANALYTICS ===============================" << endl;
    cout << left << setw(70) << "METRIC" << "VALUE" << endl;
    cout << string(80, '-') << endl;
    cout << setfill('.');
    cout << left << setw(70) << "Total Liquidity: " << fixed << setprecision(2) << totalLiquidity << endl;
    cout << left << setw(70) << "Total Transaction Volume: " << fixed << setprecision(2) << transactionVol << endl;
    cout << left << setw(70) << "System Net Flow: " << fixed << setprecision(2) << netFlow << endl;
    cout << left << setw(70) << "Total Number of Transactions: " << transactionNum << endl;
    cout << left << setw(70) << "Total Number of Users: " << totalUsers << endl;
    cout << left << setw(70) << "Average Balance of Users: " << fixed << setprecision(2) << avWealth << endl;
    cout << setfill(' ');

    cout << string(80, '=') << endl;
}

void displayAllAccounts(const vector<Wallet> &masterData, vector<int> trxnNums)
{
    cout << string(80, '-') << endl;
    cout << string(80, '=') << endl;
    cout << "================================= USER ACCOUNTS ================================" << endl;
    cout << left << setw(3) << "ID"
         << left << setw(23) << "USER NAME"
         << left << setw(23) << "BALANCE"
         << left << setw(31) << "TOTAL NUMBER OF TRANSACTIONS" << endl;

    for (int i = 0; i < masterData.size(); i++)
    {
        cout << left << setw(3) << i
             << left << setw(23) << masterData[i].userName
             << left << setw(23) << fixed << setprecision(2) << masterData[i].balance
             << left << setw(31) << trxnNums[i] << endl;
    }
    cout << string(80, '=') << endl;
    cout << endl;
}

void displaySystemActions(int &value)
{
    cout << string(80, '=') << endl;
    cout << "Choose What to do: " << endl;
    cout << string(80, '-') << endl;
    cout << "1. Give Global Bonus" << endl;
    cout << "2. Deduct Global Fee" << endl;
    cout << "3. System Freeze (WARNING!)" << endl;
    cout << "4. System Unfreeze" << endl;
    cout << "5. Wipe All User Data (DANGER!!!)" << endl;
    cout << "6. Back" << endl;
    cout << string(80, '-') << endl;
    cin >> value;
    cout << string(80, '=') << endl;
    cout << endl;
}

void displayUserSpecificActions(int &value)
{
    cout << string(80, '=') << endl;
    cout << "Choose What to do: " << endl;
    cout << string(80, '-') << endl;
    cout << "1. View User Profile" << endl;
    cout << "2. Freeze Account" << endl;
    cout << "3. Unfreeze Account" << endl;
    cout << "4. Direct Account Deposit" << endl;
    cout << "5. Direct Account Deduction" << endl;
    cout << "6. Reset Password" << endl;
    cout << "7. Delete Account" << endl;
    cout << "8. Back" << endl;
    cout << string(80, '-') << endl;
    cin >> value;
    cout << string(80, '=') << endl;
    cout << endl;
}

void displayUserInfo(vector<Wallet> masterData, int num)
{
    cout << string(80, '=') << endl;
    cout << left << setw(60) << "User Name: " << masterData[num].userName << endl;
    cout << left << setw(60) << "User Balance: " << masterData[num].balance << endl;
    cout << string(80, '-') << endl;
    cout << setw(80) << "User Transaction History" << endl;
    cout << string(80, '-') << endl;
    cout << left << setw(60) << "Transaction Type" << "Volume" << endl;
    for (int i = 0; i < masterData[num].txRecord.size(); i++)
    {
        if (masterData[num].txRecord[i] > 0)
        {
            cout << left << setw(60) << "Deposit" << masterData[num].txRecord[i] << endl;
        }
        else
        {
            cout << left << setw(60) << "Withdraw" << masterData[num].txRecord[i] << endl;
        }
    }
    cout << string(80, '=') << endl;
    cout << endl;
}

void displaySystemWideAccountChange(float amount)
{
    cout << string(80, '-') << endl;
    if (amount > 0)
    {
        cout << "Successfully deposited " << amount << " for each accounts." << endl;
    }
    else
    {
        cout << "Successfully Withdrawn " << amount << " for each accounts." << endl;
    }
    cout << string(80, '=') << endl;
}

void displayAccountFreezeMessage(string name)
{
    cout << string(80, '=') << endl;
    cout << "User " << name << "your Account have been Frozen by the Admin." << endl;
    cout << "NO ACTIONS CAN'T BE PERFORMED CONTACT YOUR ADMIN" << endl;
    cout << string(80, '=') << endl;
}

void displaySpecialMessage(string message)
{
    cout << string(80, '=') << endl;
    cout << message << endl;
    cout << string(80, '=') << endl;  
    cout << endl;  
}

