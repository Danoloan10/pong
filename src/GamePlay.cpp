#include <cmath>
#include <iostream>
#include "IGameState.hpp"
#include "GameEngine.hpp"
GamePlay::GamePlay()
{
}

void GamePlay::init(GameEngine* game)
{
	this->score = 0;

	this->score_title = sf::Text("SCORE:", *(game->get_font("Inconsolata-Bold")));
	this->score_title.setPosition(50,50);
	this->score_show = sf::Text();
	this->score_show.setFont(*(game->get_font()));
	this->score_show.setPosition(50,100);

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
	//menu
	this->buttons[0] = Button(sf::Vector2f(50,400),sf::Vector2f(200,50), "Menu");
	this->buttons[1] = Button(sf::Vector2f(50,500),sf::Vector2f(200,50), "Quit");
	for(int i = 0; i < sizeof(this->buttons)/sizeof(this->buttons[0]); i++) buttons[i].text->setFont(*(game->get_font("Inconsolata-Bold")));
	this->score = 0;
	this->clear(game);
}

void GamePlay::clear(GameEngine* game)
{
	this->score_now = MAX_SCORE;
	this->ticks = 0;

	this->over = false;
	this->running = false;
	this->win = false;

	this->left = false;
	this->right = false;

	this->walls[0].setPosition(350,50);
	this->walls[1].setPosition(375,50);
	this->walls[2].setPosition(600,50);
	this->walls[3].setPosition(725,50);
	
	this->floor.setPosition(375,575);
	
	this->bar.setPosition((game->get_window()->getSize().x-300)/2.f + 300 - this->bar.getSize().x/2.f,525);
	this->ball.setPosition(537,495);
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
		case sf::Keyboard::Left:
			this->left = true;
			break;
		case sf::Keyboard::Right:
			this->right = true;
			break;
		case sf::Keyboard::Space:
			if(!this->running){
				this->running = true;
				srand(time(NULL));
				float start_ang = (rand()%141+20)*3.14159265/180.;
				this->v_v = -V*std::sin(start_ang);
				this->v_h = V*std::cos(start_ang);
			}
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch(event.key.code){
			case sf::Keyboard::Left:
				this->left = false;
				break;
			case sf::Keyboard::Right:
				this->right = false;
				break;
		}
		break;
	}
}

sf::Vector2f rotate(float angle, sf::Vector2f vector, sf::Vector2f center=sf::Vector2f(0,0)){
	angle = angle*3.14159265/180.;
	float x = vector.x;
	float y = vector.y;
	float sn = std::sin(angle);
	float cs = std::cos(angle);

	x -= center.x;
	y -= center.y;

	x = x*cs - y*sn + center.x;
	y = x*sn + y*cs + center.y;

	return sf::Vector2f(x,y);
}
void GamePlay::update(GameEngine* game)
{
	this->ticks++;
	this->score_show.setString(std::to_string(this->score + score_now));
	if(running && !over){
			this->score_now = MAX_SCORE - MAX_SCORE*ticks/(MAX_TIME*60);
			if(this->score_now < 0) this->score_now = 0;
			sf::Vector2f ball_pos = this->ball.getPosition();
			if(ball_pos.y <= 0){
				this->over = this->win = true;
				return;
			}
			sf::Vector2f ball_size = this->ball.getSize();
			//walls E,W
			if (this->walls[0].getGlobalBounds().contains(ball_pos))
				this->v_h = std::abs(this->v_h);
			if(this->walls[3].getGlobalBounds().contains(ball_pos+sf::Vector2f(ball_size.x,0)))
				this->v_h = -std::abs(this->v_h);
			//walls N
			if (this->walls[1].getGlobalBounds().contains(ball_pos) ||
				this->walls[2].getGlobalBounds().contains(ball_pos+sf::Vector2f(ball_size.x,0))){
				if  (this->walls[1].getGlobalBounds().contains(ball_pos+sf::Vector2f(0,V))||
					this->walls[2].getGlobalBounds().contains(ball_pos+sf::Vector2f(ball_size.x,V)))
					this->v_h = -this->v_h;
				else 
					this->v_v = -this->v_v;
				
			}
			//bar
			if (this->bar.getGlobalBounds().contains(ball_pos+sf::Vector2f(0,ball_size.y)) || 
				this->bar.getGlobalBounds().contains(ball_pos+ball_size)){
				float x_off = ball_pos.x + (ball_size/2.f).x - this->bar.getPosition().x - this->bar.getSize().x/2.f; 
				float x_norm = x_off / (this->bar.getSize().x / 2.f);
				float angle = 75. * x_norm * 3.14159265 / 180.;
				this->v_v = -V*std::cos(angle);
				this->v_h = V*std::sin(angle);
			}	

			if(this->ball.getGlobalBounds().intersects(this->floor.getGlobalBounds()))
				this->over = true;
			//move ball
			this->ball.move(this->v_h, this->v_v);

			//move bar
			if(this->left){
				if(!this->bar.getGlobalBounds().intersects(this->walls[0].getGlobalBounds()))
					this->bar.move(-10,0);
			}else if(this->right){
				if(!this->bar.getGlobalBounds().intersects(this->walls[3].getGlobalBounds()))
					this->bar.move(10,0);
			}
		}else if(over && !win){
			game->set_last_score(this->score);
			game->change_state(&(Name::get_instance()));
		}else if(over && win){
			this->score += this->score_now;
			float s = this->bar.getSize().x-10;
			if(s > 10)
				this->bar.setSize(sf::Vector2f(s,this->bar.getSize().y));
			this->clear(game);
		}
	
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
	game->get_window()->draw(score_title);
	game->get_window()->draw(score_show);
}
