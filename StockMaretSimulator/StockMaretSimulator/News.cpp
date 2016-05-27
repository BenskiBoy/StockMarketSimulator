#include "News.h"

News::News()
{
	for (int i = 0; i < NO_OF_COMPANY_TYPES; i++) {
		NewsValue[i].value = 0;
	}
	tickVal = 0;
}

void News::setNews(TypesOfCompanies type, float value)
{
	m.lock();

	NewsValue[type-1].value = value;

	m.unlock();
}

//TODO Does this need a mutex and if so, how to unlock
float News::getNews(TypesOfCompanies type)
{
	//http://en.cppreference.com/w/cpp/thread/lock_guard
	//When control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and the mutex is released. 
	lock_guard<std::mutex> lg(m);

	return NewsValue[type].value;
}

void News::setTick(int val)
{
	//TODO Can we have two different mutexes so two threads can read/write different vals
	m.lock();
	tickVal = val;
	m.unlock();
}

int News::getTick()
{
	//Due to the continual checking of the tick value by the failsafe
	//This method cannot use the below auto releasing mutex
	//lock_guard<std::mutex> lg(m);
	return tickVal;
}

bool News::isPublicCreated()
{ 
	return publicCreated;
}

void News::setPublicCreated() 
{ 
	m.lock(); 
	publicCreated = true; 
	m.unlock(); 
}