#pragma once
#ifndef __H_ENUMS__
#define __H_ENUMS__

#include <string>
#include <vector>

#define NO_OF_TRADERS 100
#define NO_OF_COMPANIES 100
#define NO_OF_SHARES 100000
#define TICK_TIME_MS 1000

using namespace std;

enum TypesOfCompanies {
	A,
	B,
	C,
	D
};

struct share {
	string ID;
};

struct Portfolio {
	int money;
	vector<share> shares;
};


#endif