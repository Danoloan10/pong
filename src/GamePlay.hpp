#ifndef GPLAY_H
#define GPLAY_H

class GamePlay : public IGameState{
public:
	static GamePlay& get_instance(){ static GameOver g; return g; } //TODO duda

	void init(GameEngine* game);
	void clear(GameEngine* game);

	void pause();
	void resume();

	void events(GameEngine* game, sf::Event event);
	void update(GameEngine* game);
	void render(GameEngine* game, float interp);
protected:
	GameMain main;
	GamePlay();
};

#endif
