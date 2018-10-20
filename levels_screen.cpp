//levels_screen.cp
//Group 20
//CSCE 121-515
//11-30-2017

#include "levels_screen.h"
#include "Puzzle.h"
#include <FL/Fl_JPEG_Image.H>  
#include <FL/Fl_PNG_Image.H>
#include "Graph.h"

using namespace Graph_lib;

//Font to be used in improving appearance of window
Graph_lib::Font times_font = Graph_lib::Font(Graph_lib::Font::Font_type::times);

levels_screen::levels_screen()
	:Window{ Point(100,100), 600, 400, "Levels" },
	win(nullptr), //address of next window
	initials_in{Point(80,125), 80,30,"Initials:"},
	levels(Point(0, 240), "levels.gif")
{
	//Levels image
	attach(levels);
	
	//Attach buttons
	attach(b_beginner);
	attach(b_intermediate);
	attach(b_advanced);
	attach(b_expert);

	//Attach Instructions Text objects
	attach(gameInstructions);
	attach(gameInstructions2);
	attach(gameInstructions3);
	gameInstructions.set_font(times_font);
	gameInstructions2.set_font(times_font);
	gameInstructions3.set_font(times_font);

	gameInstructions.set_font_size(18);
	gameInstructions2.set_font_size(18);
	gameInstructions3.set_font_size(18);

	//Attach In Box
	attach(initials_in);
	attach(error_msg);
	error_msg.set_font(times_font);
	error_msg.set_font_size(18);
	error_msg.set_color(Color::red);

	//Update and wait
	Fl::redraw();
	Fl::run();
}

//Callback functions - pass number of moves to next function
void levels_screen::cb_1(Address, Address pw2) { reference_to<levels_screen>(pw2).check_for_input(10);}
void levels_screen::cb_2(Address, Address pw2) { reference_to<levels_screen>(pw2).check_for_input(20);}
void levels_screen::cb_3(Address, Address pw2) { reference_to<levels_screen>(pw2).check_for_input(40);}
void levels_screen::cb_4(Address, Address pw2) { reference_to<levels_screen>(pw2).check_for_input(80);}

//Check to make sure there's something in the In_Box
void levels_screen::check_for_input(int start_moves) {
	//get truncated text from get_initials
	string user_initials = get_initials();
	if (user_initials.empty()) {
		//display error message
		error_msg.set_label("Error: Enter initials");
		error_msg.set_font(times_font);
		error_msg.set_color(Color::red);

		//Increse font size to further communicate to the user
		if(error_msg.font_size() < 30) 
			error_msg.set_font_size(error_msg.font_size() + 2);

		Fl::redraw(); //Update picture
	}
	else //User did put something in the In_Box
		handle_levels(start_moves, user_initials);

}

//Deals with all button presses and creates the puzzle window according to the difficulty
void levels_screen::handle_levels(int start_moves, string user_initials) {
	if (user_initials.length() == 1) user_initials += "  ";
	if (user_initials.length() == 2) user_initials += " ";
	hide();
	win = new Puzzle(start_moves, user_initials);
}

//Retrieves the initials from the In Box and takes the first three characters
string levels_screen::get_initials() {
	//Get initials from In Box
	string initials = initials_in.get_string();
	if (initials.length() > 3)
		initials = initials.substr(0, 3);

	return initials;
}