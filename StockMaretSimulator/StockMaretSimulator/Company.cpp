#include "Company.h"
#include <iostream>

Company::Company(int noOfShares, int companyValue, string ID, TypesOfCompanies companyType)
{
	this->ID = ID;
	this->companyType = companyType;
	shares = noOfShares;
	this->companyValue = companyValue;

	cout << "Company: " << ID << " Made" << endl;
	/*
	shares.reserve(noOfShares);
	shares.resize(noOfShares);
	share s;
	s.ID = ID;
	fill(shares.begin(), shares.end(), s);
	*/
}

void Company::cycle()
{

}

vector<share> Company::buyShare(int noOfShares)
{
	m.lock();
	
	if (noOfShares < shares) {

		vector<share> temp;
		temp.reserve(noOfShares);
		temp.resize(noOfShares);
		share s;
		s.ID = this->ID;
		for (int i = 0; i < noOfShares; i++) {
			fill(temp.begin(), temp.end(), s);
		}
		m.unlock();

		return temp;
	}
	m.unlock();
}

void Company::sellShare(vector<share> sellShares)
{
	m.lock();

	shares += sellShares.size();

	//TODO Fill this in

	m.unlock();
}

string Company::getID()
{
	return ID;
}

int Company::getPrice()
{
	return companyValue;
}

void Company::setPrice(int value)
{
	companyValue = value;
	cout << ID << ": " << companyValue << endl;
}

bool Company::canBuyShares(int noOfShares)
{
	if (shares >= noOfShares)
	{
		return true;
	}
	return false;
}

TypesOfCompanies Company::getType()
{
	return companyType;
}

string Company::getStatus()
{
	stringstream ss;
	ss << "Shares Own: " << shares << '\n' << "Value:" <<"\t"<< this->companyValue << '\n';
	return ss.str();;
}