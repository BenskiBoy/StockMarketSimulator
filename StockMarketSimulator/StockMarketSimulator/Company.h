#pragma once
#ifndef __H_COMPANY__  
#define __H_COMPANY__   

#include "Enums.h"
#include <mutex>  
#include <sstream>

using namespace std;

class Company {
private:
	//vector<share> shares;
	int companyValue;
	int shares;
	string ID;
	TypesOfCompanies companyType;
	mutex m;
	void gatherNews();

public:
	Company(int noOfShares, int companyValue, string ID, TypesOfCompanies companyType);
	void cycle();

	vector<share> buyShare(int noOfShares);
	void sellShare(vector<share>);
	int getPrice();
	string getID();
	bool canBuyShares(int noOfShares);
	TypesOfCompanies getType();
	string getStatus();
};

#endif