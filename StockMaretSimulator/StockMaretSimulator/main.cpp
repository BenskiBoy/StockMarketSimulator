#include "Public.h"
#include "Company.h"
#include "Tick.h"
#include "World.h"
#include "Logger.h"
#include "UI.h"
#include "Failsafe.h"
#include <iostream>
#include <thread>

using namespace std;

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char* argv[])
{

	News n;
	Tick t(TICK_TIME_MS / 1000, &n);
	Logger l("log_file.txt", &n);
	World w(&n, &t);
	Industry i(&n);
	Public p(&i, &n);

	Failsafe f(&n);

	UI ui(&i, &n);
	
	thread tui(ui);
	thread ft(f, &l); //Failsafe Thread
	thread tt(t, &l); //Tick Thread
	thread tw(w, &l); //World Thread
	thread it(i, &l); //Industry Thread
	thread pt(p, &l); //Public Thread
	
	
	if (tt.joinable() && tui.joinable() && tw.joinable() && it.joinable() && pt.joinable() && ft.joinable()){
		//main is blocked until funcTest1 is not finished
		ft.join();
		tt.join();
		tw.join();
		tui.join();
		it.join();
		pt.join();
	}

	return 0;

}