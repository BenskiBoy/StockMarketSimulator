#include "Trader.h"
#include <iostream>
Trader::Trader(int startUpMoney, Industry* industry)
{
	portfolio.money = startUpMoney;
	this->industry = industry;
}

void Trader::cycle()
{
	vector<Company*> prospects = industry->getHigherThanCompanies(1);
	vector<share> purchasedShares;

	for (unsigned int i = 0; i < prospects.size(); i++) {
		if ((prospects.at(i)->canBuyShares(10)) && (portfolio.money >= prospects.at(i)->getPrice()*10)) {
			purchasedShares = prospects.at(i)->buyShare(100);
			portfolio.money -= prospects.at(i)->getPrice() * 100;
		}
		else
			i = prospects.size() + 1;
	}

	for (unsigned int i = 0; i < purchasedShares.size(); i++)
	{
		portfolio.shares.push_back(purchasedShares.at(i));
	}

	//http://stackoverflow.com/questions/10464992/c-delete-vector-objects-free-memory
	vector<share>().swap(purchasedShares);
	vector<Company*>().swap(prospects);
}

string Trader::getStatus()
{
	stringstream ss;
	ss << "Portfolio size: " << portfolio.shares.size() << '\n' << "Money: " << portfolio.money << '\n';
	return ss.str();;
}