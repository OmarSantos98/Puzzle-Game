//main.cpp
//Group 20
//CSCE 121-515
//11-30-2017

#include "start_screen.h"
#include "std_lib_facilities_5.h"

int main()
{
	try {
		start_screen win;
	
		return Graph_lib::gui_main();
	}
	catch (exception& e) { //catches range errors and run_time_errors
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) { //catch any exception
		cerr << "Exception: something went wrong \n";
		return 2;
	}
}