#ifndef SCORE_H
#define SCORE_H

#include<fstream>
#include<vector>

typedef struct Score{
	std::string name;
	int score;
	Score(int score, std::string name){
		this->score = score;
		this->name = name;
	}
} Score;

class ScoreBoard{
public:
	ScoreBoard(std::string file_path);
	~ScoreBoard();

	void load_scores();
	void save_scores();
	void add_score(Score score);
	void add_score(int score, std::string name);
	
	std::vector<Score> get_scores();
private:
	std::vector<Score*> scores;
	std::string path;
	std::fstream file;
};
#endif
