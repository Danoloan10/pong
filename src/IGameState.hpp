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

	virtual void events(GameEngine* game, sf::Event event) = 0;
	virtual void update(GameEngine* game) = 0;
	virtual void render(GameEngine* game, float interp) = 0;
protected:
	IGameState(){}
};

#include "ScoreBoard.hpp"

#include "Button.hpp"
#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "Name.hpp"
#include "GameOver.hpp"

#endif
