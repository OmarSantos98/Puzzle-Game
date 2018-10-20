//Puzzle.h
//Group 20
//CSCE 121-515
//11-30-2017

#ifndef Puzzle_h
#define Puzzle_h

#include "std_lib_facilities_5.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"

#include "My_Button.h"
#include "Score.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <cassert>
#include <sstream>
#include <iostream>

using namespace Graph_lib;

//Global times font
extern Graph_lib::Font times_font;

//tell compiler to initialize EMPTY somewhere else
extern const int EMPTY;

//forward declaration of My_Button
class My_Button;

//forward declaration of end_game_screen
struct end_game_screen;

//Declaration of Score's overloaded operators
std::ostream& operator<<(std::ostream& os, const Score& a);
bool operator<(const Score& a, const Score& b);

//Chosen by user, calculated by start_moves / 10 in constructor
enum Difficulty {
	BEGINNER = 1, INTERMEDIATE = 2, ADVANCED = 4, EXPERT = 8
};

struct Puzzle : Graph_lib::Window {
	Puzzle(int start_moves, string user_initials);

	~Puzzle();

private:

	//16 buttons as an array of Button* 's
	My_Button* buttons[4][4];

	//Address of final game screen after Puzzle finishes
	end_game_screen* win;

	//High scores text objects
	Text top0{ Point{10, 20}, "HIGH SCORES" };
	Text top00{ Point{10, 21}, "_________________" };

	//Initialize with empty strings to be changed in update_scores
	Text* text_scores[5];
	Text topUser{ Point{10, 153},""};	

	//Instructions
	Rectangle instructions_background{ Point{5, 340}, 190, 55 };
	Text instructions1{ Point{10, 360}, "Click on a yellow tile" };
	Text instructions2{ Point{10, 380}, "to get started." };
	
	//Keeps track of game moves
	int start_moves;

	//Remaining moves
	Text rem_moves_txt{ Point{10,175}, "Remaining moves:" };
	Text num_moves_txt{ Point{10,220},"" };
	int moves_left;

	//Incorrect tiles
	Text incorrect_txt{ Point{10, 245}, "Incorrect tiles:" };
	Text num_incorrect_txt{ Point{10, 290}, "" };

	//hint button
	Button hint_button;
	string user_init;
	
	//difficulty
	Difficulty difficulty;

	//Member functions
	//gets user initials
	string get_user_initials();
	
	//Finds location of button pressed
	void find(Fl_Button* button, int &i, int &j);

	//Finds location of empty button
	void find_blank(int &blank_i, int &blank_j);

	//Action for each button when pressed
	void swap(int i, int j);

	//Button array callback
	static void cb_button(Address, Address);

	//Handles all button callbacks
	void handle_button(Fl_Button*);

	//Updates the # of remaining Moves
	void update_moves();

	//Finds how many tiles in wrong positions
	int incorrect_tiles(bool sim_check);

	//Returns the new count of incorrect tiles and colors the tiles appropriately
	void color_tiles(int i, int j, int tile, bool good, int blank_i, int blank_j);

	//Updates the # of incorrect tiles
	void update_incorrect();

	//Get the string file name for the correct difficulty
	string file_name(Difficulty difficulty);
	
	//Reads off the .txt file and returns the scores for the difficulty specified
	vector<Score> read_scores(Difficulty difficulty);
	
	//Inputs the final score into its place in the old scores file
	//and call write_scores to write the top 5 scores to the file
	void input_score(Score final_score, Difficulty difficulty);

	//Write the 5 highest scores to the .txt file
	void write_scores(vector<Score>game_scores, Difficulty difficulty);
	
	//Updates the scores text objects
	void update_scores(vector<Score>);
	
	//Gets the number sequence based on the difficulty
	vector<int> get_puzzle_1(Difficulty difficulty);
	vector<int> get_puzzle_2(Difficulty difficulty);
	vector<int> get_puzzle_3(Difficulty difficulty);
	vector<int> get_puzzle_4(Difficulty difficulty);

	//Hint button callback
	static void cb_hint(Address, Address);
	
	//Hint button logic
	void get_hint();
	void get_hint_2(int blank_i, int blank_j, vector<int> sim_sums);
	void get_hint_3(int blank_i, int blank_j, vector<int> sim_sums);
	void get_hint_4(int blank_i, int blank_j, vector<int> sim_sums);
	
	//hint simulation code
	int hint_sim(int i, int j);
	
	//hint get position of lowest sum
	int get_lowest(vector<int> sim_sums);
	
	//updates the hint text on the window
	void update_hint(int pos);
	
	//Check to make a legal move
	string tile_check();

	
	//calculates final score once game is finished
	void end_game();
};

#endif