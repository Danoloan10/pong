#include <iostream>
#include "GameEngine.hpp"
#include "../GameState/IGameState.hpp"

void GameEngine::init(std::string title)
{
		this->window = new sf::RenderWindow(sf::VideoMode(800,600), title, sf::Style::Titlebar);
		this->window->clear();
}

void GameEngine::clear()
{
}

void GameEngine::change_state(IGameState* state)
{
		this->states = std::vector<IGameState*>();
		this->states.push_back(state);
		this->window->clear();
		this->states.back()->init(this);
}

void GameEngine::push_state(IGameState* state)
{
		this->states.push_back(state);
}

void GameEngine::pop_state()
{
		this->states.back()->clear(this);
		this->states.pop_back();
}

void GameEngine::events()
{
		this->states.back()->events(this);
}

void GameEngine::update()
{
		this->states.back()->update(this);
}

void GameEngine::render(float interp)
{
		this->states.back()->render(this, interp);
		this->window->display();
}
