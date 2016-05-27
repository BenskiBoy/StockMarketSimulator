#pragma once
#ifndef __H_ENUMS__
#define __H_ENUMS__

#include <string>
#include <vector>

#define NO_OF_TRADERS 10
#define NO_OF_COMPANIES 10
#define NO_OF_SHARES 100000
#define TICK_TIME_MS 5000
#define NEWS_CHANGES_PER_TICK 1
#define MAX_VALUE_OF_NEWS_CHANGE 70

using namespace std;

enum TypesOfCompanies {
	A,
	B,
	C,
	D,
	NO_OF_COMPANY_TYPES
};

struct NewsPoint {
	TypesOfCompanies EffectedIndustry;
	float value;
};

struct share {
	string ID;
};

struct Portfolio {
	float money;
	vector<share> shares;
};


#endif