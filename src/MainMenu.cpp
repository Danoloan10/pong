#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"

MainMenu::MainMenu()
{
}

void MainMenu::init(GameEngine* game)
{
	sf::Font * font = game->get_font("Inconsolata-Bold");
	sf::Window* window = game->get_window();
	sf::Vector2f center(window->getSize().x/2, window->getSize().y/2);
	this->play_but = Button(center-sf::Vector2f(100,25), sf::Vector2f(200,50), "PLAY");
	this->play_but.text->setFont(*font);
	center.y+= 100;
	this->quit_but = Button(center-sf::Vector2f(100,25), sf::Vector2f(200,50), "QUIT");
	this->quit_but.text->setFont(*font);
}

void MainMenu::clear(GameEngine* game)
{
	play_but = Button();
	quit_but = Button();
}

void MainMenu::pause()
{
}


void MainMenu::resume()
{
}

void MainMenu::events(GameEngine* game, sf::Event event){
	switch(event.type){
	case sf::Event::MouseMoved:
		this->play_but.hover_point(sf::Vector2f(event.mouseMove.x,event.mouseMove.y));
		this->quit_but.hover_point(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
		break;
	case sf::Event::MouseButtonPressed:
		if(this->quit_but.hover_point(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
			game->get_window()->close();
		}else
		if(this->play_but.hover_point(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
			game->change_state(&(GamePlay::get_instance()));
		}
		break;
	}
}

void MainMenu::update(GameEngine* game){
}

void MainMenu::render(GameEngine* game, float interp)
{
	sf::RenderWindow* window = game->get_window();
	window->draw(this->play_but.get_rect());
	window->draw(this->play_but.get_text());
	window->draw(this->quit_but.get_rect());
	window->draw(this->quit_but.get_text());
}

