#include "Failsafe.h"
#include <iostream>

Failsafe::Failsafe(News* n)
{
	this->n = n;
}

void Failsafe::operator()(Logger* l)
{
	stringstream ss;

	ss << "failsafe thread started" << endl << endl;
	l->Log(ss);
	
	while (1) {
		ss.str(std::string()); //Clears stringstream
		if (n->getTick() > 1) {
			if ( (l->lastLogTickIndustry < n->getTick() - 1) || (l->lastLogTickPublic < n->getTick() - 1) || (l->lastLogTickWorld < n->getTick() - 1) )
			{
				ss << "FAILURE FOUND IN FAILSAFE!" << endl << "ABORT!" << endl;
				l->Log(ss);
				exit(1);
			}
		}
	}
}