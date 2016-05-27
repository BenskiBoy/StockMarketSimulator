#pragma once
#ifndef __H_UI__  
#define __H_UI__   

#include "Company.h"
#include "Trader.h"
#include "Tick.h"
#include "News.h"
#include "Logger.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include <thread>
#include <sstream>

#include <cstdio>
#include <conio.h>
#include "libtcod.hpp"

using namespace std;

class UI {
private:
	Industry* industry;
	Trader* t;
	News* n;

	char* stringToCharStar(string s);

	int companyIndex = 0; 
	int numberOfShares = 1;

public:
	UI(Industry* i, News* n);

	void getInput();

	void updateScreenCycle();
	void printBuySelection();

	void printCompanies();
	void printUITraderStatus();
	void printIndustryStatus();

	void printTickNumber();

	void operator()();
};

#endif