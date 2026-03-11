#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "utils.h"
#include "Wallet.h"
#include "display.h"

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


void userAction(int value, float amount, vector<Wallet>& data, int num)
{
    switch (value)
    {
    case 1:
        data[num].balance += amount;
        cout << data[num].userName << ", You have successfully deposited " << amount << " Birr" << endl;
        data[num].txRecord.push_back(amount);
        break;
    case 2:
    {
        if (amount > data[num].balance)
        {
            cout << "Oops! You're broke for that!" << endl;
        }
        else
        {
            data[num].balance -= amount;
            cout << data[num].userName << ", You have successfully withdrawn " << amount << " Birr" << endl;
            data[num].txRecord.push_back(-amount);
        }
    }
    break;
    default:
        break;
    }
}

void mainLogic(int &value, vector<Wallet>& data, int num)
{
    float amount;
    switch (value)
    {
    case 1:
    {
        cout << "Enter Amount to be Deposited: ";
        cin >> amount;
        userAction(value, amount, data, num);
        userDisplay(data[num].userName, value, 1, data[num].balance);
    }
    break;
    case 2:
    {
        cout << "Enter Amount to withdraw: ";
        cin >> amount;
        userAction(value, amount, data, num);
        userDisplay(data[num].userName, value, 1, data[num].balance);
    }
    break;
    case 3:
    {
        userDisplay(data[num].userName, value, 2, data[num].balance);
        userDisplay(data[num].userName, value, 1, data[num].balance);
    }
    break;
    case 4:
    {
        displayTransactionHistory(data, num);
        userDisplay(data[num].userName, value, 1, data[num].balance);
    }
    case 5:
        exit(0);
        break;
    default:
        break;
    }
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
            vector<string> data = splitString(line);
            Wallet tempWallet;
            tempWallet.userName = data[0];
            tempWallet.password = data[1];
            tempWallet.balance = stof(data[2]);
            masterData.push_back(tempWallet);
        }
    }

    ifstream transaction("transaction.txt");
    if(transaction) {
        
    }

    // cout << "Master String: " << masterString << endl;

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
            // for (Wallet w : masterData)
            // {
            //     masterString += w.userName + " " + w.password + " " + to_string(w.balance) + '\n';
            // }
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
                    break;
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
    while (value != 5)
    {
        mainLogic(value, masterData, currentIndex);
        updateTransaction(masterData, currentIndex);
        updateFile(masterData);
            // for (Wallet w : masterData)
            // {
            //     masterString += w.userName + " " + w.password + " " + to_string(w.balance) + " " + to_string(w.txRecord[0]) + " " + to_string(w.txRecord[1]);
            // }
            // cout << masterString;
        // updateTransactionVector(allTransactions, masterData);
    }
    return 0;
}