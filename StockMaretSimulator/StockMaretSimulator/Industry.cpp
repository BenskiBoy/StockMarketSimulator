#include "Industry.h"
#include <iostream>
#include <string>

Industry::Industry(News* news)
{
	this->news = news;
	for (int i = 0; i < NO_OF_COMPANIES; i++) {
		Company *c = new Company(NO_OF_SHARES, 1000, to_string(i), generateRandomCompanyType());
		companies.push_back(c);
	}
	cout << "Companies made" << endl;
	
}

thread::id Industry::get_id()
{
	return std::this_thread::get_id();
}

void Industry::loop()
{
	for (int i = 0; i < NO_OF_COMPANIES; i++) {
		companies.at(i)->setPrice(companies.at(i)->getPrice() + (float(companies.at(i)->getPrice() * news->getNews(companies.at(i)->getType()))));
	}

	
	for (int i = 0; i < NO_OF_COMPANIES; i++) {
		companies.at(i)->cycle();
		//cout << "Company: " << i << endl << companies.at(i)->getStatus() << endl;
	}
	
}

void Industry::operator()(Logger* log)
{
	stringstream ss;
	clock_t start_time;
	clock_t end_time;
	double total_time;

	while (news->isPublicCreated()) {
		if (currentTick != news->getTick()) {
				
			currentTick = news->getTick();
			start_time = clock();
			ss.str(std::string()); //Clears stringstream
			cout << "Industry Cycle Begun" << endl;
			
			loop();
			total_time = ((clock() - start_time) / (double)CLOCKS_PER_SEC);
			cout << "Industry Cycle Complete" << endl;

			ss << "Finished Industry loop for Tick:" << "\t" << news->getTick() << endl;
			ss << "Loop Time:" << "\t" << total_time << "s" << endl;

			if (total_time * 1000 > TICK_TIME_MS) {
				ss << "*** FAIL ***" << endl << "Execution time took to long" << endl;
			}

			log->Log(ss);
		}
	}
}

//Get company at given Index
Company* Industry::getCompany(int index)
{
	return companies.at(index);
}

int Industry::getNumberOfCompanies()
{
	return companies.size();
}

//Get companies with a price lower than that 'valueLowerThan'
vector<Company*> Industry::getLowerThanCompanies(int valueLowerThan)
{
	vector<Company*> temp;

	for (int i = 0; i < NO_OF_COMPANIES; i++) {
		if (companies.at(i)->getPrice() < valueLowerThan) {
			temp.push_back(companies.at(i));
		}
	}

	return temp;
}

//Get companies with a price higher than 'valueHightThan'
vector<Company*> Industry::getHigherThanCompanies(int valueHigherThan)
{

	//m.lock();

	vector<Company*> temp;

	for (int i = 0; i < NO_OF_COMPANIES; i++) {
		if (this->companies.at(i)->getPrice() > valueHigherThan) {
			temp.push_back(this->companies.at(i));
		}
	}
	//m.unlock();

	return temp;
}

//Get companies of a type given by 'CompanyType'
vector<Company*> Industry::getTypeCompanies(char CompanyType)
{
	vector<Company*> temp;

	for (int i = 0; i < NO_OF_COMPANIES; i++) {
		if (companies.at(i)->getType() == CompanyType) {
			temp.push_back(companies.at(i));
		}
	}

	return temp;
}

TypesOfCompanies Industry::generateRandomCompanyType()
{
	int val = rand() % 3;
	switch (val) {
	case 0:
		return TypesOfCompanies(A);
	case 1:
		return TypesOfCompanies(B);
	case 2:
		return TypesOfCompanies(C);
	case 3:
		return TypesOfCompanies(D);
	}
}

string Industry::getStatus()
{
	stringstream ss;
	int total = 0;
	for (int i = 0; i < companies.size(); i++) {
		total+=companies.at(i)->getPrice();
	}
	int industrialAverage = total / companies.size();
	ss << "Industrial Average: " << industrialAverage << endl;
	return ss.str();;
}