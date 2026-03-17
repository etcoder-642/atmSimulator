#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>

#include "../include/Wallet.h"
#include "../include/display.h"
#include "../include/utils.h"
#include "../include/Bank.h"

int handleAdminSession(Admin &adminAcc, Bank& bank);

#endif

