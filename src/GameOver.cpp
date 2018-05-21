#include "IGameState.hpp"

#include "GameEngine.hpp"

GameOver::GameOver()
{
}


void GameOver::init(GameEngine* game)
{
	sf::Font * inc_bold = new sf::Font();
	inc_bold->loadFromFile("res/Inconsolata-Bold.ttf");
	sf::Window * window = game->get_window();
	this->cont = Button(sf::Vector2f(window->getSize().x/2.0f, window->getSize().y*2.0f/3.0f)-sf::Vector2f(100,25), 
		      sf::Vector2f(200,50),
		      "CONTINUE");
	this->cont.text->setFont(*inc_bold);
}


void GameOver::clear(GameEngine* game)
{
	return /* something */;
}


void GameOver::pause()
{
	return /* something */;
}

void GameOver::resume()
{
	return /* something */;
}

void GameOver::events(GameEngine* game, sf::Event event)
{
	switch(event.type){
	case sf::Event::MouseMoved:
		if(this->cont.over(sf::Vector2f(event.mouseMove.x,event.mouseMove.y))){
			this->cont.is_hover = true;
		}else{
			this->cont.is_hover = false;
		}
		break;
	case sf::Event::MouseButtonPressed:
		if(this->cont.over(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
			game->change_state(&(MainMenu::get_instance()));
		}
	}
}

void GameOver::update(GameEngine* game)
{
	return /* something */;
}

void GameOver::render(GameEngine* game, float interp)
{
	sf::RenderWindow* window = game->get_window();
	window->draw(this->cont.get_rect());
	window->draw(this->cont.get_text());
}

