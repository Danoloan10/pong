#ifndef GAMENG_H
#define GAMENG_H

#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class IGameState;

class GameEngine{
public:
	void init(std::string title);
	void clear();

	void change_state(IGameState* state);
//	void change_state(State state);
	void push_state(IGameState* state);
	void pop_state();

	void save_score();

	void events();
	void update();
	void render(float interp);

	bool is_running(){ return running; }
	void quit(){ running = false; }
	
	sf::RenderWindow* get_window(){ return window; }

	GameEngine(std::string title){ this->init(title); }
	~GameEngine(){ this->clear(); }
	
	std::string lastName;
	int lastScore;
private:
	std::vector<IGameState*> states;
	sf::RenderWindow* window;
	bool running;
};
#endif
