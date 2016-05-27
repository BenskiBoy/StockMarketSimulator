#pragma once
#ifndef __H_WORLD__  
#define __H_WORLD__   

#include "Enums.h"
#include "News.h"
#include "Tick.h"
#include "Logger.h"
#include <string>
#include <mutex>

using namespace std;

//class News;
class World {
private:
	NewsPoint NewsValue[NO_OF_COMPANY_TYPES];
	News* news;
	Tick* tick;
	mutex m;

	int currentTick = 0;
	int lastTickOfNewsChange;

	int newsChangesPerTick;

	//Range from 0 to 100
	int maxValueOfNewsChange;
		

public:
	World(News* news, Tick* tick);

	//Reason for this not understood entirely. Won't compile without it
	World::World(const World& other) {
		newsChangesPerTick = NEWS_CHANGES_PER_TICK;
		maxValueOfNewsChange = MAX_VALUE_OF_NEWS_CHANGE;
		news = other.news;
		tick = other.tick;
	}
	
	//World(News* news, string fileName); //If wish to load news values from file at some point
	void operator()(Logger* l);
	void generateNews();
	int sudoNormalDistribution(int min, int max);
	int RandomGenerator(int max);
};

#endif