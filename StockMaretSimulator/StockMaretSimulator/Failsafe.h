#pragma once
#ifndef __H_FAILSAFE__  
#define __H_FAILSAFE__   

#include "Enums.h"
#include "Logger.h"
#include "News.h"
#include <mutex>  
#include <sstream>

using namespace std;

class Failsafe {
private:
	News* n;
public:
	Failsafe(News* n);

	Failsafe::Failsafe(const Failsafe& other) {
		n = other.n;
	}

	void operator()(Logger* l);
};

#endif