#include "IGameState.hpp"
#include "../GameEngine/GameEngine.hpp"

MainMenu::MainMenu()
{
}

MainMenu& MainMenu::get_instance(){
	static MainMenu instance;
	return instance; 
}

void MainMenu::init(GameEngine* game)
{
	sf::Font font;
	//font.loadFromFile("Hack-Bold.ttf");
	sf::Window* window = game->get_window();
	sf::Vector2f center(window->getSize().x/2, window->getSize().y/2);
	this->play_but = Button(center-sf::Vector2f(100,25), sf::Vector2f(200,50), "Play");
	this->play_but.text.setFont(font);
	center.y+= 100;
	this->quit_but = Button(center-sf::Vector2f(100,25), sf::Vector2f(200,50), "Quit");
	this->play_but.text.setFont(font);
}

void MainMenu::clear(GameEngine* game)
{
		return /* something */;
}


void MainMenu::next_state(GameEngine* game)
{
}


void MainMenu::pause()
{
		return /* something */;
}


void MainMenu::resume()
{
		return /* something */;
}


void MainMenu::events(GameEngine* game){
		sf::Event event;
		sf::RenderWindow* window = game->get_window();
		if(window->pollEvent(event)){
			switch(event.type){
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseMoved:
				if(this->play_but.over(sf::Vector2f(event.mouseMove.x,event.mouseMove.y))){
					this->play_but.is_hover = true;
				}else{
					this->play_but.is_hover = false;
				}

				if(this->quit_but.over(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))){
					this->quit_but.is_hover = true;
				}else{
					this->quit_but.is_hover = false;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if(this->quit_but.over(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
					window->close();
				}
				break;
			}
		}
}


void MainMenu::update(GameEngine* game){
		if(!game->get_window()->isOpen())
			game->quit();
}

void MainMenu::render(GameEngine* game, float interp)
{
	sf::RenderWindow* window = game->get_window();
	window->draw(this->play_but.get_rect());
//	window->draw(this->play_but.get_text());
	window->draw(this->quit_but.get_rect());
//	window->draw(this->quit_but.text);
}

