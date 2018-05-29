//CONSTANTS
static const float TICKS_PER_SECOND = 60;
static const float SKIP_MILLIS = 1000 / TICKS_PER_SECOND;
static const int MAX_FPS_SKIP = 5;

#include <SFML/System.hpp>
#include "GameEngine.hpp"

#include "IGameState.hpp"

#include <iostream>

//TIMING
static sf::Clock game_clk;
static sf::Time update_t;

//RUNTIME
static bool is_running = true;

//HEADERS
/*
 * This method defines the updates of the game
 */
void update_game();
/*
 * This method defines the rendering of the game
 */
void render_game(float);

/*
 * This main method implements the game loop.
 */
int main()
{
	GameEngine game = GameEngine("hola");
	game.change_state(&(MainMenu::get_instance()));

	game_clk.restart();
	while(game.is_running())
	{
		game.events();

		update_t = game_clk.getElapsedTime();
		int loops = 0;
		if(update_t.asMilliseconds() > SKIP_MILLIS && loops < MAX_FPS_SKIP){
			game.update();
			loops++;
			game_clk.restart();
		}
		
		float interp = (float) (game_clk.getElapsedTime().asMilliseconds()) / (float) SKIP_MILLIS;

		game.render(interp);
	}

	return 0;
}
