#pragma once
#ifndef __H_PUBLIC__  
#define __H_PUBLIC__   

#include "Trader.h"
#include "Industry.h"
#include <vector>
#include <string>
#include <thread>
#include <time.h>

using namespace std;

class Trader;
class Public {
private: 
	//Only 1 task can access 1 trader at a time
	vector<Trader*> traders;
	
	//Pointer to industry so can know about companies of industry
	Industry* industry;

	//program cycle, will run once every tick count
	void loop();

public:
	Public(Industry* industry);
	thread::id get_id();
	void operator()();
};


#endif