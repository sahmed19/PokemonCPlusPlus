#include <iostream>
#include "Game.h"
#include <time.h>
#include <sstream>

using namespace std;

int main()
{
	srand(time(NULL));
	Game* game = new Game();

	while (game->isPlaying()) {
		game->gameLoop();
	}
	return 0;
}