#ifndef GPLAY_H
#define GPLAY_H

class GamePlay : public IGameState{
public:
	static GamePlay& get_instance(){ static GamePlay g; return g; } //TODO duda

	void init(GameEngine* game);
	void clear(GameEngine* game);

	void pause();
	void resume();

	void events(GameEngine* game, sf::Event event);
	void update(GameEngine* game);
	void render(GameEngine* game, float interp);
protected:
	GamePlay();
private:
	sf::RectangleShape walls [4];
	sf::RectangleShape floor;

	sf::RectangleShape bar;
	sf::RectangleShape ball;

	sf::RectangleShape sidebar;
	
	sf::Text score_title;
	sf::Text score_show;

	Button buttons[2];

	int v_h = 0;
	int v_v = 0;

	int score = 0;

	static const int MAX_SCORE = 100;
	static const int MAX_TIME = 40;
	int ticks = 0;
	int score_now = 0;

	const int V = 5;
	
	bool left = false;
	bool right = false;

	bool running = false;
	bool over = false;
	bool win = false;
};

#endif
