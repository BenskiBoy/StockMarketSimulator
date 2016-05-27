#pragma once
#ifndef __H_TICK__  
#define __H_TICK__   

#include "Enums.h"
#include "News.h"
#include "Logger.h"
#include <string>
#include <sstream>
#include <mutex>

using namespace std;

class Tick {
private:
	double SecondsPerTick;
	News* news;
public:
	Tick(double SecondsPerTick, News* news);

	Tick::Tick(const Tick& other) {
		SecondsPerTick = other.SecondsPerTick;
		news = other.news;
	}

	void operator()(Logger* l);
};
#endif
