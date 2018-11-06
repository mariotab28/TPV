#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{
		Game* game = new Game();
		game->run();
		delete game;
	}
	catch (string ex)
	{
		cout << ex;
		system("pause");
	}
	return 0;
}