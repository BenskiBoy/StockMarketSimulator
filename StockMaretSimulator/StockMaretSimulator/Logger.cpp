#include "Logger.h"
#include <iostream>

Logger::Logger(string fileName, News* n)
{
	this->fileName = fileName;
	file.open(fileName);
	file << "Logger Begin" << "\t" << endl;
	file << "Number of Traders" << "\t" << NO_OF_TRADERS << endl;
	file << "Number of Companies" << "\t" << NO_OF_COMPANIES <<endl;
	file << "Number of Shares per Company" << "\t" << NO_OF_SHARES <<endl;
	file << "Tick Time (ms)" << "\t" << TICK_TIME_MS << endl << endl;

	this->n = n;
}

void Logger::Log(stringstream& ss)
{
	m.lock();

	//If a thread has detected a failure, exit
	if (ss.str().find("FAIL") != std::string::npos) {
		file << ss.str() << endl << flush;
		m.unlock();
		exit(1);
	}

	else if (ss.str().find("Industry") != std::string::npos) {
		lastLogTickIndustry = n->getTick();
	}

	else if (ss.str().find("Public") != std::string::npos) {
		lastLogTickPublic = n->getTick();
	}

	else if (ss.str().find("News") != std::string::npos) {
		lastLogTickWorld = n->getTick();
	}

	else {}

	file << ss.str() << endl << flush;
	m.unlock();
}