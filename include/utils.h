#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Wallet.h"
#include "Bank.h"
using namespace std;

bool checkFile(string fileName);
vector<string> splitString(string str);
bool authenticateAdmin(Admin adminAcc, string tempName, string tempPassword);
void loadAdminData(Admin& adminAcc);
void uploadAdminData(const Admin& adminAcc);

#endif