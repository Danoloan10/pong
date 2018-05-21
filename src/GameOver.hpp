#ifndef GOVER_H
#define GOVER_H

class GameOver : public IGameState{
public:
	static GameOver& get_instance(){ static GameOver g; return g; } //TODO duda

	void init(GameEngine* game);
	void clear(GameEngine* game);

	void pause();
	void resume();

	void events(GameEngine* game, sf::Event event);
	void update(GameEngine* game);
	void render(GameEngine* game, float interp);
protected:
	GameOver();
	Button cont;
};

#endif
