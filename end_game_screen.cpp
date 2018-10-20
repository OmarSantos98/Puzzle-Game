//end_game_screen.cpp
//Group 20
//CSCE 121-515
//11-30-2017

#include "end_game_screen.h"
#include "levels_screen.h"
#include <sstream>
#include <iostream>

using namespace Graph_lib;

extern Graph_lib::Font times_font;

end_game_screen::end_game_screen(Difficulty game_dif, Score user_score)
	:Window{ Point(100,100), 600, 400, "Game Over" },
	difficulty(difficulty),
	yes_button{ Point{ 33, 300 }, 250, 80, "Continue",cb_yes },
	no_button{ Point{ 333 , 300 }, 250, 80, "End",cb_no }
{
	//Graphical aesthetics
	line0.set_font_size(18);
	line1.set_font_size(18);
	line2.set_font_size(18);
	line3.set_font_size(18);
	
	line0.set_color(Color::black);
	line1.set_color(Color::black);
	line2.set_color(Color::black);
	line3.set_color(Color::black);

	line0.set_font(times_font);
	line1.set_font(times_font);
	line2.set_font(times_font);
	line3.set_font(times_font);


	backdrop1.set_fill_color(Color::dark_green);
	backdrop2.set_fill_color(Color::yellow);
	backdrop3.set_fill_color(Color::black);
	backdrop4.set_fill_color(Color::white);

	//Attach graphical objects
	attach(yes_button);
	attach(no_button);
	attach(backdrop1);
	attach(backdrop2);
	attach(backdrop3);
	attach(backdrop4);
	attach(line0);
	attach(line1);
	attach(line2);
	attach(line3);

	//High scores from .txt file
	for (int i = 0; i < 5; ++i) {
		text_scores[i] = new Text(Point(310, 100 + 24 * i), "");
		text_scores[i]->set_font(times_font);
		text_scores[i]->set_font_size(18);
		text_scores[i]->set_color(Color::black);
		attach(*text_scores[i]);
	}

	attach(highScores);
	highScores.set_color(Color::black);
	highScores.set_font_size(18);
	highScores.set_font(times_font);
	difficulty = game_dif;
	vector<Score> game_scores = read_scores(difficulty);
	update_scores(game_scores);

	//User score passed from constructor argument
	attach(userScore);
	userScore.set_color(Color::black);
	userScore.set_font_size(18);
	userScore.set_font(times_font);

	ostringstream os;
	os.str("");
	os << user_score;
	user.set_label(os.str());
	user.set_font_size(18);
	user.set_font(times_font);
	user.set_color(Color::black);
	attach(user);
	
	//Update and infinite loop
	Fl::redraw();
	Fl::run();
}

//Destructor for end_game_screen
end_game_screen::~end_game_screen() {
	for (int i = 0; i < 5; ++i)
		delete text_scores[i];
}

//Get the string file name for the specified difficulty
string file_name(Difficulty difficulty) {

	switch (difficulty) {
	case BEGINNER:     return "beginner_scores.txt";
	case INTERMEDIATE: return "intermediate_scores.txt";
	case ADVANCED:     return "advanced_scores.txt";
	case EXPERT:       return "expert_scores.txt";
	}
}

//Reads off the .txt file and returns the scores for the difficulty specified
vector<Score> end_game_screen::read_scores(Difficulty difficulty) {
	//use the txt_name specified for the ifstream
	string txt_name = file_name(difficulty);
	//open an ifstream
	ifstream is{ txt_name };
	if (!is) cout << "Bad ifstream\n"; //DELETE LATER
									   //declare ifstream variables
	Score entry;
	string name;
	int number;
	//output variable
	vector<Score>top_scores;
	while (!is.eof()) { //until is reaches EOF
		is >> name >> number;
		entry = { name, number };
		top_scores.push_back(entry);
	}
	return top_scores;
}

void end_game_screen::update_scores(vector<Score> top_scores) {
	ostringstream os;
	for (int i = 0; i < top_scores.size(); ++i) {
		os.str(""); //clear os
					//Put the rankings and scores into os
		os << i + 1 << ") " << top_scores.at(i);
		//update each Text object label
		text_scores[i]->set_label(os.str());
		//if i doesn't go high enough to reach the upper labels, it will
		//already be cleared from its initialization
	}
}

//Callback for no button
void end_game_screen::cb_yes(Address, Address pw) { reference_to<end_game_screen>(pw).newGame(); }

//Callback for yes button
void end_game_screen::cb_no(Address, Address pw) { reference_to<end_game_screen>(pw).endGame(); }

//Create a new game by instantiating a new levels screen
void end_game_screen::newGame() {
	hide();
	levels_screen win2;
}

//Hide the window to quit
void end_game_screen::endGame() {
	hide();
}
