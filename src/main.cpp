#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "../include/Wallet.h"
#include "../include/Bank.h"
#include "../include/display.h"
#include "../include/utils.h"
#include "../include/admin.h"

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

void accountAction(int value, float amount, Bank &bank, int num)
{
    vector<Wallet> tempWallet = bank.getWallet();
    switch (value)
    {
    case 1:
        tempWallet[num].setBalance(tempWallet[num].getBalance() + amount);
        cout << tempWallet[num].getUserName() << ", You have successfully deposited " << amount << " Birr" << endl;
        tempWallet[num].setTxRecord(amount);
        break;
    case 2:
    {
        if (amount > tempWallet[num].getBalance())
        {
            cout << "Oops! You're broke for that!" << endl;
        }
        else
        {
            tempWallet[num].setBalance(tempWallet[num].getBalance() - amount);
            cout << tempWallet[num].getUserName() << ", You have successfully withdrawn " << amount << " Birr" << endl;
            tempWallet[num].setTxRecord(-amount);
        }
    }
    break;
    default:
        break;
    }
}

void mainLogic(int &value, Bank &bank, int num, int &initialVal)
{
    float amount;
    switch (value)
    {
    case 1:
    {
        if(bank.getWallet()[num].getState()){
            displayAccountFreezeMessage(bank.getWallet()[num].getUserName());
            userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
            return;
        }
        cout << "Enter Amount to be Deposited: ";
        cin >> amount;
        accountAction(value, amount, bank, num);
        userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
    }
    break;
    case 2:
    {
        if(bank.getWallet()[num].getState()){
            displayAccountFreezeMessage(bank.getWallet()[num].getUserName());
            userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
            return;
        }
        cout << "Enter Amount to withdraw: ";
        cin >> amount;
        accountAction(value, amount, bank, num);
        userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
    }
    break;
    case 3:
    {
        displayBalance(bank.getWallet()[num].getUserName(), bank.getWallet()[num].getBalance());
        userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
    }
    break;
    case 4:
    {
        displayTransactionHistory(bank, num);
        userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
    }
    break;
    case 5:
    {
        if(bank.getWallet()[num].getState()){
            displayAccountFreezeMessage(bank.getWallet()[num].getUserName());
            userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
            return;
        }
        string receiverName;
        float sentAmount;
        cout << "Enter Name of Person you want to transfer to: ";
        cin >> receiverName;
        cout << "Enter Amount to send: ";
        cin >> sentAmount;
        bank.handleMoneyTransfer(num, receiverName, sentAmount);
        userDisplay(bank.getWallet()[num].getUserName(), value, bank.getWallet()[num].getBalance());
    }
    break;
    case 6:
    {
        initialPage(initialVal);
    }
    break;
    case 7:
        break;
    default:
        break;
    }
}

int main()
{

    Bank mainbank;
    Admin adminAcc;

    int initialVal = 0;
    int currentIndex = -1;
    int value = 0;
    string masterString = "";
    string adminPassword = "admin";
    int adminChoice;

    mainbank.loadUserData();
    mainbank.loadTransactionData();

    while (value != 7 && initialVal != 4)
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
                Wallet myWallet;
                displaySignUpPage(myWallet);
                if (mainbank.checkNameExist(myWallet.getUserName()))
                {
                    cout << "Provided name already exists." << endl;
                    continue;
                }
                mainbank.addValue(myWallet);
                // for (Wallet w : masterData)
                // {
                //     masterString += w.getUserName() + " " + w.getPassword() + " " + to_string(w.getBalance()) + '\n';
                // }
                currentIndex = mainbank.size() - 1;
                cout << myWallet.getUserName() << " " << myWallet.getPassword() << " " << myWallet.getBalance() << endl;
                mainbank.updateFile();
                authenticated = true;
            }
            break;
            case 2:
            {
                string tempName;
                string tempPassword;

                displayLogInPage(tempName, tempPassword);
                if (mainbank.authenticateUser(tempName, tempPassword, currentIndex))
                    authenticated = true;
                else
                {
                    cout << "USER AUTHENTICATION FAILED!" << endl;
                    authenticated = false;
                }
            }
            break;
            case 3:
            {
                if(handleAdminSession(adminAcc, mainbank) == 6) 
                {
                    initialVal = 4;
                };
            }
            break;
            case 4:
                break;
            default:
                break;
            }
        }
        if (initialVal == 4)
            break;

        userDisplay(mainbank.getWallet()[currentIndex].getUserName(), value, mainbank.getWallet()[currentIndex].getBalance());
        while (value != 7 && value != 6)
        {
            mainLogic(value, mainbank, currentIndex, initialVal);
            mainbank.updateTransaction();
            mainbank.updateFile();
            // for (Wallet w : masterData)
            // {
            //     masterString += w.getUserName() + " " + w.getPassword() + " " + to_string(w.getBalance()) + " " + to_string(w.getTxRecord()[0]) + " " + to_string(w.getTxRecord()[1]);
            // }
            // cout << masterString;
        }
    }
    return 0;
}