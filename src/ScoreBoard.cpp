#include "ScoreBoard.hpp"
#include<iostream>
#include <fstream>
using namespace std;
ScoreBoard::ScoreBoard(std::string file_path){
	this->path = file_path;
	file = fstream();
	file.open(file_path, ios::in|ios::out|ios::binary);
	if(file.is_open()){
		cout << file_path << " opened successfully" << endl;
		this->load_scores();
	}
	else{
		file.open(file_path, ios::in|ios::out|ios::binary|ios::trunc);
	}
}
ScoreBoard::~ScoreBoard(){
	file.close();
}
void ScoreBoard::load_scores()
{
	for(std::vector<Score*>::iterator i = scores.begin(); i != scores.end(); i++) delete (*i);
	this->scores.clear();

	file.seekg(0, ios::beg);

	while(file.good()){
		std::string name;
		getline(file, name, '\t');

		int score = (file.get() << 8) + file.get();
		file.ignore(); // endl

		Score new_score = Score(score, name);
		this->scores.push_back(&new_score);
	}
}

void ScoreBoard::add_score(Score score){
	this->add_score(score.score, score.name);
}

void ScoreBoard::add_score(int score, std::string name)
{
	for(std::vector<Score*>::iterator i = this->scores.begin(); i != this->scores.end(); i++){
		if((*i)->score < score){
			this->scores.insert(i, new Score(score, name));
			this->scores.pop_back();
			return;
		}
	}
}


void ScoreBoard::save_scores()
{
	for(std::vector<Score*>::iterator i = this->scores.begin(); i != this->scores.end(); i++){
		file << (*i)->name << '\t' << (*i)->score << std::endl;
	}
}

std::vector<Score> ScoreBoard::get_scores(){
	std::vector<Score> s_v;
	for(Score* sc : this->scores)
		s_v.push_back(*sc);
	return s_v;
}
