#pragma once
#ifndef __H_TRADER__  
#define __H_TRADER__   

#include "Enums.h"
#include "Industry.h"
#include <string>
#include <sstream>
using namespace std;


class Trader {
private:
	Portfolio portfolio;
	Industry* industry;
public:
	Trader(int startUpMoney, Industry* industry);
	void cycle();
	string getStatus();
	bool buy(int companyIndex, int numberOfShares);
	int getMoney() { return portfolio.money; }
	int getNetworth(); //value of shares owned

};

#endif