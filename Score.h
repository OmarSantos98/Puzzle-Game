/Score.h
//Group 20
//CSCE 121-515
//11-30-2017

#ifndef Score_h
#define Score_h

//Keeps track of Score objects used in Puzzle and end_game_screen
class Score {
public:
	Score(string aa, int bb) { name = aa; score = bb; }
	Score() { name = ""; score = -1; }

	string get_name() const { return name; }
	int get_score() const { return score; }

private:
	string name;
	int score;

};

#endif
