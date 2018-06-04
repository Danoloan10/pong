#include "IGameState.hpp"
#include "GameEngine.hpp"
Name::Name()
{
}


void Name::clear(GameEngine* game)
{
	this->score = game->get_last_score();
}


void Name::events(GameEngine* game, sf::Event event)
{
	switch(event.type){
	case sf::Event::MouseMoved:
		this->submit.hover_point(sf::Vector2f(event.mouseMove.x,event.mouseMove.y));
		break;
	case sf::Event::MouseButtonPressed:
		if(this->submit.hover_point(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
			game->change_state(&(MainMenu::get_instance()));
		}
	}
}


void Name::init(GameEngine* game)
{
	sf::Font* inc_bold = game->get_font("Inconsolata-Bold");
	sf::Window* window = game->get_window();
	this->submit = Button(sf::Vector2f(window->getSize().x/2.0f, window->getSize().y*2.0f/3.0f)-sf::Vector2f(100,25), sf::Vector2f(200,50), "ENTER");
	this->submit.text->setFont(*inc_bold);
	this->clear(game);
}


void Name::pause()
{
		return /* something */;
}


void Name::render(GameEngine* game, float interp)
{
	sf::RenderWindow* window = game->get_window();
	window->draw(this->submit.get_rect());
	window->draw(this->submit.get_text());
}


void Name::resume()
{
		return /* something */;
}


void Name::update(GameEngine* game)
{
}

