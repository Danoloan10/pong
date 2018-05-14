#ifndef IGAME_H
#define IGAME_H

#include <string>
#include <SFML/Graphics.hpp>

class GameEngine;

class IGameState{
public:
	virtual void init(GameEngine* game) = 0;
	virtual void clear(GameEngine* game) = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void events(GameEngine* game) = 0;
	virtual void update(GameEngine* game) = 0;
	virtual void render(GameEngine* game, float interp) = 0;
protected:
	IGameState(){}
	virtual void next_state(GameEngine* game) = 0;
};

struct Button{
	sf::Vector2f pos;
	sf::Vector2f size;

	sf::Color off = sf::Color::Black;
	sf::Color out_off = sf::Color::White;

	sf::Color hover = sf::Color::Black;
	sf::Color out_hover = sf::Color::Cyan;

	sf::Color push = sf::Color::Black;
	sf::Color out_push = sf::Color::Blue;

	sf::Text text;

	bool is_hover = false;
	bool is_push = false;
	Button(){}
	Button(sf::Vector2f p, sf::Vector2f s, std::string t){
		pos = p;
		size = s;
		text.setString(t);
		text.setPosition(pos);
	}
	sf::Text get_text(){
		sf::Text txt = text;
		if(is_hover){
			txt.setFillColor(out_hover);
		}else if(is_push){
			txt.setFillColor(out_push);
		}else{
			txt.setFillColor(out_off);
		}
		return txt;
	}
	sf::RectangleShape get_rect(){
		sf::RectangleShape rect;
		rect.setSize(size);
		rect.setPosition(pos);
		rect.setOutlineThickness(10);
		if(is_hover){
			rect.setFillColor(hover);
			rect.setOutlineColor(out_hover);
		}else if(is_push){
			rect.setFillColor(push);
			rect.setOutlineColor(out_push);
		}else{
			rect.setFillColor(off);
			rect.setOutlineColor(out_off);
		}
		return rect;
	}

	bool over(sf::Vector2f point){
		return (point.x > pos.x-10) &&
			   (point.x < pos.x+size.x+10) &&
			   (point.y > pos.y-10) &&
			   (point.y < pos.y+size.y+10);
	}
};

typedef struct Button Button;

class MainMenu : public IGameState{
public:
	static MainMenu& get_instance();

	void init(GameEngine* game);
	void clear(GameEngine* game);

	void pause();
	void resume();

	void events(GameEngine* game);
	void update(GameEngine* game);
	void render(GameEngine* game, float interp);
protected:
	MainMenu();
	Button play_but;
	Button quit_but;
	void next_state(GameEngine* game);
};
#endif
