#include "World.h"
#include <iostream>


World::World(News* news, Tick* tick)
{
	this->news = news;
	this->tick = tick;

	if(NEWS_CHANGES_PER_TICK > NO_OF_COMPANY_TYPES)
		this->newsChangesPerTick = NO_OF_COMPANY_TYPES;
	else
		this->newsChangesPerTick = NEWS_CHANGES_PER_TICK;
	
	if (MAX_VALUE_OF_NEWS_CHANGE > 100)
		this->maxValueOfNewsChange = 100;
	else
		this->maxValueOfNewsChange = maxValueOfNewsChange;
}

void World::operator()(Logger* l)
{
	stringstream ss;
	clock_t start_time;
	clock_t end_time;
	double total_time;

	while (1) {
		ss.str(std::string()); //Clears stringstream
		if (currentTick != news->getTick()) {
			start_time = clock();
			currentTick = news->getTick();
			
			generateNews();

			total_time = ((clock() - start_time) / (double)CLOCKS_PER_SEC);
			cout << "News generation Complete" << endl;

			ss << "Finished News generation for Tick:" << "\t" << news->getTick() << endl;
			ss << "Generation Time:" << "\t" << total_time << "s" << endl;

			if (total_time * 1000 > TICK_TIME_MS) {
				ss << "*** FAIL ***" << endl << "Execution time took to long" << endl;
			}

			l->Log(ss);
		}
	}
}

void World::generateNews() 
{
	int typesToChange[NO_OF_COMPANY_TYPES];
	int company;
	bool ok = false;

	for (int i = 0; i < newsChangesPerTick; i++) {
		company = RandomGenerator(NO_OF_COMPANY_TYPES);
		while (!ok) {
			ok = true;
			for (int j = 0; j < newsChangesPerTick; j++) {
				if (typesToChange[j] == company) {
					ok = false;
				}
			}
		}
		typesToChange[i] = company;
	}

	for (int i = 0; i < newsChangesPerTick; i++) {
		news->setNews((TypesOfCompanies)typesToChange[i], float(((100-sudoNormalDistribution(0, 2*maxValueOfNewsChange)))) / 100);
	}
}


int World::sudoNormalDistribution(int min, int max)
{
	float angle = RandomGenerator(1570);
	angle /= 1000;
	int value = sin(angle) * max;
	if (value < min)
	{
		int temp = value + min;
		if (temp > max)
		{
			return value + (min / 2);
		}
	}
	else
	{
		return value;
	}
}
int World::RandomGenerator(int max)
{
	return rand() % max + 1;
}