#pragma once
#ifndef __H_LOGGER__  
#define __H_LOGGER__   

#include "Enums.h"
#include "News.h"
#include <fstream>
#include <string>
#include <mutex>
#include <sstream>

using namespace std;

class Logger {
private:

	mutex m;
	ofstream file;
	int currentTick = 0;
	string fileName;

	News* n;

public:
	Logger(string fileName, News* n);

	int lastLogTickIndustry; //The last tick cycle in which a log was performed by Inudstry.
	int lastLogTickPublic; //The last tick cycle in which a log was performed by Public.
	int lastLogTickWorld; //The last tick cycle in which a log was performed by World.

	
	void Log(stringstream& ss);
};

#endif