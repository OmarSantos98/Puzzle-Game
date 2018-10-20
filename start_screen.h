//start_screen.h
//Group 20
//CSCE 121-515
//11-30-2017

#ifndef start_screen_h
#define start_screen_h

#include "std_lib_facilities_5.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "GUI.h"

#include <unistd.h>
#include <stdio.h>

using namespace Graph_lib;

struct start_screen : Graph_lib::Window {
	start_screen();

private:
	Text team{ Point{ 250,150 },"Team 20" };
	Text names1{ Point{ 60,220 },"Omar Santos     Zachary Williams" };
	Text names2{ Point{ 60, 260 },"Hector Tale       Jonathan Williams " };
	Text game_title{ Point{ 150,100 }, "The 15-Puzzle Game" };
	Text newText{ Point{ 495,530 }, "Start" };
    
	//Animation for game being played
	Image* myImages[11];
	Button start_button;
	Rectangle background;

	void wait(int sec);

	void start();  

	static void cb_start(Address, Address);
};



#endif
