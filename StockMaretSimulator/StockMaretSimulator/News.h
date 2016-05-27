#pragma once
#ifndef __H_NEWS__  
#define __H_NEWS__   

#include "Enums.h"
#include <string>
#include <sstream>
#include <mutex>

using namespace std;

class News {
private:
	NewsPoint NewsValue[NO_OF_COMPANY_TYPES];
	mutex m;
	int tickVal = 0;

	//The public takes a while to create. 
	//This value is used to force Industry to wait to begin thread cycle
	bool publicCreated = false;

public:
	News();
	void setNews(TypesOfCompanies type, float value);
	float getNews(TypesOfCompanies type);
	void setTick(int val);
	int getTick();

	bool isPublicCreated();
	void setPublicCreated();
};

#endif