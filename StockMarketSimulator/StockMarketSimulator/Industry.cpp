#include "Industry.h"
#include <iostream>
#include <string>

Industry::Industry()
{
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
		companies.at(i)->cycle();
		cout << "Company: " << i << endl << companies.at(i)->getStatus() << endl;
	}
}

void Industry::operator()()
{
	clock_t this_time = clock();
	clock_t last_time = this_time;
	double time_counter = 0;

	while (1) {
		this_time = clock();

		time_counter += (double)(this_time - last_time);

		last_time = this_time;

		if (time_counter > (double)(TICK_TIME_MS / 1000 * CLOCKS_PER_SEC))
		{
			time_counter -= (double)(TICK_TIME_MS / 1000 * CLOCKS_PER_SEC);
			loop();
		}
	}
}

//Get company at given Index
Company* Industry::getCompany(int index)
{
	return companies.at(index);
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