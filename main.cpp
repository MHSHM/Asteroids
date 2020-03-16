#include "pch.h"
#include "Game.h"


int main(int argc, char ** argv)
{
	Game game; 
	bool success = game.Initialize(); 
	if (success) 
	{
		game.RunGame(); 
	}
	game.Shutdown(); 
	return 0;
}