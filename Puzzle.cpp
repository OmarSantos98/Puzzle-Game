//Puzzle.cpp
//Group 20
//CSCE 121-515
//11-30-2017

#include "Game_Scores.h"
#include "My_Button.h"
#include "Scores.h"
#include "end_game_screen.h"

#include <string>
#include <cassert>
#include <sstream>


using namespace Graph_lib;

extern Graph_lib::Font times_font;

//Overload << to be used in printing a Score object
std::ostream& operator<<(std::ostream& os, const Score& a)
{
	return os << a.get_name() << "   " << a.get_score();
}

bool operator<(const Score& a, const Score& b) { return a.get_score() < b.get_score(); }

//Indicates the number of the blank tile
const int EMPTY = -1;

//General Puzzle constructor called by scores_window
Puzzle::Puzzle(int start_moves, string user_initials)
	:Window{ Point(100,100), 600, 400, "Slider Puzzle" },
	start_moves(start_moves),
	hint_button(Point(10, 300), 100, 30, "Hint", cb_hint),
	moves_left(start_moves),
	win(nullptr)
	
{
	//difficulty can be 1, 2, 4, or 8
	Difficulty difficulty = (Difficulty)(start_moves / 10);
	
	//Initialize Buttons
	vector<int>numbers;

	

	//Create different numbers vectors based on inputted difficulty
	switch (which) {
	case 1:
		numbers = get_puzzle_1(difficulty);
		break;
	case 2:
		numbers = get_puzzle_2(difficulty);
		break;
	case 3:
		numbers = get_puzzle_3(difficulty);
		break;
	case 4:
		numbers = get_puzzle_4(difficulty);
		break;
            
    case 5:
            numbers = get_puzzle_1(difficulty);
            break;
    case 6:
            numbers = get_puzzle_2(difficulty);
            break;
    case 7:
            numbers = get_puzzle_3(difficulty);
            break;
    case 8:
            numbers = get_puzzle_4(difficulty);
            break;
            
    case 9:
            numbers = get_puzzle_4(difficulty);
            break;
	}

	int count = 0;
	ostringstream os;

	


	

	}

	//Extract old scores from disk
	vector<Score> old_scores = read_scores(difficulty);
	bool is_empty = (old_scores.at(0).get_name() == "");
	if (!is_empty) 
		update_scores(old_scores); //Update text objects
	os.str("");
	os << "?) " << user_initials << "   ???";
	topUser.set_label(os.str());
	topUser.set_font(times_font);
	topUser.set_font_size(18);



//gets user initials
string Puzzle::get_user_initials() {
	return user_init;
}













//Get the string file name for the specified difficulty
string Puzzle::file_name(Difficulty difficulty) {

	switch (difficulty) {
	case BEGINNER:     return "beginner_scores.txt";
	case INTERMEDIATE: return "intermediate_scores.txt";
	case ADVANCED:     return "advanced_scores.txt";
	case EXPERT:       return "expert_scores.txt";
	}
}

//Reads off the .txt file and returns the scores for the difficulty specified
vector<Score> Puzzle::read_scores(Difficulty difficulty) {
	//use the txt_name specified for the ifstream
	string txt_name = file_name(difficulty);
	//open an ifstream
	ifstream is{ txtName };
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

//Inputs the final score into its appropriate place from the .txt file
//and call write_scores to write the top 5 scores to the file
void Puzzle::input_score(Score final_score, Difficulty difficulty) {
	//get the current scores from the .txt file
	vector<Score>game_scores = read_scores(difficulty);

	//If first name is empty, scores file is empty
	bool is_empty = (game_scores.at(0).get_name() == "");
	if (is_empty) //Put final score as the first element
		game_scores.at(0) = final_score;
	else //Push final_score onto the back
		game_scores.push_back(final_score);

	//Reverse sort game_scores from highest to lowest
	sort(game_scores.rbegin(), game_scores.rend());

	//if necessary, delete the 6th element using the erase iterator
	if (game_scores.size() == 6)
		game_scores.erase(game_scores.begin() + 5, game_scores.end());
	write_scores(game_scores, difficulty);
}

//Write the 5 highest scores to the .txt file
void Puzzle::write_scores(vector<Score>game_scores, Difficulty difficulty) {
	//get the string file name from file_name
	string txt_name = file_name(difficulty);
	//open an ofstream with the appropriate difficulty file
	ofstream os{ txt_name };
	if (!os) cout << "Bad ofstream" << endl;
	//Write scores to file
	for (int i = 0; i < game_scores.size(); ++i) {
		os << game_scores[i];
		//only have a new line on all but last score to keep ifstream valid
		if (i != game_scores.size() - 1)
			os << endl;
	}
	os.close();
}

//Updates the scores text objects
void Puzzle::update_scores(vector<Score> top_scores) {
	ostringstream os;
	assert(top_scores.size() <= 5);
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



//ends the current game, moves to end game screen
void Puzzle::end_game() {
	int user_score = (16 - incorrect_tiles(false)) * start_moves;	//calculate user score
	topUser.set_label("");
	string username = get_user_initials();
	Difficulty difficulty = (Difficulty)(start_moves / 10);
	Score userScore{username,user_score};
	
	input_score(userScore, difficulty);
	
	hide();
	win  = new end_game_screen(difficulty, userScore);
}
