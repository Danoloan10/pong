#ifndef STATE_H
#define STATE_H

#include "IGameState.hpp"

enum State{
	MainMenu,
	GameOver
};

IGameState* get_state(State state){
	switch(state){
	case MainMenu:
		return &MainMenu::get_instance();
	case GameOver:
		return &GameOver::get_instance();
	}
	return NULL;
}
#endif
