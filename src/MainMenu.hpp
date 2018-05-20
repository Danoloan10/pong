#ifndef MAINMENU_H
#define MAINMENU_H

//This header file is meant to be included into IGameState.hpp

class MainMenu : public IGameState{
public:
	static MainMenu& get_instance(){ static MainMenu m; return m; }

	void init(GameEngine* game);
	void clear(GameEngine* game);

	void pause();
	void resume();

	void events(GameEngine* game, sf::Event event);
	void update(GameEngine* game);
	void render(GameEngine* game, float interp);
protected:
	MainMenu();
	Button play_but;
	Button quit_but;
};
#endif
