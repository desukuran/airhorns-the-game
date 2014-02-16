//"audiere test" - Omar Staying
// April 4, 2013, started on the 3rd. I guess.
// Buff Drinklots.

//Parts from http://lazyfoo.net/SDL_tutorials/
// I am lazy.


#include <iostream>
#include "audiere.h"
#include <string>
#include <cstdio>

#include "GameLogic.h"
#include "Music.h"
#include "Sound.h"
#include "Game.h"
#include "DebugMessage.h"
#include "config.h"

#include "SDL.h"
#include "SDL_image.h"
#include "main.h"

using namespace audiere;
using namespace std;

	bool CDebugMessage::debugOn;

int main(int argc, char* argv[])
{

	//If Initing everything is good, continue
	if (CGameLogic::InitGame())
		printf("Successfully Inited SDL");
	else 
		return 0;

	//If we reached this point, time to start the loop
	main::game = 1;

	if (CConfig::skiptitleFlag == 1)
		CGame::SetGameState(STATE_GAME);
	else
		CGame::SetGameState(STATE_LOGO);

	while(main::game)
	{
		CGame::Think();
		CGame::Render();
		CDebugMessage::Draw();
		CGame::flip();
	}

	//We're done here, let's clean up the mess.
	CGameLogic::CleanUp();

	return 0;
}