#include "UI.h"
#include <iostream>
#include <windows.h>

UI::UI(Industry* i, News* n) {
	this->industry = i;
	this->n = n;
	t = new Trader(500000, i);
	TCODConsole::initRoot(80, 50, "RTP Stock Simulator", false);
	TCODConsole::flush();
}

void UI::getInput()
{
	

	if ((GetAsyncKeyState('B') & 0x8000)) { //'B'
		if (t->getMoney() >= industry->getCompany(companyIndex)->getPrice()*numberOfShares) {
			t->buy(companyIndex, numberOfShares);
			updateScreenCycle();
		}
	}
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)) { 
		if (companyIndex != 0) {
			companyIndex--;
		}
		else {
			companyIndex = NO_OF_COMPANIES;
		}
		updateScreenCycle();
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		if (companyIndex == NO_OF_COMPANIES) {
			companyIndex = 0;
		}
		else {
			companyIndex++;
		}
		updateScreenCycle();
	}
	if ((GetAsyncKeyState(VK_UP) & 0x8000)) {
		numberOfShares++;
		updateScreenCycle();
	}
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000)) {
		if(numberOfShares != 0){
			numberOfShares--;
		}
		updateScreenCycle();
	}
}

void UI::operator()()
{
	string temp;
	int prevTick = -1;

	while (1) {
		getInput();
		if (n->getTick() != prevTick) {
			prevTick = n->getTick();
			updateScreenCycle();
		}
	}
}

void UI::updateScreenCycle() 
{
	TCODConsole::root->clear();

	printIndustryStatus();
	printUITraderStatus();
	printCompanies();
	printTickNumber(); 
	printBuySelection();

	TCODConsole::flush();
}

void UI::printTickNumber()
{
	string temp = "Tick Number: " + to_string(n->getTick());
	TCODConsole::root->printEx(0, 48, TCOD_BKGND_NONE, TCOD_LEFT, stringToCharStar(temp));
}

void UI::printBuySelection()
{
	string temp = "Company Number: " + to_string(companyIndex);
	TCODConsole::root->printEx(50, 48, TCOD_BKGND_NONE, TCOD_LEFT, stringToCharStar(temp));
	temp = "Number of Shares: " + to_string(numberOfShares);
	TCODConsole::root->printEx(50, 49, TCOD_BKGND_NONE, TCOD_LEFT, stringToCharStar(temp));
}

void UI::printIndustryStatus()
{
	string temp = industry->getStatus();
	int cal = temp.length();
	TCODConsole::root->printEx(80 - cal, 0, TCOD_BKGND_NONE, TCOD_RIGHT, stringToCharStar(temp));
}

void UI::printCompanies()
{
	stringstream ss;
	for (int i = 0; i < industry->getNumberOfCompanies(); i++) {
		ss.str(std::string());
		ss << "[ " << i << "] Value: " << industry->getCompany(i)->getPrice();
		TCODConsole::root->printEx(60, i+1, TCOD_BKGND_NONE, TCOD_RIGHT, stringToCharStar(ss.str()));
	}
}

void UI::printUITraderStatus()
{
	stringstream ss;
	string temp = static_cast<ostringstream*>(&(ostringstream() << (t->getNetworth()) + t->getMoney()))->str(); //int to string
	ss << t->getStatus() << endl << "Networth: " << temp ;
	TCODConsole::root->printEx(0, 1, TCOD_BKGND_NONE, TCOD_LEFT, stringToCharStar(ss.str()));
}

char* UI::stringToCharStar(string s)
{
	char *a = new char[s.size() + 1];
	a[s.size()] = 0;
	memcpy(a, s.c_str(), s.size());
	return a;
}