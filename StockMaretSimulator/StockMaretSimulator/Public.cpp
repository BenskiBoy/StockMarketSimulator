#include "Public.h"
#include <iostream>

Public::Public(Industry* industry, News* news )
{
	this->industry = industry;
	vector<Trader*> temp;
	for (int i = 0; i < NO_OF_TRADERS; i++) {
		Trader *t = new Trader(500000, this->industry);
		cout << "Trader: " << i << " Made" << endl;
		traders.push_back(t);
	}
	this->news = news;
	news->setPublicCreated();
}

thread::id Public::get_id()
{
	return std::this_thread::get_id();
}

void Public::loop()
{
	for (int i = 0; i < NO_OF_TRADERS; i++) {
		traders.at(i)->cycle();
		//cout << "Trader ID: " << i << endl <<  traders.at(i)->getStatus() << endl << endl;
	}
}

void Public::operator()(Logger* log)
{

	stringstream ss;
	clock_t start_time;
	clock_t end_time;
	double total_time;

	while (1) {
		if (currentTick != news->getTick()) {

			currentTick = news->getTick();
			start_time = clock();
			ss.str(std::string()); //Clears stringstream

			loop();
			total_time = ((clock() - start_time) / (double)CLOCKS_PER_SEC);
			cout << "Public cycle complete" << endl;

			ss << "Finished Public loop for Tick: " << "\t" << news->getTick() << endl;
			ss << "Loop Time: " << "\t" << total_time << "s" << endl;

			if (total_time * 1000 > TICK_TIME_MS) {
				ss << "*** FAIL ***" << endl << "Execution time took to long" << endl;
			}

			log->Log(ss);
		}
	}
}