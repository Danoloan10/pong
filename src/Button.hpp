#ifndef BUTT_H
#define BUTT_H

#include <SFML/Graphics.hpp>

struct Button{
	sf::Vector2f pos;
	sf::Vector2f size;

	sf::Color off = sf::Color::Black;
	sf::Color out_off = sf::Color::White;

	sf::Color hover = sf::Color::Black;
	sf::Color out_hover = sf::Color::Cyan;

	sf::Color push = sf::Color::Black;
	sf::Color out_push = sf::Color::Blue;

	sf::Text * text;

	bool is_hover = false;
	bool is_push = false;
	Button(){
		text = new sf::Text();
	}
	Button(sf::Vector2f p, sf::Vector2f s, std::string t) : Button(){
		pos = p;
		size = s;
		text->setString(t);
	}
	Button(sf::Vector2f s, std::string t) : Button(sf::Vector2f(0,0), s, t){}
	sf::Text& get_text(){
		text->setPosition(pos + 
						  sf::Vector2f(size.x/2, size.y/2) - 
						  sf::Vector2f(text->getLocalBounds().width/2.0f, 
						  			   text->getLocalBounds().height/2.0f) - 
						  sf::Vector2f(0,5));
		if(is_hover){
			text->setFillColor(out_hover);
		}else if(is_push){
			text->setFillColor(out_push);
		}else{
			text->setFillColor(out_off);
		}
		return *text;
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

	bool hover_point(sf::Vector2f point){
		if((point.x > pos.x-10) &&
		   (point.x < pos.x+size.x+10) &&
		   (point.y > pos.y-10) &&
		   (point.y < pos.y+size.y+10))
			is_hover = true;
		else is_hover = false;
		return is_hover;
	}
};

typedef struct Button Button;
#endif
