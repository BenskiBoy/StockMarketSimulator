#include "Tick.h"
#include <iostream>

Tick::Tick(double SecondsPerTick, News* news)
{
	this->news = news;
	this->SecondsPerTick = SecondsPerTick;
	
}
void Tick::operator()(Logger* l)
{
	cout << "Tick Started" << endl;
	

	clock_t this_time = clock();
	clock_t last_time = this_time;
	double time_counter = 0;
	int temp = 0;

	this->news->setTick(temp);

	stringstream ss;

	while (1) {
		ss.str(std::string()); //Clears stringstream

		this_time = clock();

		time_counter += (double)(this_time - last_time);

		last_time = this_time;

		if (time_counter > (double)(SecondsPerTick * CLOCKS_PER_SEC))
		{
			news->setTick(temp + 1);
			temp++;
			time_counter -= (double)(SecondsPerTick * CLOCKS_PER_SEC);

			ss << "New Tick: " << temp << endl;
			l->Log(ss);
		}
	}
}