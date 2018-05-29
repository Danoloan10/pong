#include "IGameState.hpp"
#include "GameEngine.hpp"
GamePlay::GamePlay()
{
}

void GamePlay::init(GameEngine* game)
{
	this->walls[0] = sf::RectangleShape(sf::Vector2f(25,550));
	this->walls[3] = sf::RectangleShape(sf::Vector2f(25,550));
	this->walls[1] = sf::RectangleShape(sf::Vector2f(125,25));
	this->walls[2] = sf::RectangleShape(sf::Vector2f(125,25));
	for(int i = 0; i < sizeof(this->walls)/sizeof(this->walls[0]); i++) this->walls[i].setFillColor(sf::Color::White);

	this->floor = sf::RectangleShape(sf::Vector2f(350,25));
	this->floor.setFillColor(sf::Color::Red);

	this->bar = sf::RectangleShape(sf::Vector2f(100,25));
	this->bar.setFillColor(sf::Color::White);

	this->ball = sf::RectangleShape(sf::Vector2f(25,25));
    this->ball.setFillColor(sf::Color::White);
	
	this->sidebar = sf::RectangleShape(sf::Vector2f(300, 600));
	this->sidebar.setOutlineThickness(10);
	this->sidebar.setOutlineColor(sf::Color::White);
	this->sidebar.setFillColor(sf::Color::Black);

	this->sidebar.setPosition(0,0);
	
	this->walls[0].setPosition(350,50);
	this->walls[1].setPosition(375,50);
	this->walls[2].setPosition(600,50);
	this->walls[3].setPosition(725,50);
	
	this->floor.setPosition(375,575);
	
	this->bar.setPosition(500,525);
	this->ball.setPosition(537,500);

	//menu
	this->buttons[0] = Button(sf::Vector2f(50,400),sf::Vector2f(200,50), "Menu");
	this->buttons[1] = Button(sf::Vector2f(50,500),sf::Vector2f(200,50), "Quit");
	for(int i = 0; i < sizeof(this->buttons)/sizeof(this->buttons[0]); i++) buttons[i].text->setFont(*(game->get_font("Inconsolata-Bold")));
}

void GamePlay::clear(GameEngine* game)
{
	this->init(game);
}

void GamePlay::pause()
{
		return /* something */;
}

void GamePlay::resume()
{
		return /* something */;
}

void GamePlay::events(GameEngine* game, sf::Event event)
{
	switch(event.type){
	case sf::Event::MouseMoved:
		for(int i = 0; i < sizeof(this->buttons)/sizeof(this->buttons[0]); i++){
			this->buttons[i].hover_point(sf::Vector2f(event.mouseMove.x,event.mouseMove.y));	
		}
		break;
	case sf::Event::MouseButtonPressed:
		if(this->buttons[0].hover_point(sf::Vector2f(event.mouseMove.x,event.mouseMove.y))){
			//menu
		}
		else if (this->buttons[1].hover_point(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
			game->get_window()->close();
		}
		break;
	case sf::Event::KeyPressed:
		switch(event.key.code){
		case sf::Keyboard::Space:
			this->v_v = -V;
			this->v_h = -V;
			break;
		}
	}
}

void GamePlay::update(GameEngine* game)
{
//TODO mal
	bool move = true;
	sf::Vector2f new_pos = this->ball.getPosition()+(sf::Vector2f(this->v_h,this->v_v));
	if(this->walls[0].getGlobalBounds().contains(new_pos)){
		this->v_h = -this->v_h;
		move = false;
	}
	if(this->walls[3].getGlobalBounds().contains(new_pos+sf::Vector2f(this->ball.getSize().x,0))){
		this->v_h = -this->v_h;
		move = false;
	}
	if(this->bar.getGlobalBounds().contains(new_pos+sf::Vector2f(this->ball.getSize().x,0))){
		this->v_h = -this->v_h;
		move = false;
	}
	if(this->walls[1].getGlobalBounds().contains(new_pos) || this->walls[2].getGlobalBounds().contains(new_pos) || this->bar.getGlobalBounds().contains(new_pos+sf::Vector2f(0,this->ball.getSize().y))){
		this->v_v = -this->v_v;
		move = false;
	}
	if(this->floor.getGlobalBounds().contains(new_pos+sf::Vector2f(0,this->ball.getSize().y))){
		//game over
		this->v_v = -this->v_v;
		move = false;
	}
	if(move) this->ball.setPosition(new_pos);
}

void GamePlay::render(GameEngine* game, float interp)
{
	for(int i = 0; i < sizeof(this->walls)/sizeof(this->walls[0]); i++) game->get_window()->draw(walls[i]);
	game->get_window()->draw(floor);
	game->get_window()->draw(bar);
	game->get_window()->draw(ball);
	game->get_window()->draw(sidebar);
	for(int i = 0; i < sizeof(this->buttons)/sizeof(this->buttons[0]); i++){
		game->get_window()->draw(buttons[i].get_rect());
		game->get_window()->draw(buttons[i].get_text());
	}
}
