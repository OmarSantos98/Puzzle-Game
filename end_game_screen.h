//end_game_screen.h
//Group 20
//CSCE 121-515
//11-30-2017

#ifndef end_game_screen_h
#define end_game_screen_h

#include "std_lib_facilities_5.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "GUI.h"

#include "Puzzle.h"
#include "Score.h"

using namespace Graph_lib;

struct end_game_screen : Graph_lib::Window {
	end_game_screen(Difficulty game_dif, Score user_score);

	~end_game_screen();

private:
	//Data members
	Difficulty difficulty;

	//Text objects
	Text line0{ Point{ 60,80 }, "Thank You for playing, if" };
	Text line1{ Point{ 60,100 },"you would like to play again" };
	Text line2{ Point{ 80,140 },"-->  Please hit \"Continue\"" };
	Text line3{ Point{ 80,175},"-->  Otherwise hit \"End\"" };
	Text highScores{ Point(310, 75), "High Scores:" };
	Text* text_scores[5];
	Text userScore{ Point{440, 75}, "User Score:" };
	Text user{ Point{440, 100}, "" };

	Rectangle backdrop1{ Point(20, 20), 560, 230 };
	Rectangle backdrop2{ Point(30, 30), 540, 210 };
	Rectangle backdrop3{ Point(40, 40), 520, 190 };
	Rectangle backdrop4{ Point(50, 50), 500, 170 };

	//Option buttons
	Button yes_button;
	Button no_button;

	//Callback functions
	static void cb_yes(Address, Address);
	static void cb_no(Address, Address);

	//Callback action functions
	void newGame();
	void endGame();

	//Helper functions
	vector<Score> read_scores(Difficulty difficulty);
	void update_scores(vector<Score> scores);
};

#endif