#include "Public.h"
#include <iostream>

Public::Public(Industry* industry)
{
	this->industry = industry;
	vector<Trader*> temp;
	for (int i = 0; i < NO_OF_TRADERS; i++) {
		Trader *t = new Trader(500000, this->industry);
		cout << "Trader: " << i << " Made" << endl;
		traders.push_back(t);
	}
}

thread::id Public::get_id()
{
	return std::this_thread::get_id();
}

void Public::loop()
{
	for (int i = 0; i < NO_OF_TRADERS; i++) {
		traders.at(i)->cycle();
		cout << "Trader ID: " << i << endl <<  traders.at(i)->getStatus() << endl << endl;
	}
}

void Public::operator()()
{
	clock_t this_time = clock();
	clock_t last_time = this_time;
	double time_counter = 0;

	while (1) {
		this_time = clock();

		time_counter += (double)(this_time - last_time);

		last_time = this_time;

		if (time_counter > (double)(TICK_TIME_MS/1000 * CLOCKS_PER_SEC))
		{
			time_counter -= (double)(TICK_TIME_MS/1000 * CLOCKS_PER_SEC);
			loop();
		}
	}
}