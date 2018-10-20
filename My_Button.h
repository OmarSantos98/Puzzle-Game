//My_Button.h
//Group 20
//CSCE 121-515
//11-30-2017

/*
Creates an inherited button class to give Button access to pw,
which is the address of an Fl_Button declared as virtual void in FL/Fl_Button.h
*/


#ifndef My_Button_h
#define My_Button_h

#include "std_lib_facilities_5.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"

#include "Puzzle.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <cassert>
#include <sstream>

using namespace Graph_lib;

//tell compiler to initialize EMPTY somewhere else
extern const int EMPTY;

struct My_Button : public Button {
	My_Button(Point xy, int w, int h, const string& label, Callback cb)
		: Button(xy, w, h, label, cb) {}

	//Determines whether an inputed Fl_Button* is the same as pw,
	//which is the Fl_Button* that was pushed
	bool is(Fl_Button* fl) { return fl == pw; }

	//Retrieves the name of the tile as an integer
	int get_tile() {
		istringstream is;
		if (label.empty()) //if blank tile, return EMPTY (-1)
			return EMPTY;
		is.str(label); //else, return the string of the label
		int num;
		is >> num;
		assert(is);
		return num;
	}

	//sets a tile to an int num
	void set_tile(int num) {
		ostringstream os;
		if (num != EMPTY) //if the set tile isn't empty, set it to num
			os << num;
		//if num == EMPTY, keep it as an empty ostringstream

		label = os.str();

		//Update
		Fl::redraw();
	}

	//Change background color of My_Button
	void set_colors(Fl_Color back, Fl_Color font) {
		pw->Fl_Widget::color(back, Color::gray);
		pw->Fl_Widget::labelcolor(font);
	}
};

#endif