//start_screen.cpp
//Group 20
//CSCE 121-515
//11-30-2017

#include "start_screen.h"
#include "levels_screen.h"
#include <FL/Fl_JPEG_Image.H>  
#include <unistd.h>

using namespace Graph_lib;

start_screen::start_screen()
	:Window{ Point(100,100), 600, 600, "Slider Puzzle" },
	start_button{ Point{ 480,510 }, 80, 25, "START",cb_start },
	background{ Point{ 480,510 }, 80, 25 }
{
	//Array of image names
	string my_images[11] = { "tileOne","tileTwo", "tileThree","tileFour","tileFive",
		"tileSix","tileSeven","tileEight","tileNine","tileTen", "tileEleven" };

	//Aesthetics
	background.set_fill_color(Color::white);
	names1.set_font_size(30);
	names2.set_font_size(30);
	newText.set_font_size(22);
	team.set_font_size(30);
	game_title.set_font_size(30);

	//Attach graphical objects
	attach(team);
	attach(names1);
	attach(names2);
	attach(background);	
	attach(newText);
	attach(game_title);
	attach(start_button);


	for (int i = 0; i < 11; i++) {
		myImages[i] = new Image{ Point{ 200,300 }, my_images[i].append(".jpg") };
		attach(*myImages[i]);
	}

	//Update the screen and wait
	Fl::redraw();
	Fl::run();
}


void start_screen::cb_start(Address, Address pw)
{
	reference_to<start_screen>(pw).start();
}

void start_screen::start() {
	hide();
	levels_screen win2;
}