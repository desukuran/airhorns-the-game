//"audiere test" - Omar Staying
// April 4, 2013, started on the 3rd. I guess.
// Buff Drinklots.

//Parts from http://lazyfoo.net/SDL_tutorials/
// I am lazy.


#include <iostream>
#include "SDL/SDL_mixer.h"
#include <string>
#include <cstdio>

#include "GameLogic.h"
#include "Music.h"
#include "Sound.h"
#include "Game.h"
#include "DebugMessage.h"
#include "config.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "main.h"

	bool CDebugMessage::debugOn;

CGame gameClass;
CGameLogic logic;
CDebugMessage DEBUG;
CMainLogic mainLogic;
CConfig CONFIG;

int main(int argc, char* argv[])
{

	//If Initing everything is good, continue
	if (logic.InitGame())
		printf("Successfully Inited SDL");
	else
        return 0;

	//If we reached this point, time to start the loop
	mainLogic.game = 1;

	if (CConfig::skiptitleFlag == 1)
		gameClass.SetGameState(STATE_GAME);
	else
		gameClass.SetGameState(STATE_LOGO);

	while(mainLogic.game)
	{
		gameClass.Think();
		gameClass.Render();
		CDebugMessage::Draw();
		gameClass.flip();
	}

	//We're done here, let's clean up the mess.
	logic.CleanUp();

	return 0;
}
