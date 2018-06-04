#ifndef NAME_H
#define NAME_H

//This header file is meant to be included into IGameState.hpp

class Name : public IGameState{
public:
	static Name& get_instance(){ static Name m; return m; };

	void init(GameEngine* game);
	void clear(GameEngine* game);

	void pause();
	void resume();

	void events(GameEngine* game, sf::Event event);
	void update(GameEngine* game);
	void render(GameEngine* game, float interp);
protected:
	Name();
	Button submit;
	std::string name = "Player";
	int score = 0;
};
#endif
