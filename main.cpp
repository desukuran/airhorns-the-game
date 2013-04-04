#include <iostream>
#include "audiere.h"
#include <string>
#include <cstdio>

#include "GameLogic.h"
#include "Music.h"
#include "Game.h"

#include "SDL.h"
#include "SDL_image.h"
#include "main.h"

using namespace audiere;
using namespace std;

int main(int argc, char* argv[])
{

	if (CGameLogic::InitGame())
		printf("Successfully Inited SDL");
	else 
		return 0;

	main::game = 1;

	CGame::flip();

	while(main::game)
	{
		CGame::CGame();
	}

	CGameLogic::CleanUp();

	return 0;
}