//levels_screen.h
//Group 20
//CSCE 121-515
//11-30-2017

#ifndef levels_screen_h
#define levels_screen_h

#include "std_lib_facilities_5.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "GUI.h"

//forward declaration of Puzzle
class Puzzle;

using namespace Graph_lib;

struct levels_screen : Graph_lib::Window {
	levels_screen();

private:
	//Button objects for each level
	Button b_beginner{ Point(0,240), 150, 130, "Beginner", cb_1 };
	Button b_intermediate{ Point(150,240), 160, 130, "Intermediate",cb_2 };
	Button b_advanced{ Point(310,240), 150, 130, "Advanced",cb_3 };
	Button b_expert{ Point(450,240), 150, 130, "Expert",cb_4 };

	//Text instructions
	Text gameInstructions{ Point{ 30,50 },"Click on a tile next to the empty space to move it there. You will be" };
	Text gameInstructions2{ Point{ 30, 70 },"permitted 10, 20, 40, or 80 moves to solve the puzzle. The purpose" };
	Text gameInstructions3{ Point{ 30, 90 },"of the game is to reorder all tiles into ascending order." };
	Text error_msg{ Point{ 10, 200 }, "" };

	//Puzzle GUI
	Puzzle* win;

	//In Box
	In_box initials_in;

	//Levels image
	Image levels;

	//Deals with all buttons
	void handle_levels(int difficulty, string user_initials);

	//Retrieves the initials from the In Box and
	//takes the first three characters
	string get_initials();

	//Checks to see if there is something in the in box
	void check_for_input(int difficulty);

	//Callback functions
	static void cb_1(Address, Address);
	static void cb_2(Address, Address);
	static void cb_3(Address, Address);
	static void cb_4(Address, Address);

};

#endif