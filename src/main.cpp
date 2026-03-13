#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "../include/Wallet.h"
#include "../include/display.h"
#include "../include/utils.h"

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

void accountAction(int value, float amount, vector<Wallet> &data, int num)
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

void mainLogic(int &value, vector<Wallet> &data, int num, int &initialVal)
{
    float amount;
    switch (value)
    {
    case 1:
    {
        cout << "Enter Amount to be Deposited: ";
        cin >> amount;
        accountAction(value, amount, data, num);
        userDisplay(data[num].userName, value, data[num].balance);
    }
    break;
    case 2:
    {
        cout << "Enter Amount to withdraw: ";
        cin >> amount;
        accountAction(value, amount, data, num);
        userDisplay(data[num].userName, value, data[num].balance);
    }
    break;
    case 3:
    {
        displayBalance(data[num].userName, data[num].balance);
        userDisplay(data[num].userName, value, data[num].balance);
    }
    break;
    case 4:
    {
        displayTransactionHistory(data, num);
        userDisplay(data[num].userName, value, data[num].balance);
    }
    break;
    case 5:
    {
        string receiverName;
        float sentAmount;
        cout << "Enter Name of Person you want to transfer to: ";
        cin >> receiverName;
        cout << "Enter Amount to send: ";
        cin >> sentAmount;
        handleMoneyTransfer(data, num, receiverName, sentAmount);
        userDisplay(data[num].userName, value, data[num].balance);
    }
    break;
    case 6:
    {
        initialPage(initialVal);
    }
    break;
    case 7:
    {
    }
    break;
    case 8:
        break;
    default:
        break;
    }
}

int main()
{

    Wallet myWallet;
    vector<Wallet> masterData;

    int initialVal;
    int currentIndex;
    int value;
    string masterString = "";

    loadUserData(masterData);
    loadTransactionData(masterData);
 
    while (value != 8 && initialVal != 4)
    {
        value = 0;

        // cout << "Master String: " << masterString << endl;

        bool authenticated = false;

        while (!authenticated && initialVal != 4)
        {
            initialPage(initialVal);

            switch (initialVal)
            {
            case 1:
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
                break;
            case 2:
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
                    }
                    else
                    {
                        cout << "Wrong Password! Try Again!" << endl;
                        continue;
                    }
                }
            }
               break;
            case 3:
            {

            }
               break;
            case 4:
                break;
            default:
                break;
            }
        }
        if(initialVal == 4) break;

        userDisplay(masterData[currentIndex].userName, value, masterData[currentIndex].balance);
        while (value != 8 && value != 6)
        {
            mainLogic(value, masterData, currentIndex, initialVal);
            updateTransaction(masterData, currentIndex);
            updateFile(masterData);
            // for (Wallet w : masterData)
            // {
            //     masterString += w.userName + " " + w.password + " " + to_string(w.balance) + " " + to_string(w.txRecord[0]) + " " + to_string(w.txRecord[1]);
            // }
            // cout << masterString;
        }
    }
    return 0;
}