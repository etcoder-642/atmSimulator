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


void accountAction(int value, float amount, vector<Wallet>& data, int num)
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
    ifstream userInfo("data/userInfo.txt");
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

    ifstream transaction("data/transaction.txt");
    if(transaction) {
        while(getline(transaction, line)){
            vector<string> data = splitString(line);
            for(int i = 1; i < data.size();i++){
                masterData[stoi(data[0])].txRecord.push_back(stof(data[i]));
            } 
        }
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

    userDisplay(masterData[currentIndex].userName, value, masterData[currentIndex].balance);
    while (value != 6)
    {
        mainLogic(value, masterData, currentIndex);
        updateTransaction(masterData, currentIndex);
        updateFile(masterData);
            // for (Wallet w : masterData)
            // {
            //     masterString += w.userName + " " + w.password + " " + to_string(w.balance) + " " + to_string(w.txRecord[0]) + " " + to_string(w.txRecord[1]);
            // }
            // cout << masterString;
    }
    return 0;
}