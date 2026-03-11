#include <iostream>
#include <string>
#include <vector>
#include "Wallet.h"

using namespace std;


void userDisplay(string user, int &value, int state, float &balance)
{
    if (state == 1)
    {
        cout << "Hello " << user << endl;
        cout << "Choose what to do: " << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. See Transaction History" << endl;
        cout << "5. Exit" << endl;
        cin >> value;
    }
    else if (state == 2)
    {
        cout << "========== YOUR WALLET =========" << endl;
        cout << "User: " << user << endl;
        cout << "Current Balance: " << balance << endl;
    }
};

void initialPage(int &initialVal)
{
    cout << "========== ATM SIMULATOR =========" << endl;
    cout << "Choose what you would do" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cin >> initialVal;
}


void displayTransactionHistory(const vector<Wallet>& data, int num){
    cout << "============= " << data[num].userName << "'s TRANSACTION HISTORY =============" << endl; 
    for(int i = 0; i < data.size(); i++){
        if(data[num].txRecord[i] > 0){
            cout << "Deposit: " << data[num].txRecord[i] << endl;
        }else if(data[num].txRecord[i] < 0){
            cout << "Withdraw: " << data[num].txRecord[i] << endl;            
        }
    }
}
