#pragma once
#ifndef __H_INDUSTRY__  
#define __H_INDUSTRY__   

#include "Company.h"
#include "Tick.h"
#include "News.h"
#include "Logger.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include <thread>

using namespace std;

class Tick;
class Company;
class Industry {
private:
	//Only 1 task can access 1 company at a time
	vector<Company*> companies;
    News* news = nullptr;
	TypesOfCompanies generateRandomCompanyType();

	void loop();

	int currentTick = 0;
public:
	Industry(News* news);
	thread::id get_id();
	void operator()(Logger* l);

	Company* getCompany(int index);
	vector<Company*> getLowerThanCompanies(int valueLowerThan);
	vector<Company*> getHigherThanCompanies(int valueHigherThan);
	vector<Company*> getTypeCompanies(char CompanyType);

	int getNumberOfCompanies();

	string getStatus();
};

#endif