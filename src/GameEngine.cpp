#include <iostream>
#include "GameEngine.hpp"
#include "IGameState.hpp"

void GameEngine::init(std::string title)
{
		this->running = true;
		this->window = new sf::RenderWindow(sf::VideoMode(800,600), title, sf::Style::Titlebar);
		this->window->clear();
		this->load_font("Inconsolata-Bold");
		this->sb = new ScoreBoard("scores.sc");
}

void GameEngine::clear()
{

}

void GameEngine::load_font(std::string font){
	if(this->fonts.find(font) == this->fonts.end()){
		sf::Font * new_font = new sf::Font();
		if(new_font->loadFromFile("res/"+font+".ttf"))
			this->fonts[font] = new_font;
	}
}

sf::Font* GameEngine::get_font(std::string font){
	if(this->fonts.find(font) != this->fonts.end())
		return this->fonts[font];
	return NULL;
}

void GameEngine::change_state(IGameState* state)
{
		if(!states.empty())this->states.back()->clear(this);
		this->states = std::vector<IGameState*>();
		this->states.push_back(state);
		this->window->clear();
		this->states.back()->init(this);
}
/*
void GameEngine::change_state(GameState state){
	IGameState* g_state
	switch(state){
	case GameState::Main:
		g_state = &(MainMenu.get_instance);
		break;
	case GameState::Play:
		g_state = &(GamePlay.get_instance);
		break;
	case GameState::Name:
		g_state = &(Name.get_instance);
		break;
	case GameState::Pause:
		g_state = &(Pause.get_instance);
		break;
	case GameState::Over:
		g_state = &(GameOver.get_instance);
		break;
	}
	this->change_state(g_state);
}
*/
void GameEngine::push_state(IGameState* state)
{
		this->states.push_back(state);
}

void GameEngine::pop_state()
{
		this->states.back()->clear(this);
		this->states.pop_back();
		this->states.back()->init(this);
}

void GameEngine::events()
{
		sf::Event event;

		while(this->window->pollEvent(event)){
			switch(event.type){
			case sf::Event::Closed:
				this->window->close();
				break;
			default:
				this->states.back()->events(this, event);
			}
		}		
}

void GameEngine::update()
{
		this->states.back()->update(this);
		
		if(!this->window->isOpen()){
			this->clear();
			this->quit();
		}
}

void GameEngine::render(float interp)
{
		this->window->clear();
		this->states.back()->render(this, interp);
		this->window->display();
}

void GameEngine::set_last_score(int score){
	this->last_score = score;
}
int GameEngine::get_last_score(){
	return this->last_score;
}
