
#include "Public.h"
#include "Company.h"
#include <iostream>
#include <thread>

using namespace std;

int main()
{

	Industry i;
	Public p(&i);
	thread it(i);
	thread pt(p);
	
	if (it.joinable() && pt.joinable())
	{
		//main is blocked until funcTest1 is not finished
		it.join();
		pt.join();
	}

	return 0;
}