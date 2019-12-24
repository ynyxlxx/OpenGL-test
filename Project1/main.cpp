#include "Game.h"


int main()
{	
	Game game("THIS IS A WINDOW!!!", 640, 480, 4, 4, true);

	//Main loop

	while (!game.getWindowShouldClose())
	{
		game.update();
		game.render();
	}

	return 0;
}