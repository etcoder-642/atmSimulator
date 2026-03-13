#include <iostream>
#include <string>
#include <vector>
#include "../include/Wallet.h"

using namespace std;

void userDisplay(string user, int &value, float &balance)
{
    cout << "Choose what to do: " << endl;
    cout << "1. Deposit Money" << endl;
    cout << "2. Withdraw Money" << endl;
    cout << "3. Check Balance" << endl;
    cout << "4. See Transaction History" << endl;
    cout << "5. Transfer Money" << endl;
    cout << "6. Log Out" << endl;
    cout << "7. Log in as an ADMIN" << endl;
    cout << "8. Exit" << endl;
    cin >> value;
};

void displayBalance(string user, float balance)
{
    cout << "------------------------------------------------------------" << endl;
    cout << "========== YOUR WALLET =========" << endl;
    cout << "User: " << user << endl;
    cout << "Current Balance: " << balance << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
}

void initialPage(int &initialVal)
{
    cout << "========== ATM SIMULATOR =========" << endl;
    cout << "Choose what you would do" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Log In as an ADMIN" << endl;
    cout << "4. exit" << endl;
    cin >> initialVal;
}

void displayTransactionHistory(const vector<Wallet> &data, int num)
{
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "============= " << data[num].userName << "'s TRANSACTION HISTORY =============" << endl;
    if(data[num].txRecord.size() == 0){
        cout << " YOU HAVE NO TRANSACRION HISTORY" << endl;
        return;
    }
    for (int i = 0; i < data[num].txRecord.size(); i++)
    {
        if (data[num].txRecord[i] > 0)
        {
            cout << "Deposit: " << data[num].txRecord[i] << endl;
        }
        else if (data[num].txRecord[i] < 0)
        {
            cout << "Withdraw: " << data[num].txRecord[i] << endl;
        }
    }
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
}
