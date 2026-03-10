#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "utils.cpp"
#include "Wallet.h"

using namespace std;

/*
   Program Description:
     -> Entities
        - User - have a wallet, have a name.
        - Wallet - contains balance
     -> Relationships & Functionalities
        - User can Deposit into Wallet
        - User can withdraw from wallet
        - User can check Wallet Balance
 */

void userDisplay(string user, int &value, int state, float &balance)
{
    if (state == 1)
    {
        cout << "Hello " << user << endl;
        cout << "Choose what to do: " << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Exit" << endl;
        cin >> value;
    }
    else if (state == 2)
    {
        cout << "========== YOUR WALLET =========" << endl;
        cout << "User: " << user << endl;
        cout << "Current Balance: " << balance << endl;
    }
};

void userAction(int value, float amount, string user, float &balance)
{
    switch (value)
    {
    case 1:
        balance += amount;
        cout << user << ", You have successfully deposited " << amount << " Birr" << endl;
        break;
    case 2:
    {
        if (amount > balance)
        {
            cout << "Oops! You're broke for that!" << endl;
        }
        else
        {
            balance -= amount;
            cout << user << ", You have successfully withdrawn " << amount << " Birr" << endl;
        }
    }
    break;
    default:
        break;
    }
}

void mainLogic(int &value, string userName, float &balance)
{
    float amount;
    switch (value)
    {
    case 1:
    {
        cout << "Enter Amount to be Deposited: ";
        cin >> amount;
        userAction(value, amount, userName, balance);
        userDisplay(userName, value, 1, balance);
    }
    break;
    case 2:
    {
        cout << "Enter Amount to withdraw: ";
        cin >> amount;
        userAction(value, amount, userName, balance);
        userDisplay(userName, value, 1, balance);
    }
    break;
    case 3:
    {
        userDisplay(userName, value, 2, balance);
        userDisplay(userName, value, 1, balance);
    }
    break;
    case 4:
        exit(0);
        break;
    default:
        break;
    }
}

void initialPage(int &initialVal)
{
    cout << "========== ATM SIMULATOR =========" << endl;
    cout << "Choose what you would do" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cin >> initialVal;
}

int main()
{

    Wallet myWallet;
    vector<Wallet> masterData;

    string line;
    int currentIndex;
    int value;
    ifstream userInfo("userInfo.txt");
    string masterString = "";
    if (userInfo)
    {
        while (getline(userInfo, line))
        {
            // cout << "Found: " << line << endl;
            cout << line << endl;
            vector<string> data = splitString(line);
            Wallet tempWallet;
            tempWallet.userName = data[0];
            tempWallet.password = data[1];
            tempWallet.balance = stof(data[2]);
            masterData.push_back(tempWallet);
        }
    }

    cout << "Master String: " << masterString << endl;

    int initialVal;

    bool authenticated = false;

    while (!authenticated)
    {
        initialPage(initialVal);

        if (initialVal == 1)
        {
            cout << "Enter User Name: ";
            cin >> myWallet.userName;
            if (checkNameExist(masterData, myWallet.userName))
            {
                cout << "Provided name already exists." << endl;
                continue;
            }

            cout << "Enter Account Password: ";
            cin >> myWallet.password;
            cout << "Enter Currect Account Balance: ";
            cin >> myWallet.balance;
            masterData.push_back(myWallet);
            for (Wallet w : masterData)
            {
                masterString += w.userName + " " + w.password + " " + to_string(w.balance) + '\n';
            }
            currentIndex = masterData.size() - 1;
            cout << masterString;
            cout << myWallet.userName << " " << myWallet.password << " " << myWallet.balance << endl;
            updateFile(masterData);
            authenticated = true;
        }
        else if (initialVal == 2)
        {
            string tempName;
            string tempPassword;
            cout << "Enter User Name: ";
            cin >> tempName;
            cout << "Enter Password: ";
            cin >> tempPassword;

            if (masterData.empty())
            {
                cout << "Error: No previous accounts exist." << endl;
                continue;
            }
            int checkSuccess = 0;
            int foundIndex = -1;
            for (int i = 0; i < masterData.size(); i++)
            {
                if (tempName == masterData[i].userName)
                {
                    foundIndex = i;
                    cout << "Wrong Password";
                    continue;
                }
            }
            if (foundIndex == -1)
            {
                cout << "This Account doesn't exist." << endl;
                continue;
            }
            else
            {
                if (tempPassword == masterData[foundIndex].password)
                {
                    cout << "Successfully Logged In!" << endl;
                    cout << "Welcome " << masterData[foundIndex].userName << endl;
                    currentIndex = foundIndex;
                    authenticated = true;
                }else {
                    cout << "Wrong Password! Try Again!" << endl;
                    continue;
                }
            }
        }
    }

    userDisplay(masterData[currentIndex].userName, value, 1, masterData[currentIndex].balance);
    while (value != 4)
    {
        mainLogic(value, masterData[currentIndex].userName, masterData[currentIndex].balance);
        updateFile(masterData);
    }
    return 0;
}