#pragma once
#ifndef __H_INDUSTRY__  
#define __H_INDUSTRY__   

#include "Company.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include <thread>

using namespace std;

class Company;
class Industry {
private:
	//Only 1 task can access 1 company at a time
	vector<Company*> companies;

	TypesOfCompanies generateRandomCompanyType();

	//mutex m;

	void loop();
public:
	Industry();
	thread::id get_id();
	void operator()();

	Company* getCompany(int index);
	vector<Company*> getLowerThanCompanies(int valueLowerThan);
	vector<Company*> getHigherThanCompanies(int valueHigherThan);
	vector<Company*> getTypeCompanies(char CompanyType);
};

#endif